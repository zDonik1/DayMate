/****************************************************************************
 *
 * @author Doniyor Tokhirov <tokhirovdoniyor(at)gmail.com>
 *
 ****************************************************************************/

#include "tododao.h"

#include <QSqlDatabase>
#include <QStringList>
#include <QVariant>

static constexpr auto TABLE = "todo";

TodoDao::TodoDao()
{
    auto database = QSqlDatabase::database();
    if (!database.tables().contains(TABLE)) {
        executeQuery(QString("create table %1 ("
                             "uuid text primary key," // id is a uuid
                             "todo text"
                             ")")
                     .arg(TABLE));
    }
}

bool TodoDao::add(const Todo &todo) const
{
    return executeQuery(QString("insert into %1 (uuid, todo) values('%2', '%3')")
                        .arg(TABLE, QUuid::createUuid().toString(QUuid::WithoutBraces),
                             todo.text)).first;
}

bool TodoDao::edit(const Todo &todo) const
{
    return executeQuery(QString("update %1 set todo='%2' where uuid='%3'")
                        .arg(TABLE, todo.text,
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
        todos.push_back(std::move(todo));
    }
    return todos;
}
