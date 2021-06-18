/****************************************************************************
 *
 * @author Doniyor Tokhirov <tokhirovdoniyor(at)gmail.com>
 *
 ****************************************************************************/

#pragma once

#include <QUuid>
#include <QColor>

#include "abstractdao.h"

struct Todo {
    QUuid uuid;
    QString text;
    QColor color;
};

class TodoDao : public AbstractDao
{
public:
    TodoDao();

    // returns new todo with added uuid
    Todo add(const Todo &todo) const;
    bool edit(const Todo &todo) const;
    bool remove(const QUuid &uuid) const;
    QList<Todo> get() const;
};

