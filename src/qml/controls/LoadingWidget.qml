import QtQuick 2.15

Item
{
    id: root

    property bool isActive: false
    property alias label: txt

    BusyWidget {
        id: bw
        anchors.centerIn: parent
        isRunning: isActive
    }

    Text {
        id: txt
        text: qsTr("Loading client devices ...")
        anchors.horizontalCenter: parent.horizontalCenter
        font.bold: true
        font.pixelSize: 15
        anchors.top: bw.bottom
        color: blueColor
    }
}
