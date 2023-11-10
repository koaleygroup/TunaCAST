import QtQuick 2.15

Item {
    id: root
    implicitWidth: 100
    implicitHeight: 100

    property alias isRunning: aimg.playing

    AnimatedImage {
        id: aimg
        anchors.centerIn: parent
        source: "qrc:/TunaCastApp/src/assets/busy.gif"
        playing: false
        width: root.width < 100 ? root.width : 100
        height: width
    }
}
