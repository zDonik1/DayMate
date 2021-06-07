/****************************************************************************
 *
 * @author Doniyor Tokhirov <tokhirovdoniyor(at)gmail.com>
 *
 ****************************************************************************/

#include "todomodel.h"

TodoModel::TodoModel(const TodoDao &todoDao, QObject *parent)
    : QAbstractListModel(parent)
    , m_todoDao(todoDao)
{
    setupModel();
}

void TodoModel::setupModel()
{
    beginResetModel();
    m_todos = m_todoDao.get();
    endResetModel();
}

void TodoModel::add(const Todo &todo)
{
    beginInsertRows({}, rowCount(), rowCount());
    m_todos.append(todo);
    endInsertRows();
}

void TodoModel::remove(int index)
{
    beginRemoveRows({}, index, index);
    m_todos.removeAt(index);
    endRemoveRows();
}

void TodoModel::update(int index, const Todo &todo)
{
    m_todos[index] = todo;
    dataChanged(createIndex(index, 0), createIndex(index, 0), { Qt::DisplayRole });
}

const Todo &TodoModel::get(int index) const
{
    return m_todos.at(index);
}

int TodoModel::rowCount(const QModelIndex &/*parent*/) const
{
    return m_todos.size();
}

QVariant TodoModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) return {};

    switch (role) {
    case Qt::DisplayRole:
        return m_todos[index.row()].text;
    }
    return {};
}

bool TodoModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid()) return false;

    switch (role) {
    case Qt::DisplayRole:
        m_todos[index.row()].text = value.toString();
        break;
    default:
        return false;
    }
    dataChanged(index, index, { role });
    return true;
}
