import QtQuick 2.15
import QtGraphicalEffects 1.0

import Felgo 3.0

Item {
    function open () { visible = true }
    function close () { visible = false }

    property int verticalMargins: dp(20)

    anchors.centerIn: parent
    height: textEdit.contentHeight + verticalMargins * 2
    width: dp(300)
    visible: false

    // background press catches
    Item {
        anchors.centerIn: parent
        height: page.height
        width: page.width

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

    DropShadow {
        anchors.fill: card
        source: card

        radius: 15
        samples: 10
        verticalOffset: 5
        color: "black"
    }

    Canvas {
        property int radius: dp(50)
        property int lineWidth: dp(3)

        id: card
        visible: false
        anchors.centerIn: parent
        implicitHeight: parent.height + lineWidth * 2
        implicitWidth: parent.width + lineWidth * 2
        onPaint: {
            var ctx = getContext("2d")
            ctx.fillStyle = Theme.tintColor
            ctx.strokeStyle = Theme.textColor
            ctx.lineWidth = lineWidth

            // highlight
            ctx.beginPath()
            ctx.moveTo(lineWidth, height)
            ctx.lineTo(lineWidth, radius + lineWidth)
            ctx.arc(radius + lineWidth,
                    radius + lineWidth,
                    radius, Math.PI, Math.PI * 3/2, false)
            ctx.lineWidth = lineWidth
            ctx.lineTo(width, lineWidth)
            ctx.stroke()

            // rest of the background
            ctx.lineTo(width, height - radius)
            ctx.arc(width - radius,
                    height - radius,
                    radius, 0, Math.PI / 2, false)

            ctx.fill()
        }
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
