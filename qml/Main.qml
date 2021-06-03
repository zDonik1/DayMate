import QtQuick 2.0

import Felgo 3.0

import "logic"
import "pages"
import "helper"

App {
    id: app

    // business logic
    Logic {
        id: logic

        onAddTodo: mainController.todoController.addTodo(text)
    }

    // view
    Navigation {
        id: navigation

        // first tab
        NavigationItem {
            title: qsTr("Todo List")
            icon: IconType.list

            NavigationStack {
                navigationBar.rightBarItem: IconButtonBarItem {
                    icon: IconType.plus
                    color: Theme.backgroundColor

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
                                                if (ok) {
                                                    logic.addTodo(text)
                                                }
                                            })
        }
    }
}
