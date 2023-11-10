import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material

Button {
    id: btn
    implicitHeight: 30
    implicitWidth: 100
    width: r.width + 30
    height: 40
    text: "Start Cast"
    Material.theme: Material.Light

    property alias backgroundColor: rect.color
    property real buttonRadius: rect.radius

    background: Rectangle {
        id: rect
        color: 'green'
        radius: 16
        opacity: enabled ? 1 : 0.3

        Row {
            id: r
            anchors.centerIn: parent

            Text {
                id: lbl
                color: '#ddd'
                font.bold: true
                text: btn.text
                anchors.verticalCenter: parent.verticalCenter
            }
        }
    }

    contentItem: Item{}
}
