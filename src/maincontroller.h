/****************************************************************************
 *
 * @author Doniyor Tokhirov <tokhirovdoniyor(at)gmail.com>
 *
 ****************************************************************************/

#pragma once

#include <QObject>

#include "database/databasemanager.h"
#include "controllers/todocontroller.h"

class MainController : public QObject
{
    Q_OBJECT

    Q_PROPERTY(TodoController *todoController READ todoController CONSTANT)

public:
    explicit MainController(QObject *parent = nullptr);

    TodoController *todoController();

private:
    DatabaseManager m_databaseManager;

    TodoController m_todoController;
};

