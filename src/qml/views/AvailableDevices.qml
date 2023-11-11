import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import "../controls"

Item {
    id: root

    property real selectedScreenIndex: -1
    property real selectedWindowIndex: -1


    SideBar {
        id: sideBar
    }

    CastWindow{
        anchors.left: sideBar.right
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.leftMargin: 10
    }
}
