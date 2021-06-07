import QtQuick 2.15
import QtQuick.Controls 2.12

import Felgo 3.0

import "../components"

Page {
    function addTodo() {
        if (!listView.itemBeingAdded) {
            listView.itemBeingAdded = true
            logic.addTodo()
        }
    }

    id: page
    title: qsTr("Todo List")

    AppListView {
        property bool itemBeingAdded: false

        id: listView
        anchors.fill: parent
        model: mainController.todoController.todoModel
        spacing: -dp(5)
        currentIndex: -1
        boundsBehavior: Flickable.StopAtBounds
        scrollIndicatorVisible: true
        delegate: TodoDelegate {
            text: display
            selected: ListView.isCurrentItem
        }

        Rectangle {
            width: listView.width
            height: Math.max(listView.height, parent.height)
            opacity: 0.2
            color: "black"
            visible: listView.currentIndex > -1
            parent: listView.contentItem

            MouseArea {
                anchors.fill: parent
                onPressed: {
                    if (listView.itemBeingAdded) {
                        listView.currentItem.finalizeAdd()
                        listView.itemBeingAdded = false
                    } else {
                        listView.currentItem.deselect()
                    }
                    listView.currentIndex = -1
                }
            }
        }
    }
}
