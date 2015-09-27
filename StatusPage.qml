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
//        onOutput:
    }

    ColumnLayout
    {
        anchors.fill: parent

        GroupBox
        {
            Layout.fillWidth: true
            title:            qsTr("Server")

            RowLayout
            {
                anchors.fill: parent

                Text
                {
                    text: qsTr("World:")
                }

                Text
                {
                    Layout.fillWidth: true
                }

                Button
                {
                    text:      "open"
                    onClicked: pageStack.push(openWorldPage)
                }

                Button
                {
                    text:      "new"
                    onClicked: pageStack.push(newWorldPage)
                }
            }
        }

        GroupBox
        {
            Layout.fillWidth:  true
            Layout.fillHeight: true
            title:             qsTr("Players")
        }

        GroupBox
        {
            Layout.fillWidth:  true
            Layout.fillHeight: true
            title:             qsTr("Output")

            TextEdit
            {
                anchors.fill: parent
            }
        }
    }
}
