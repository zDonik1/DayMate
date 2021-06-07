import QtQuick 2.0

Item {
    signal addTodo()
    signal editTodo(var index, var text)
    signal removeTodo(var index)
}
