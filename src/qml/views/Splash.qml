import QtQuick 2.15
import "../controls"

Item {
    id: root

    Timer {
        interval: 500
        running: true
        onTriggered: {
            bw.isRunning = false
            appStack.push("qrc:/TunaCastApp/src/qml/views/AvailableDevices.qml")
        }
    }

    BusyWidget {
        id: bw
        anchors.centerIn: parent
        isRunning: true
    }

    Text {
        text: qsTr("TunaCAST is loading ...")
        anchors.horizontalCenter: parent.horizontalCenter
        font.bold: true
        font.pixelSize: 15
        anchors.top: bw.bottom
        color: blueColor
    }
}
