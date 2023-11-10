import QtQuick

Item {
    id: root
    width: 200
    implicitHeight: 100
    height: container.height

    property string name
    property string dims
    property real dpi

    Rectangle {
        id: container
        width: 180
        height: contentCol.height + 20
        color: 'lightgrey'
        radius: 8
        anchors.centerIn: parent

        Column {
            id: contentCol
            spacing: 5
            anchors.centerIn: parent

            Text {
                font.bold: true
                font.pixelSize: 12
                width: 170; elide: Text.ElideRight
                text: root.name
                anchors.horizontalCenter: parent.horizontalCenter
            }

            Item {
                width: 170
                implicitHeight: 20

                Text {
                    font.pixelSize: 10
                    text: root.dims
                    anchors.left: parent.left
                    anchors.verticalCenter: parent.verticalCenter
                }

                Text {
                    text: root.dpi + ' dpi'
                    font.pixelSize: 10
                    font.italic: true
                    anchors.right: parent.right
                    anchors.rightMargin: 10
                    anchors.verticalCenter: parent.verticalCenter
                }
            }
        }
    }
}
