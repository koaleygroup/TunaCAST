import QtQuick

Rectangle {
    id: root
    implicitHeight: 100
    implicitWidth: 200
    height: contentCol.height + 20
    color: selected ? blueColor : 'lightgrey'

    property string name
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

        Item {
            width: parent.width
            implicitHeight: 50

            Item {
                id: rc
                height: 48; width: 48
                anchors.left: parent.left
                anchors.verticalCenter: parent.verticalCenter

                ImageIcon {
                    height: 48
                    width: 48
                    source: "qrc:/TunaCastApp/src/assets/svg/window.svg"
                    anchors.centerIn: parent
                    color: selected ? '#eee' : 'darkgrey'
                }
            }

            Text {
                color: selected ? '#eee' : '#444'
                text: root.name
                font.pixelSize: 10
                font.bold: selected
                anchors.left: rc.right
                anchors.right: parent.right
                anchors.rightMargin: 10
                anchors.leftMargin: 10
                anchors.verticalCenter: parent.verticalCenter
                wrapMode: Text.WordWrap
            }
        }
    }

    MouseArea {
        anchors.fill: parent
        onClicked: root.clicked()
    }
}
