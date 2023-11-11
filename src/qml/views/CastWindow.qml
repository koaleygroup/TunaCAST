import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtMultimedia
import com.koaleygroup.multimedia

import "../controls"

Item {
    id: root

    property string currentTab: 'screen'

    Item {
        id: tabs
        anchors.top: parent.top
        width: parent.width
        height: 50

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
        color: '#ddd'

        Rectangle {
            anchors.top: parent.top
            anchors.bottom: bottomBar.top
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.margins: 10
            color: '#444'
            radius: 8

            VideoCaptureProvider {
                id: frameProvider
                videoSink: videoOutput.videoSink
            }

            VideoOutput {
                id: videoOutput
                anchors.fill: parent
                anchors.margins: 8
                fillMode: VideoOutput.PreserveAspectFit

                Component.onCompleted: frameProvider.start()
            }
        }

        Item {
            id: bottomBar
            height: 40
            width: parent.width - 20
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 5
            anchors.right: parent.right
            anchors.rightMargin: 10

            Row {
                spacing: 10
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right

                CastButton {
                    id: stopCastBtn
                    backgroundColor: 'red'
                    height: 40
                    text: qsTr('Stop Cast')
                    anchors.verticalCenter: parent.verticalCenter
                }

                CastButton {
                    id: startCastBtn
                    height: 40
                    anchors.verticalCenter: parent.verticalCenter
                }
            }
        }
    }
}
