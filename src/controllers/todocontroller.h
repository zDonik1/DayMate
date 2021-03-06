/****************************************************************************
 *
 * @author Doniyor Tokhirov <tokhirovdoniyor(at)gmail.com>
 *
 ****************************************************************************/

#pragma once

#include <QObject>

#include "database/databasemanager.h"
#include <models/todomodel.h>

class TodoController : public QObject
{
    Q_OBJECT

    Q_PROPERTY(TodoModel *todoModel READ todoModel CONSTANT)

public:
    explicit TodoController(DatabaseManager &dbManager, QObject *parent = nullptr);

    TodoModel *todoModel();

public slots:
    void addTodo();
    void editTodo(int index, const QString &todoText);
    void removeTodo(int index);

private:
    DatabaseManager &m_databaseManager;
    TodoModel m_todoModel;
};

