import QtQuick                 2.4
import QtQuick.Controls        1.3
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts         1.1
import QtQuick.Window          2.2

ApplicationWindow
{
    id:      rootWindow
    title:   qsTr("Minecraft QML Launcher")
    width:   640
    height:  480
    visible: true

    property string worldName

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

    GridLayout
    {
        anchors.fill:    parent
        anchors.margins: 10
        columns:         2

        StackView
        {
            id:                pageStack
            Layout.fillWidth:  true
            Layout.fillHeight: true
            Layout.columnSpan: 2
            focus:             true
            initialItem:       InitialPage {}
        }

        Rectangle
        {
            Layout.fillWidth:  true
            Layout.columnSpan: 2
            height:            1
            color:             "black"
        }

        Button
        {
            text:      "Back"
            onClicked: pageStack.pop()
            enabled:   (pageStack.depth > 1)
        }

        Button
        {
            Layout.alignment: Qt.AlignRight
            text:             "Next"
            enabled:          (pageStack.currentItem !== null) && (pageStack.currentItem.nextPage !== undefined) && (pageStack.currentItem.nextPage !== null)
            onClicked:        pageStack.push(pageStack.currentItem.nextPage)
        }
    }
}
