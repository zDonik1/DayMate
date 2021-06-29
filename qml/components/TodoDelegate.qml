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
    width: listView.width * 0.9
    x: (listView.width - width) / 2
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
        height: appTextEdit.height + verticalMargins * 2
        width: parent.width
        elevated: selected
        background.color: decoration
    }

    MouseArea {
        anchors.fill: parent

        onClicked: listView.currentIndex = index
    }

    AppTextEdit {
        id: appTextEdit
        anchors {
            left: parent.left
            leftMargin: parent.width * 0.05
            right: buttonRow.left
            rightMargin: buttonRow.visible ? 0 : parent.width * 0.05
            verticalCenter: parent.verticalCenter
        }
        height: contentHeight
        font.pixelSize: sp(22)
        wrapMode: Text.Wrap
        color: Theme.backgroundColor
        placeholderText: qsTr("Write todo here...")
        placeholderColor: Theme.secondaryTextColor
        enabled: selected
    }

    Row {
        property real __originalWidth

        id: buttonRow
        anchors {
            right: parent.right
            verticalCenter: parent.verticalCenter
        }
        visible: width > 0
        spacing: -dp(10)

        Component.onCompleted: {
            __originalWidth = width
            width = Qt.binding(function() {
                return selected && !appTextEdit.activeFocus ? __originalWidth : 0
            })
        }

        ColorButton {
            width: dp(48)
            height: width
            source: Qt.resolvedUrl("../../assets/four_colors.png")

            onClicked: {
                logic.setColorInColorPicker(decoration)
                colorModal.open()
            }
        }

        CustomIconButton {
            width: dp(48)
            height: width
            icon: IconType.check
            color: mainController.todoController.fullColorModel.colorIndex(decoration) === 0
                   || mainController.todoController.fullColorModel.colorIndex(decoration) === 1
                   || mainController.todoController.fullColorModel.colorIndex(decoration) === 3
                   ? Qt.lighter("green") : "green"
            size: sp(20)

            onClicked: {
                listView.currentIndex = -1
                logic.removeTodo(index)
            }
        }
    }
}
