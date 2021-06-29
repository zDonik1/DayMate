import QtQuick 2.0

import Felgo 3.0

AppModal {
    id: root

    fullscreen: false
    backgroundColor: Theme.secondaryBackgroundColor
    modalHeight: dp(200)

    AppText {
        id: titleText
        anchors {
            top: parent.top
            topMargin: dp(20)
            horizontalCenter: parent.horizontalCenter
        }
        text: qsTr("Pick Color Group")
        font.pixelSize: sp(20)
        font.bold: true
    }

    Row {
        anchors {
            horizontalCenter: parent.horizontalCenter
            top: titleText.bottom
            topMargin: dp(10)
        }

        Repeater {
            model: mainController.todoController.fullColorModel
            delegate: ColorButton {
                width: dp(48)
                height: width
                color: display
                source: statusTip ? selectedSource : defaultSource

                onClicked: {
                    logic.editTodoColor(listView.currentIndex, index)
                    root.close()
                    listView.currentIndex = -1
                }
            }
        }
    }
}
