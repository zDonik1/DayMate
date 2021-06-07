import QtQuick 2.0

import Felgo 3.0

import "logic"
import "pages"
import "helper"
import "components"

App {
    id: app

    onInitTheme: {
        Theme.colors.tintColor = "#34495e"
        Theme.colors.textColor = "#d8efc9"
        Theme.colors.secondaryTextColor = "#a2acad"
        Theme.colors.backgroundColor = "#2c3e50"
        Theme.colors.secondaryBackgroundColor = "#34495e"
        Theme.navigationBar.titleColor = Theme.textColor
    }

    // business logic
    Logic {
        id: logic

        onAddTodo: mainController.todoController.addTodo()
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

                    onClicked: todoListPage.addTodo()
                }

                splitView: tablet // use side-by-side view on tablets
                initialPage: TodoListPage {
                    id: todoListPage
                }
            }
        }
    }
}
