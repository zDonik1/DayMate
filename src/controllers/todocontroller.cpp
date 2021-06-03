/****************************************************************************
 *
 * @author Doniyor Tokhirov <tokhirovdoniyor(at)gmail.com>
 *
 ****************************************************************************/

#include "todocontroller.h"

TodoController::TodoController(DatabaseManager &dbManager, QObject *parent)
    : QObject(parent)
    , m_databaseManager(dbManager)
    , m_todoModel(m_databaseManager.getDao<TodoDao>())
{
}

TodoModel *TodoController::todoModel()
{
    return &m_todoModel;
}

void TodoController::addTodo(const QString &todoText)
{
    // adding into database
    auto todoDao = m_databaseManager.getDao<TodoDao>();
    auto newTodo = todoDao.add({ "", todoText });

    // adding to model
    m_todoModel.add(newTodo);
}
