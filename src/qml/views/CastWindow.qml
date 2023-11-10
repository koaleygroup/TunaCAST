import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
    id: root

    property string currentTab: 'screen'

    Item {
        id: tabs
        anchors.top: parent.top
        width: parent.width
        height: 40

        Row {
            anchors.verticalCenter: parent.verticalCenter
            spacing: 5

            Rectangle {
                height: 40
                radius: 0
                width: r1.width
                color: currentTab !=='window' ? '#ddd' : '#fff'

                Row {
                    id: r1
                    anchors.verticalCenter: parent.verticalCenter

                    Text {
                        text: qsTr("Screen")
                        anchors.verticalCenter: parent.verticalCenter
                        leftPadding: 10
                        rightPadding: 10
                    }
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: currentTab = 'screen'
                }
            }

            Rectangle {
                height: 40
                radius: 0
                width: r2.width
                color: currentTab ==='window' ? '#ddd' : '#fff'


                Row {
                    id: r2
                    anchors.verticalCenter: parent.verticalCenter

                    Text {
                        text: qsTr("Window")
                        anchors.verticalCenter: parent.verticalCenter
                        leftPadding: 10
                        rightPadding: 10
                    }
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: currentTab = 'window'
                }
            }
        }
    }

    Rectangle {
        anchors.top: tabs.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.bottomMargin: 10
        color: '#ddd'

        StackLayout {
            anchors.fill: parent

            Item {
                id: homeTab
            }

            Item {
                id: discoverTab
            }
        }
    }
}
