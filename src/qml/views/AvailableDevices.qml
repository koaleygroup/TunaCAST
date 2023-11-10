import QtQuick
import QtQuick.Controls
import com.koaleygroup.models
import QtQuick.Layouts

import "../controls"

Item {
    id: root

    property bool searchingClients: !true
    property real selectedScreenIndex: -1
    property real selectedWindowIndex: -1


    SideBar {
        id: sideBar
    }

    StackView {
        id: castStack
        anchors.left: sideBar.right
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.leftMargin: 10
        initialItem: CastWindow{}
    }
}
