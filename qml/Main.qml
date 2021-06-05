import QtQuick 2.0

import Felgo 3.0

import "logic"
import "pages"
import "helper"

App {
    id: app

    onInitTheme: {
        Theme.colors.tintColor = "#0f2a62"
        Theme.colors.textColor = "#d8efc9"
        Theme.colors.backgroundColor = "#0c2351"
        Theme.navigationBar.titleColor = Theme.textColor
    }

    // business logic
    Logic {
        id: logic

        onAddTodo: mainController.todoController.addTodo(text)
        onEditTodo: mainController.todoController.editTodo(index, text)
        onRemoveTodo: mainController.todoController.removeTodo(index)
    }

    // view
    Navigation {
        id: navigation
        navigationMode: navigationModeTabs

        // first tab
        NavigationItem {
            title: qsTr("Todo List")
            icon: IconType.list

            NavigationStack {
                navigationBar.rightBarItem: IconButtonBarItem {
                    icon: IconType.plus

                    onClicked: helper.openAddTodoDialog()
                }

                splitView: tablet // use side-by-side view on tablets
                initialPage: TodoListPage {}
            }
        }
    }

    QtObject {
        id: helper

        function openAddTodoDialog() {
            InputDialog.inputTextSingleLine(app, qsTr("Add Todo"), qsTr("Todo text"),
                                            function(ok, text) {
                                                if (ok) logic.addTodo(text)
                                            })
        }

        function openEditTodoDialog(index, text) {
            InputDialog.inputTextSingleLine(app, qsTr("Edit Todo"), text,
                                            function(ok, text) {
                                                if (ok) logic.editTodo(index, text)
                                            })
        }
    }
}
