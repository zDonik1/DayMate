import QtQuick 2.15

import Felgo 3.0

FocusScope {
    function onDeselected() {
        appTextEdit.focus = false
        if (appTextEdit.text === "") {
            logic.removeTodo(index)
        } else {
            logic.editTodo(index, appTextEdit.text)
        }
    }

    property bool selected: false
    property alias text: appTextEdit.text
    property int verticalMargins: dp(20)
    property int spacing: dp(15)

    id: root
    height: background.height + spacing
    width: parent.width * 0.9
    x: (parent.width - width) / 2
    z: selected ? 1 : -1
    scale: selected ? 1.03 : 1

    ListView.onAdd: {
        appTextEdit.forceActiveFocus()
        Qt.callLater(function () { listView.currentIndex = index })
    }

    Behavior on scale {
        NumberAnimation {
            duration: 100
        }
    }

    StylizedBackground {
        id: background
        anchors.centerIn: parent
        height: appTextEdit.contentHeight + verticalMargins * 2
        width: parent.width
        elevated: selected
    }

    MouseArea {
        anchors.fill: parent

        onClicked: listView.currentIndex = index
    }

    AppTextEdit {
        id: appTextEdit
        anchors {
            left: parent.left
            leftMargin: parent.width * 0.075
            right: button.left
            rightMargin: button.visible ? 0 : parent.width * 0.075
            verticalCenter: parent.verticalCenter
        }
        font.pixelSize: sp(22)
        wrapMode: Text.Wrap
        color: Theme.textColor
        placeholderText: qsTr("Write todo here...")
        placeholderColor: Theme.secondaryTextColor
        enabled: selected
    }

    AppButton {
        id: button
        anchors.right: parent.right
        icon: IconType.check
        height: parent.height
        width: selected && !appTextEdit.activeFocus ? dp(50) : 0
        visible: width > 0
        flat: true
        textColor: Qt.lighter("green")
        iconSize: sp(20)

        onClicked: {
            listView.currentIndex = -1
            logic.removeTodo(index)
        }
    }
}
