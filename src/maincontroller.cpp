/****************************************************************************
 *
 * @author Doniyor Tokhirov <tokhirovdoniyor(at)gmail.com>
 *
 ****************************************************************************/

#include "maincontroller.h"

#include "androidnatives.h"

MainController::MainController(QObject *parent)
    : QObject(parent)
    , m_todoController(m_databaseManager)
{
}

void MainController::setFullscreen()
{
    nativeSetFullscreen();
}

TodoController *MainController::todoController()
{
    return &m_todoController;
}
