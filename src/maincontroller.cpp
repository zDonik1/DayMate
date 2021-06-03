/****************************************************************************
 *
 * @author Doniyor Tokhirov <tokhirovdoniyor(at)gmail.com>
 *
 ****************************************************************************/

#include "maincontroller.h"

MainController::MainController(QObject *parent)
    : QObject(parent)
    , m_todoController(m_databaseManager)
{
}

TodoController *MainController::todoController()
{
    return &m_todoController;
}
