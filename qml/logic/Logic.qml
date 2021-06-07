import QtQuick 2.0

Item {
    signal addTodo()
    signal updateAddedTodo(var index, var text)
    signal editTodo(var index, var text)
    signal removeTodo(var index)
}
