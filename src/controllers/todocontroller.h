/****************************************************************************
 *
 * @author Doniyor Tokhirov <tokhirovdoniyor(at)gmail.com>
 *
 ****************************************************************************/

#pragma once

#include <QObject>

#include "database/databasemanager.h"
#include <models/todomodel.h>
#include <models/colormodel.h>

class TodoController : public QObject
{
    Q_OBJECT

    Q_PROPERTY(TodoModel *todoModel READ todoModel CONSTANT)
    Q_PROPERTY(ColorModel *activeColorModel READ activeColorModel CONSTANT)
    Q_PROPERTY(ColorModel *fullColorModel READ fullColorModel CONSTANT)

public:
    explicit TodoController(DatabaseManager &dbManager, QObject *parent = nullptr);

    TodoModel *todoModel();
    ColorModel *activeColorModel();
    ColorModel *fullColorModel();

public slots:
    void addTodo();
    void editTodo(int index, QString todoText);
    void editColor(int todoIndex, int colorIndex);
    void removeTodo(int index);
    void moveTodo(int prevIndex, int nextIndex);

    void selectColorGroup(int index);

private:
    void updateActiveColorModel();

private:
    DatabaseManager &m_databaseManager;
    TodoModel m_todoModel;
    ColorModel m_activeColorModel;
    ColorModel m_fullColorModel;
};

