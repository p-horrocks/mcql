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

    signal nextClicked()

    onClosing: {
        if(typeof(pageStack.currentItem.running) === "boolean")
        {
            // The StatusPage must be active. If the server is running then
            // instead of closing straight away wait for the server to shutdown
            if(pageStack.currentItem.running)
            {
                pageStack.currentItem.stopServer()
                close.accepted = false
            }
        }
    }

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
        id: importWorldPage

        ImportWorldPage {}
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
            initialItem:       startServerPage
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
            onClicked: {
                rootWindow.nextClicked()
                pageStack.push(pageStack.currentItem.nextPage)
            }
        }
    }
}
