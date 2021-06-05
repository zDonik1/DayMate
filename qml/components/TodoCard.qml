import QtQuick 2.15

import Felgo 3.0

Item {
    function open () { visible = true }
    function close () { visible = false }

    property int verticalMargins: dp(20)

    id: root
    anchors.centerIn: parent
    height: textEdit.contentHeight + verticalMargins * 2
    width: dp(300)
    visible: false

    // background press catches
    Item {
        anchors.centerIn: parent
        height: app.height
        width: app.width

        TapHandler {
            onTapped: {
                textEdit.focus = false
                if (textEdit.text !== "") {
                    logic.addTodo(textEdit.text)
                    textEdit.text = ""
                }
                close()
            }
        }
    }

    StylizedBackground {
        id: background
        anchors.centerIn: parent
        height: parent.height
        width: parent.width
    }

    AppTextEdit {
        id: textEdit
        anchors {
            centerIn: parent
            verticalCenterOffset: dp(2)
        }
        width: parent.width * 0.8
        wrapMode: TextEdit.Wrap
        color: Theme.textColor
        placeholderText: qsTr("Write todo here...")
        placeholderColor: Theme.secondaryTextColor
    }
}
