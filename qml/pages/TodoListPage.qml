import QtQuick 2.15
import QtQuick.Controls 2.12
import QtQml.Models 2.12

import Felgo 3.0

import "../components"

Page {
    function addTodo() {
        if (listView.itemBeingAdded) {
            closeSelectedTodo()
        }
        logic.addTodo()
        listView.itemBeingAdded = true
        listView.currentIndex = 0
        listView.currentItem.focusOnText()
    }

    function closeSelectedTodo() {
        if (listView.currentIndex === -1) return

        listView.itemBeingAdded = false
        listView.currentItem.onDeselected()
        listView.currentIndex = -1
    }

    property alias listView: listView

    id: page
    title: qsTr("Todo List")

    Connections {
        target: app

        function onBackButtonPressedGlobally(event) {
            event.accepted = true
            closeSelectedTodo()
        }
    }

    DelegateModel {
        property int countAtStart: -1

        id: todoDelegateModel
        model: mainController.todoController.todoModel
        delegate: TodoDelegate {
            text: display
            selected: ListView.isCurrentItem
            itemsIndex: DelegateModel.itemsIndex
        }

        Component.onCompleted: if (count > 0) countAtStart = count
    }

    AppListView {
        property bool itemBeingAdded: false

        id: listView
        anchors.fill: parent
        spacing: -dp(5)
        model: todoDelegateModel
        currentIndex: -1
        boundsBehavior: Flickable.StopAtBounds
        scrollIndicatorVisible: true
        emptyView.children: [
            Item {
                anchors.centerIn: parent
                width: childrenRect.width
                height: childrenRect.height

                AppText {
                    id: firstTextOnEmpty
                    anchors.horizontalCenter: parent.horizontalCenter
                    color: Theme.textColor
                    font.pixelSize: sp(25)
                    text: qsTr("Add your first todo")
                }

                Row {
                    anchors {
                        top: firstTextOnEmpty.bottom
                        horizontalCenter: parent.horizontalCenter
                    }

                    AppText {
                        color: Theme.textColor
                        font.pixelSize: sp(25)
                        text: qsTr("by pressing")
                    }

                    Icon {
                        width: dp(35)
                        height: dp(35)
                        icon: IconType.plus
                    }
                }
            }
        ]

        // DelegateModel uses "add" mechanic to setup model, so last element is "selected"
        onCurrentIndexChanged: if (countAtStart !== -1 && currentIndex === count - 1) {
                                   todoDelegateModel.countAtStart = -1
                                   closeSelectedTodo()
                               }

        // transitions
        add: Transition {
            NumberAnimation {
                property: "x"
                from: page.width / 2
                duration: 100
                easing.type: Easing.OutCubic
            }
            NumberAnimation {
                property: "opacity"
                from: 0
                to: 1
                duration: 50
            }
        }
        displaced: Transition {
            NumberAnimation {
                property: "y"
                duration: 100
            }
        }
        remove: Transition {
            NumberAnimation {
                property: "x"
                to: page.width / 2
                duration: 50
            }
            NumberAnimation {
                property: "opacity"
                to: 0
                duration: 50
            }
        }

        Rectangle {
            id: todoModal
            width: listView.width
            height: Math.max(listView.height, parent.height)
            opacity: listView.currentIndex > -1 ? 0.2 : 0
            color: "black"
            visible: opacity > 0
            parent: listView.contentItem

            MouseArea {
                anchors.fill: parent
                onPressed: closeSelectedTodo()
            }

            Behavior on opacity {
                NumberAnimation {
                    duration: 100
                }
            }
        }
    }

    ColorPickerModal {
        id: colorModal
        pushBackContent: navigation
    }
}
