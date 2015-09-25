import QtQuick          2.4
import QtQuick.Controls 1.3
import QtQuick.Window   2.2
import QtQuick.Dialogs  1.2
import QtQuick.Layouts  1.1

ApplicationWindow
{
    title:   qsTr("Minecraft QML Launcher")
    width:   640
    height:  480
    visible: true

    Component
    {
        id: newWorldPage

        NewWorldPage {}
    }

    StackView
    {
        id:              pageStack
        anchors.fill:    parent
        anchors.margins: 10
        focus:           true
        initialItem:     StatusPage {}
    }
}
