import QtQuick 2.0
import QtQuick.Controls 2.12

import Felgo 3.0

import "../components"

Page {
    id: page
    title: qsTr("Todo List")

    AppListView {
        anchors.fill: parent
        model: mainController.todoController.todoModel
        delegate: TodoDelegate {
            text: display
        }
    }
}
