import QtQuick 2.0

import Felgo 3.0

import "logic"
import "pages"
import "helper"
import "components"

App {
    id: app

    function setAlpha(color, alpha) {
        return Qt.hsla(color.hslHue, color.hslSaturation, color.hslLightness, alpha)
    }

    Component.onCompleted: {
        mainController.setFullscreen()
        showFullScreen()
    }

    onInitTheme: {
        Theme.colors.tintColor = "#34495e"
        Theme.colors.textColor = "#d8efc9"
        Theme.colors.secondaryTextColor = "gray"
        Theme.colors.backgroundColor = "#2c3e50"
        Theme.colors.secondaryBackgroundColor = "#34495e"
        Theme.colors.inputCursorColor = "#a2acad"
        Theme.colors.inputSelectionColor = "gray"
        Theme.navigationBar.titleColor = Theme.textColor
    }

    // business logic
    Logic {
        id: logic

        onAddTodo: mainController.todoController.addTodo()
        onEditTodo: mainController.todoController.editTodo(index, text)
        onEditTodoColor: mainController.todoController.editColor(todoIndex, colorIndex)
        onRemoveTodo: mainController.todoController.removeTodo(index)
        onMoveTodo: mainController.todoController.moveTodo(prevIndex, nextIndex)

        onSetColorInColorPicker:
            mainController.todoController.fullColorModel.currentColor = color
        onSelectColorGroup: mainController.todoController.selectColorGroup(index)
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
                navigationBar.rightBarItem: NavigationBarRow {
                    ColorButton {
                        source: mainController.todoController.activeColorModel.currentIndex === 0
                                ? Qt.resolvedUrl("../assets/four_colors.png")
                                : selectedSource
                        color: mainController.todoController.activeColorModel.currentColor

                        onClicked: colorPickerPopup.open()

                        ColorPickerPopup {
                            id: colorPickerPopup
                            x: (parent.width - width) / 2
                            y: dp(5)
                        }
                    }

                    IconButtonBarItem {
                        icon: IconType.plus

                        onClicked: todoListPage.addTodo()
                    }
                }

                splitView: tablet // use side-by-side view on tablets
                initialPage: TodoListPage {
                    id: todoListPage
                }
            }
        }
    }
}
