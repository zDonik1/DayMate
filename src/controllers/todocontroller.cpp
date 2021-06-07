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

void TodoController::addTodo()
{
    // adding to model
    m_todoModel.add({});
}

void TodoController::updateAddedTodo(int index, const QString &todoText)
{
    // adding into database
    const auto newTodo = m_databaseManager.getDao<TodoDao>().add({ "", todoText });

    // updating model
    m_todoModel.update(index, newTodo);
}

void TodoController::editTodo(int index, const QString &todoText)
{
    // editing in database
    const auto &todo = m_todoModel.get(index);
    m_databaseManager.getDao<TodoDao>().edit({ todo.uuid, todoText});

    // editing in model
    m_todoModel.setData(m_todoModel.index(index), todoText, Qt::DisplayRole);
}

void TodoController::removeTodo(int index)
{
    // removing in database
    m_databaseManager.getDao<TodoDao>().remove(m_todoModel.get(index).uuid);

    // removing in model
    m_todoModel.remove(index);
}
