import QtQuick 2.0

import Felgo 3.0

Item {
    property alias text: appText.text

    height: dp(50)
    width: parent.width

    AppText {
        id: appText
        anchors {
            left: parent.left
            leftMargin: dp(20)
            verticalCenter: parent.verticalCenter
        }
    }

    Row {
        anchors.right: parent.right
        height: parent.height
        spacing: -height * 0.3

        IconButton {
            icon: IconType.pencil
            height: parent.height
            width: height
            color: Qt.lighter("orange")
            size: sp(20)

            onClicked: helper.openEditTodoDialog(index, text)
        }

        IconButton {
            icon: IconType.trash
            height: parent.height
            width: height
            color: Qt.lighter("red")
            size: sp(20)

            onClicked: logic.removeTodo(index)
        }
    }
}
