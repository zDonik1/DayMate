import QtQuick 2.0
import QtGraphicalEffects 1.0

import Felgo 3.0

Item {
    property int radius: dp(30)
    property int lineWidth: dp(3)
    property int elevation: 1

    id: root

    DropShadow {
        anchors.fill: canvas
        source: canvas

        radius: 3 * elevation
        samples: 2 * elevation
        verticalOffset: 5
        color: "black"
    }

    Canvas {
        id: canvas
        visible: false
        implicitHeight: parent.height + lineWidth * 2
        implicitWidth: parent.width + lineWidth * 2
        onPaint: {
            var ctx = getContext("2d")
            ctx.fillStyle = Theme.secondaryBackgroundColor
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
}
