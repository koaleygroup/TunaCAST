import QtQuick 2.15

Rectangle {
    id: root
    implicitHeight: 100
    implicitWidth: 200
    height: contentCol.height + 20
    color: selected ? blueColor : 'lightgrey'

    property string name
    property string dims
    property real dpi
    property bool selected: false

    signal clicked

    Column {
        id: contentCol
        spacing: 5
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
        anchors.leftMargin: 10
        anchors.rightMargin: 10

        Text {
            font.bold: true
            font.pixelSize: 12
            width: contentCol.width
            elide: Text.ElideRight
            text: root.name
            color: selected ? '#fff' : '#444'
        }

        Item {
            width: contentCol.width
            implicitHeight: 20

            Text {
                color: selected ? '#fff' : '#444'
                font.pixelSize: 10
                text: root.dims
                anchors.left: parent.left
                anchors.verticalCenter: parent.verticalCenter
            }

            Text {
                color: selected ? '#fff' : '#444'
                text: root.dpi + ' dpi'
                font.pixelSize: 10
                font.italic: true
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
            }
        }
    }

    MouseArea {
        anchors.fill: parent
        onClicked: root.clicked()
    }
}
