import QtQuick 2.0

Item {
    signal addTodo()
    signal editTodo(var index, var text)
    signal editTodoColor(var todoIndex, var colorIndex)
    signal removeTodo(var index)
    signal moveTodo(var prevIndex, var nextIndex)

    signal setColorInColorPicker(var color)
    signal selectColorGroup(var index)
}
