import QtQuick 2.15
import QtQuick.Controls 2.12
import QtQml.Models 2.12

import Felgo 3.0

import "../components"

Page {
    function addTodo() {
        if (!listView.itemBeingAdded) {
            listView.itemBeingAdded = true
            logic.addTodo()
        }
    }

    property alias listView: listView

    id: page
    title: qsTr("Todo List")

    DelegateModel {
        id: todoDelegateModel
        model: mainController.todoController.todoModel
        delegate: TodoDelegate {
            text: display
            selected: ListView.isCurrentItem
            itemsIndex: DelegateModel.itemsIndex
        }
    }

    AppListView {
        property bool firstTime: true
        property bool itemBeingAdded: false

        id: listView
        anchors.fill: parent
        spacing: -dp(5)
        model: todoDelegateModel
        currentIndex: -1
        boundsBehavior: Flickable.StopAtBounds
        scrollIndicatorVisible: true

        // DelegateModel uses "add" mechanic to setup model, so last element is "selected"
        onCurrentIndexChanged: if (firstTime && currentIndex === count - 1) {
                                   firstTime = false
                                   currentIndex = -1
                               }

        // transitions
        add: Transition {
            NumberAnimation {
                properties: "x"
                from: page.width
                duration: 100
            }
        }
        displaced: Transition {
            NumberAnimation {
                properties: "y"
                duration: 100
            }
        }
        remove: Transition {
            NumberAnimation {
                properties: "x"
                to: page.width
                duration: 50
            }
        }

        Rectangle {
            width: listView.width
            height: Math.max(listView.height, parent.height)
            opacity: listView.currentIndex > -1 ? 0.2 : 0
            color: "black"
            visible: opacity > 0
            parent: listView.contentItem

            MouseArea {
                anchors.fill: parent
                onPressed: {
                    listView.itemBeingAdded = false
                    listView.currentItem.onDeselected()
                    listView.currentIndex = -1
                }
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
