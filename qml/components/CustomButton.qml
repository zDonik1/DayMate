import QtQuick 2.15

import Felgo 3.0

IconButtonBarItem {
    property alias visualComponent: loader.sourceComponent
    property alias visualItem: loader.item

    id: root

    Loader {
        id: loader
        anchors.centerIn: parent
        width: dp(28)
        height: width
    }
}
