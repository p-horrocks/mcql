import QtQuick          2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts  1.1
import app.mcql         1.0

FocusScope
{
    Layout.fillWidth:  true
    Layout.fillHeight: true

    ServerLink
    {
        onOutput: serverOutput.append(text)
    }

    ColumnLayout
    {
        anchors.fill: parent

        Text
        {
            text:           "World Name"
            font.pointSize: 16
        }

        Text
        {
            text: rootWindow.worldName
        }

        Text
        {
            text:           "Settings"
            font.pointSize: 16
        }

        Text
        {
            text:           "Players"
            font.pointSize: 16
        }

        Text
        {
            text:           "Server Output"
            font.pointSize: 16
        }

        Rectangle
        {
            Layout.fillWidth:  true
            Layout.fillHeight: true
            color:             "white"
            radius:            4
            border.color:      "black"

            TextEdit
            {
                id:              serverOutput
                anchors.fill:    parent
                anchors.margins: 4
                readOnly:        true
            }
        }
    }
}
