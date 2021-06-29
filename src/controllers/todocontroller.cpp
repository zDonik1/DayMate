/****************************************************************************
 *
 * @author Doniyor Tokhirov <tokhirovdoniyor(at)gmail.com>
 *
 ****************************************************************************/

#include "todocontroller.h"

#include <QRegularExpression>

TodoController::TodoController(DatabaseManager &dbManager, QObject *parent)
    : QObject(parent)
    , m_databaseManager(dbManager)
{
    m_todoModel.setupModel(m_databaseManager.getDao<TodoDao>().get());

    QList<QColor> fullColors{ std::begin(TODO_COLORS), std::end(TODO_COLORS) };

    QList<QColor> activeColors = { Qt::black }; // serves as "all" colors
    activeColors.append(fullColors);
    m_activeColorModel.setupModel(activeColors);
    m_activeColorModel.activate(0);
    m_activeColorModel.setCurrentIndex(0);

    m_fullColorModel.setupModel(fullColors);
    m_fullColorModel.setAllActive();

    updateActiveColorModel();
}

TodoModel *TodoController::todoModel()
{
    return &m_todoModel;
}

ColorModel *TodoController::activeColorModel()
{
    return &m_activeColorModel;
}

ColorModel *TodoController::fullColorModel()
{
    return &m_fullColorModel;
}

void TodoController::addTodo()
{
    // adding into database
    const auto color = m_activeColorModel.currentIndex() == 0
            ? m_fullColorModel.get(0) : m_activeColorModel.currentColor();
    const auto newTodo = m_databaseManager.getDao<TodoDao>()
            .add({ color });

    // adding to model
    m_todoModel.add(newTodo);

    // update popup color picker
    if (m_activeColorModel.currentIndex() == 0) {
        updateActiveColorModel();
    }
}

void TodoController::editTodo(int index, QString todoText)
{
    // remove trailing new lines
    todoText = todoText.trimmed();

    // editing in database
    const auto &todo = m_todoModel.get(index);
    m_databaseManager.getDao<TodoDao>().edit({ todo.uuid, todoText, todo.color });

    // editing in model
    m_todoModel.setData(m_todoModel.index(index), todoText, Qt::DisplayRole);
}

void TodoController::editColor(int todoIndex, int colorIndex)
{
    // editing in database
    const auto &todo = m_todoModel.get(todoIndex);
    const auto color = m_fullColorModel.get(colorIndex);
    m_databaseManager.getDao<TodoDao>().edit({ todo.uuid, todo.text, color });

    // editing in model
    if (m_activeColorModel.currentIndex() == 0) { // if "all colors"
        m_todoModel.setData(m_todoModel.index(todoIndex), color, Qt::DecorationRole);
    } else if (m_activeColorModel.currentIndex() != colorIndex) { // not current color group
        if (m_todoModel.rowCount() == 1) {
            selectColorGroup(0); // reset to "all colors"
        } else {
            m_todoModel.remove(todoIndex);
        }
    }

    // update popup color picker
    updateActiveColorModel();
}

void TodoController::removeTodo(int index)
{
    // removing in database
    m_databaseManager.getDao<TodoDao>().remove(m_todoModel.get(index).uuid);

    // removing in model
    m_todoModel.remove(index);

    // update popup color picker
    updateActiveColorModel();
}

void TodoController::selectColorGroup(int index)
{
    if (m_activeColorModel.currentIndex() == index) return;

    m_activeColorModel.setCurrentActiveIndex(index);
    if (index == 0) {
        const auto todos = m_databaseManager.getDao<TodoDao>().get();
        m_todoModel.setupModel(todos);
    } else {
        const auto todos = m_databaseManager.getDao<TodoDao>().getColoredTodos(
                    m_activeColorModel.getActive(index));
        m_todoModel.setupModel(todos);
    }
}

void TodoController::updateActiveColorModel()
{
    const auto todoUsedColors = m_databaseManager.getDao<TodoDao>().getColors();
    m_activeColorModel.setAllActive(false);
    m_activeColorModel.activate(0);
    for (auto &color : todoUsedColors) {
        m_activeColorModel.activate(m_fullColorModel.colorIndex(color) + 1);
    }
}
