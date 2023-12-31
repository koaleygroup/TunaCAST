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

        Item {
            anchors.top: parent.top
            anchors.bottom: bottomBar.top
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.margins: 10

            VideoCaptureProvider {
                id: frameProvider
                videoSink: videoOutput.videoSink
                castState: QmlInterface.isCapturing ?
                               QmlInterface.captureSource===0 ?
                                   VideoCaptureProvider.ScreenMode : VideoCaptureProvider.WindowMode :
                                   VideoCaptureProvider.StandbyMode
            }

            VideoOutput {
                id: videoOutput
                anchors.fill: parent
                fillMode: VideoOutput.PreserveAspectFit

                Component.onCompleted: frameProvider.init(QmlInterface)
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
                    visible: QmlInterface.isCapturing
                    enabled: QmlInterface.isCapturing
                    backgroundColor: 'red'; height: 40
                    text: qsTr('Stop Cast')
                    anchors.verticalCenter: parent.verticalCenter

                    onClicked: QmlInterface.stopCapture()
                }

                CastButton {
                    id: startCastBtn
                    visible: !QmlInterface.isCapturing
                    enabled: !QmlInterface.isCapturing
                    height: 40
                    anchors.verticalCenter: parent.verticalCenter

                    onClicked: QmlInterface.startCapture(QmlInterface.sourceType===0 ? selectedScreenIndex : selectedWindowIndex)
                }
            }
        }
    }
}
