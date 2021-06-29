import QtQuick 2.15
import QtGraphicalEffects 1.0

CustomButton {
    readonly property url defaultSource: Qt.resolvedUrl("../../assets/color_button.png")
    readonly property url selectedSource: Qt.resolvedUrl("../../assets/color_button_selected.png")

    property color color
    property url source: defaultSource

    property bool __isColoured: source === defaultSource || source === selectedSource

    id: root

    visualComponent: Item {
        Image {
            id: image
            width: parent.width
            height: parent.height
            source: root.source
            visible: !__isColoured
        }

        ColorOverlay {
            id: overlay
            anchors.fill: image
            source: image
            color: root.color
            visible: __isColoured
        }
    }
}
