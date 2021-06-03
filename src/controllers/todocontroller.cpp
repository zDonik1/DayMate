/****************************************************************************
 *
 * @author Doniyor Tokhirov <tokhirovdoniyor(at)gmail.com>
 *
 ****************************************************************************/

#include "todocontroller.h"

TodoController::TodoController(const TodoDao &todoDao, QObject *parent)
    : QObject(parent)
    , m_todoModel(todoDao)
{
}

TodoModel *TodoController::todoModel()
{
    return &m_todoModel;
}
