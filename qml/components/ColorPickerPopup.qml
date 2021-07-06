import QtQuick 2.0
import QtQuick.Controls 2.12

import Felgo 3.0

Popup {
    id: root
    width: column.width
    height: column.height
    background: StylizedBackground {
        anchors.fill: parent
        background.color: Theme.secondaryBackgroundColor
        elevated: true
    }

    enter: Transition {
        NumberAnimation {
            property: "opacity"
            from: 0
            to: 1
            duration: 100
            easing.type: Easing.InOutQuad
        }

        NumberAnimation {
            property: "height"
            from: column.height / 2
            to: column.height
            duration: 100
            easing.type: Easing.InOutQuad
        }
    }

    exit: Transition {
        NumberAnimation {
            property: "opacity"
            from: 1
            to: 0
            duration: 100
            easing.type: Easing.InOutQuad
        }

        NumberAnimation {
            property: "height"
            from: column.height
            to: column.height / 2
            duration: 100
            easing.type: Easing.InOutQuad
        }
    }

    Column {
        id: column
        anchors.centerIn: parent
        height: repeater.count * dp(45)

        Repeater {
            id: repeater
            model: mainController.todoController.activeColorModel
            delegate: ColorButton {
                width: dp(45)
                height: width
                color: display
                source: decoration
                        ? Qt.resolvedUrl("../../assets/four_colors.png")
                        : statusTip ? selectedSource : defaultSource

                onClicked: {
                    logic.selectColorGroup(index)
                    todoListPage.closeSelectedTodo()
                    root.close()
                }
            }
        }
    }
}
