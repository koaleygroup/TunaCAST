import QtQuick
import QtQuick.Controls

Label {
    id: root

    property real size: 16
    property string icon: ''

    font.pixelSize: size
    text: icon
    font.family: materialRegularFontLoader.name
}
