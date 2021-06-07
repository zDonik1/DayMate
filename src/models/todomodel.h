/****************************************************************************
 *
 * @author Doniyor Tokhirov <tokhirovdoniyor(at)gmail.com>
 *
 ****************************************************************************/

#pragma once

#include <QObject>
#include <QAbstractListModel>

#include <database/tododao.h>

class TodoModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit TodoModel(const TodoDao &todoDao, QObject *parent = nullptr);

    void setupModel();
    void add(const Todo &todo);
    void remove(int index);
    void update(int index, const Todo &todo);

    const Todo &get(int index) const;

    int rowCount(const QModelIndex &parent = {}) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

private:
    const TodoDao &m_todoDao;
    QList<Todo> m_todos;
};

