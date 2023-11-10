import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

Item {
    id: devicesWidget
    anchors.top: parent.top
    anchors.bottom: parent.bottom
    anchors.left: parent.left
    width: 200

    Connections {
        target: QmlInterface

        function onSourceTypeChanged() {
            console.log(QmlInterface.sourceType)
        }
    }

    Item {
        id: devicesBar
        height: 50
        anchors.top: parent.top
        width: parent.width

        ComboBox {
            id: cb
            model: ["Cast Screen", "Cast Window"]
            height: 30
            leftPadding: 10
            anchors.leftMargin: 10
            anchors.left: parent.left
            anchors.right: refreshBtn.left
            anchors.rightMargin: 10
            anchors.verticalCenter: parent.verticalCenter
            onCurrentIndexChanged: QmlInterface.sourceType = currentIndex
        }

        Rectangle {
            id: refreshBtn
            width: 24
            height: 24
            border.color: blueColor
            border.width: 1
            radius: 8
            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter
        }

        Rectangle {
            width: parent.width - 10; height: 2
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            color: 'lightgrey'
        }
    }

    StackLayout {
        id: screenOrWindowsStackLayout
        anchors.top: devicesBar.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        currentIndex: QmlInterface.sourceType
        anchors.leftMargin: 10
        anchors.topMargin: 10
        anchors.bottomMargin: 10

        ListView {
            id: devicesLv
            clip: true
            model: QmlInterface.getScreenListModel()
            spacing: 4
            width: parent.width
            delegate: AvailableScreensDelegate {
                width: devicesLv.width
                name: model.label ? model.label : 'Screen ' + (index+1).toString()
                dims: `${model.width} x ${model.height}`
                dpi: model.dpi
                selected: model.currentSelectedIndex===index

                onClicked: model.currentSelectedIndex=index

                Component.onCompleted: console.log('-- ', model.currentSelectedIndex)
            }
        }

        ListView {
            id: windowsLv
            clip: true
            model: QmlInterface.getWindowListModel()
            spacing: 4
            width: parent.width
            delegate: AvailableWindowsDelegate {
                width: devicesLv.width
                name: model.display
                selected: selectedWindowIndex===index

                onClicked: selectedWindowIndex=index
            }
        }
    }

}
