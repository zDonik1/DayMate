import QtQuick 2.0

import Felgo 3.0

Item {
    property alias text: appText.text

    property int verticalMargins: dp(20)
    property int spacing: dp(15)

    anchors {
        horizontalCenter: parent.horizontalCenter
        horizontalCenterOffset: -dp(4)
    }
    height: background.height + spacing
    width: parent.width * 0.9

    StylizedBackground {
        id: background
        anchors.centerIn: parent
        height: appText.contentHeight + verticalMargins * 2
        width: parent.width
    }

    AppText {
        id: appText
        anchors {
            left: parent.left
            leftMargin: parent.width * 0.075
            right: buttons.left
            verticalCenter: parent.verticalCenter
            verticalCenterOffset: dp(4)
        }
        font.pixelSize: sp(22)
        wrapMode: Text.Wrap
    }

    Row {
        id: buttons
        anchors.right: parent.right
        height: parent.height
        spacing: -height * 0.3

        IconButton {
            icon: IconType.check
            height: parent.height
            width: dp(50)
            color: Qt.lighter("green")
            size: sp(20)

            onClicked: logic.removeTodo(index)
        }
    }
}
