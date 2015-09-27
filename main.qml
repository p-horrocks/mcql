import QtQuick                 2.4
import QtQuick.Controls        1.3
import QtQuick.Controls.Styles 1.4
import QtQuick.Window          2.2

ApplicationWindow
{
    title:   qsTr("Minecraft QML Launcher")
    width:   640
    height:  480
    visible: true

    Component
    {
        id:    bigButton
        ButtonStyle
        {
            label: Text {
                text:           (control === null) ? "" : control.text
                font.pointSize: 16
            }
        }
    }

    Component
    {
        id: startMinecraftPage

        NewWorldPage {}
    }

    Component
    {
        id: startServerPage

        StartServerPage {}
    }

    Component
    {
        id: newWorldPage

        NewWorldPage {}
    }

    Component
    {
        id: openWorldPage

        OpenWorldPage {}
    }

    Component
    {
        id: statusPage

        StatusPage {}
    }

    StackView
    {
        id:              pageStack
        anchors.fill:    parent
        anchors.margins: 10
        focus:           true
        initialItem:     InitialPage {}
    }
}
