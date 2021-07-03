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
    int order;

    Todo()
    {
    }

    Todo(QColor l_color)
        : color(l_color)
    {
    }

    Todo(QUuid l_uuid, QString l_text, QColor l_color, int l_order)
        : uuid(l_uuid)
        , text(l_text)
        , color(l_color)
        , order(l_order)
    {
    }
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
    QList<Todo> getColoredTodos(const QColor &color) const;
    QList<Todo> getInRange(int begin, int end) const;
    QList<QColor> getColors() const;
};

