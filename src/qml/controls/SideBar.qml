import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import com.koaleygroup.models

Item {
    id: devicesWidget
    anchors.top: parent.top
    anchors.bottom: parent.bottom
    anchors.left: parent.left
    width: 200

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
        anchors.margins: 10
        currentIndex: cb.currentIndex

        ListView {
            id: devicesLv
            clip: true
            model: ScreenListModel{}
            spacing: 10
            delegate: AvailableScreensDelegate {
                name: model.label ? model.label : 'Screen ' + (index+1).toString()
                dims: `${model.width} x ${model.height}`
                dpi: model.dpi

                onClicked: selected = !selected
            }
        }

        ListView {
            id: windowsLv
            clip: true
            model: WindowListModel{}
            spacing: 10
            delegate: AvailableWindowsDelegate {
                name: model.label ? model.label : 'Screen ' + (index+1).toString()
                dims: `${model.width} x ${model.height}`
                dpi: model.dpi
            }
        }
    }

}
