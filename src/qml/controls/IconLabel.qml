import QtQuick
import QtQuick.Controls
import "../Icon.js" as MtlIcons

Label {
    id: root

    property real size: 16
    property string icon: '\uf0B56'

    Component.onCompleted: console.log(materialRegularFontLoader.name, iconSet.abc)

    font.pixelSize: size
    text: icon
    font.family: "Material Design Icons"
}
