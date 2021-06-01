import Felgo 3.0
import QtQuick 2.0

Page {
    id: page
    title: qsTr("Todo List")

    AppListView {
        anchors.fill: parent
//        model: listModel
        delegate: SimpleRow {
            text: qsTr("some todo")
        }
    }
}
