import QtQuick
import QtQuick.Controls
import Qt5Compat.GraphicalEffects

Item {
    id: root
    implicitHeight: 48
    implicitWidth: 48

    property color color: blueColor
    property alias source: img.source

    Image {
        id: img
        height: parent.height
        width: parent.width
        antialiasing: true
        smooth: true
        visible: false
        fillMode: Image.PreserveAspectFit
    }

    ColorOverlay {
        anchors.fill: img
        source: img
        color: root.color
    }
}
