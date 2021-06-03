/****************************************************************************
 *
 * @author Doniyor Tokhirov <tokhirovdoniyor(at)gmail.com>
 *
 ****************************************************************************/

#pragma once

#include <QObject>

#include <models/todomodel.h>

class TodoController : public QObject
{
    Q_OBJECT

    Q_PROPERTY(TodoModel *todoModel READ todoModel CONSTANT)

public:
    explicit TodoController(const TodoDao &todoDao, QObject *parent = nullptr);

    TodoModel *todoModel();

private:
    TodoModel m_todoModel;
};

