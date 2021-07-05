/****************************************************************************
 *
 * @author Doniyor Tokhirov <tokhirovdoniyor(at)gmail.com>
 *
 ****************************************************************************/

#include "todomodel.h"

TodoModel::TodoModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

void TodoModel::setupModel(QList<Todo> todos)
{
    beginResetModel();
    setupModelNoUpdate(std::move(todos));
    endResetModel();
}

void TodoModel::setupModelNoUpdate(QList<Todo> todos)
{
    m_todos = todos;
}

void TodoModel::add(const Todo &todo)
{
    beginInsertRows({}, 0, 0);
    m_todos.append(todo);
    endInsertRows();
}

void TodoModel::remove(int index)
{
    beginRemoveRows({}, index, index);
    m_todos.removeAt(convertReverseIndex(index));
    endRemoveRows();
}

const Todo &TodoModel::get(int index) const
{
    return m_todos.at(convertReverseIndex(index));
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
        return m_todos[convertReverseIndex(index.row())].text;
    case Qt::DecorationRole:
        return m_todos[convertReverseIndex(index.row())].color;
    }
    return {};
}

bool TodoModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid()) return false;

    switch (role) {
    case Qt::DisplayRole:
        m_todos[convertReverseIndex(index.row())].text = value.toString();
        break;
    case Qt::DecorationRole:
        m_todos[convertReverseIndex(index.row())].color = value.value<QColor>();
        break;
    default:
        return false;
    }
    dataChanged(index, index, { role });
    return true;
}

int TodoModel::convertReverseIndex(int index) const
{
    return m_todos.size() - index - 1;
}
