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
                             "color text"
                             ")")
                     .arg(TABLE));
    } else if (!executeQuery(QString("select color from %1").arg(TABLE)).first) {
        executeQuery(QString("alter table %1 add color text default '%2'")
                     .arg(TABLE, TODO_COLORS[0].name(QColor::HexRgb)));
    }
}

Todo TodoDao::add(const Todo &todo) const
{
    const auto uuid = QUuid::createUuid();
    auto success = executeQuery(QString("insert into %1 (uuid, todo, color) values('%2', '%3', '%4')")
                                .arg(TABLE, uuid.toString(QUuid::WithoutBraces),
                                     todo.text, todo.color.name(QColor::HexRgb))).first;
    return success ? Todo{ uuid, todo.text, todo.color } : Todo{};
}

bool TodoDao::edit(const Todo &todo) const
{
    return executeQuery(QString("update %1 set todo='%2', color='%3' where uuid='%4'")
                        .arg(TABLE, todo.text, todo.color.name(QColor::HexRgb),
                             todo.uuid.toString(QUuid::WithoutBraces))).first;
}

bool TodoDao::remove(const QUuid &uuid) const
{
    return executeQuery(QString("delete from %1 where uuid='%2'")
                        .arg(TABLE, uuid.toString(QUuid::WithoutBraces))).first;
}

QList<Todo> TodoDao::get() const
{
    auto [success, query] = executeQuery(QString("select * from %1").arg(TABLE));
    if (!success) return {};

    QList<Todo> todos;
    while (query.next()) {
        Todo todo;
        todo.uuid = query.value(0).toString();
        todo.text = query.value(1).toString();
        todo.color.setNamedColor(query.value(2).toString());
        todos.push_back(std::move(todo));
    }
    return todos;
}

QList<Todo> TodoDao::getColoredTodos(const QColor &color) const
{
    auto [success, query] = executeQuery(QString("select * from %1 where color='%2'")
            .arg(TABLE, color.name(QColor::HexRgb)));
    if (!success) return {};

    QList<Todo> todos;
    while (query.next()) {
        Todo todo;
        todo.uuid = query.value(0).toString();
        todo.text = query.value(1).toString();
        todo.color = color;
        todos.push_back(std::move(todo));
    }
    return todos;
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
