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
