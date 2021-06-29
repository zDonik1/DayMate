import QtQuick 2.15

import Felgo 3.0

CustomButton {
    property string icon
    property real size: sp(20)
    property color color

    id: root

    visualComponent: Icon {
        icon: root.icon
        size: root.size
        color: root.color
    }
}
