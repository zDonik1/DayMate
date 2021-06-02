/****************************************************************************
 *
 * @author Doniyor Tokhirov <tokhirovdoniyor(at)gmail.com>
 *
 ****************************************************************************/

#pragma once

#include <QUuid>

#include "abstractdao.h"

struct Todo {
    QUuid uuid;
    QString text;
};

class TodoDao : public AbstractDao
{
public:
    TodoDao();

    bool add(const Todo &todo) const;
    bool edit(const Todo &todo) const;
    bool remove(const QUuid &uuid) const;
    QList<Todo> get() const;
};

