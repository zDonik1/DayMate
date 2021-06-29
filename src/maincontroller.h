/****************************************************************************
 *
 * @author Doniyor Tokhirov <tokhirovdoniyor(at)gmail.com>
 *
 ****************************************************************************/

#pragma once

#include <QObject>

#include "controllers/todocontroller.h"

class MainController : public QObject
{
    Q_OBJECT

    Q_PROPERTY(TodoController *todoController READ todoController CONSTANT)

public:
    explicit MainController(QObject *parent = nullptr);

    Q_INVOKABLE void setFullscreen();

    TodoController *todoController();

private:
    DatabaseManager m_databaseManager;
    TodoController m_todoController;
};

