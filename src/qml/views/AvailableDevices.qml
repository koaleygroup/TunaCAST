import QtQuick
import QtQuick.Controls
import com.koaleygroup.models
import QtQuick.Layouts

import "../controls"

Item {
    id: root

    property bool searchingClients: !true

    Rectangle {
        id: topBar
        anchors.top: parent.top
        height: 50
        width: parent.width
        color: blueColor
    }

    Item {
        anchors.top: topBar.bottom
        anchors.bottom: parent.bottom
        width: parent.width

        SideBar {}

        StackView {
            id: castStack
            anchors.left: devicesWidget.right
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.leftMargin: 10
            initialItem: CastWindow{}
        }
    }
}
