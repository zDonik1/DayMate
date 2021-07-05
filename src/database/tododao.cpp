/****************************************************************************
 *
 * @author Doniyor Tokhirov <tokhirovdoniyor(at)gmail.com>
 *
 ****************************************************************************/

#include "tododao.h"

#include <QSqlDatabase>
#include <QStringList>
#include <QVariant>

#include <globals.h>

static constexpr auto TABLE = "todo";

TodoDao::TodoDao()
{
    auto database = QSqlDatabase::database();

    if (!database.tables().contains(TABLE)) {
        executeQuery(QString("create table %1 ("
                             "uuid text primary key," // id is a uuid
                             "todo text,"
                             "color text,"
                             "order_rank integer"
                             ")")
                     .arg(TABLE));
    } else if (!executeQuery(QString("select color from %1").arg(TABLE)).first) {
        executeQuery(QString("alter table %1 add color text default '%2'")
                     .arg(TABLE, TODO_COLORS[0].name(QColor::HexRgb)));
    } else if (!executeQuery(QString("select order_rank from %1").arg(TABLE)).first) {
        executeQuery(QString("alter table %1 add order_rank integer").arg(TABLE));
        auto todos = get();
        for (int i = 0; i < todos.size(); ++i) {
            auto todo = todos[todos.size() - i - 1];
            todo.order = i;
            update(todo);
        }
    }
}

Todo TodoDao::add(const Todo &todo) const
{
    const auto uuid = QUuid::createUuid();
    auto success = executeQuery(QString("insert into %1 (uuid, todo, color, order_rank) "
                                        "values('%2', '%3', '%4', %5)")
                                .arg(TABLE, uuid.toString(QUuid::WithoutBraces),
                                     todo.text, todo.color.name(QColor::HexRgb))
                                .arg(todo.order)).first;
    return success ? Todo{ uuid, todo.text, todo.color, todo.order } : Todo{};
}

bool TodoDao::update(const Todo &todo) const
{
    return executeQuery(QString("update %1 set todo='%2', color='%3', order_rank=%5 where uuid='%4'")
                        .arg(TABLE, todo.text, todo.color.name(QColor::HexRgb),
                             todo.uuid.toString(QUuid::WithoutBraces))
                        .arg(todo.order)).first;
}

bool TodoDao::remove(const QUuid &uuid) const
{
    return executeQuery(QString("delete from %1 where uuid='%2'")
                        .arg(TABLE, uuid.toString(QUuid::WithoutBraces))).first;
}

QList<Todo> TodoDao::get() const
{
    return getListInRange(0, -1);
}

QList<Todo> TodoDao::getColoredTodos(const QColor &color) const
{
    auto [success, query] = executeQuery(QString("select * from %1 where color='%2' "
            "order by order_rank asc").arg(TABLE, color.name(QColor::HexRgb)));
    if (!success) return {};

    return getTodosFromQuery(query);
}

QList<Todo> TodoDao::getListInRange(int begin, int end) const
{
    auto queryString = QString("select * from %1 where order_rank >= %2")
            .arg(TABLE).arg(begin);
    if (end >= 0) queryString.append(QString(" and order_rank < %1").arg(end));
    queryString.append(" order by order_rank asc");

    auto [success, query] = executeQuery(queryString);
    if (!success) return {};

    return getTodosFromQuery(query);
}

int TodoDao::getLastOrder() const
{
    auto [success, query] = executeQuery(
            QString("select order_rank from %1 order by order_rank desc").arg(TABLE));
    if (!success) return {};

    if (query.next())
        return query.value(0).toInt();
    else
        return -1;
}

QList<QColor> TodoDao::getColors() const
{
    auto [success, query] = executeQuery(QString("select distinct color from %1").arg(TABLE));
    if (!success) return {};

    QList<QColor> colors;
    while (query.next()) {
        colors.push_back(query.value(0).value<QColor>());
    }
    return colors;
}

QList<Todo> TodoDao::getTodosFromQuery(QSqlQuery &query) const
{
    QList<Todo> todos;
    while (query.next()) {
        Todo todo;
        todo.uuid = query.value(0).toString();
        todo.text = query.value(1).toString();
        todo.color.setNamedColor(query.value(2).toString());
        todo.order = query.value(3).toInt();
        todos.push_back(std::move(todo));
    }
    return todos;
}
