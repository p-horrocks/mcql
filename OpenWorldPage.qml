import QtQuick          2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts  1.1
import app.mcql         1.0

FocusScope
{
    Layout.fillWidth:  true
    Layout.fillHeight: true
    focus:             true

    ColumnLayout
    {
        anchors.fill: parent

        Text
        {
            text:           "Choose The World To Use"
            font.pointSize: 16
        }

        Rectangle
        {
            Layout.fillWidth:  true
            Layout.fillHeight: true
            radius:            4
            color:             "white"
            border.color:      "gray"

            ListView
            {
                anchors.fill:    parent
                anchors.margins: 4
                model:           McqlUtil.availableWorlds()
                delegate:        Text { anchors.left: parent.left; anchors.right: parent.right; text: modelData }
                focus:           true
                highlight:       Rectangle { anchors.left: parent.left; anchors.right: parent.right; color: "lightsteelblue"; radius: 5 }
            }
        }

        Button
        {
            Layout.alignment: Qt.AlignLeft
            text:             "Back"
            onClicked:        pageStack.pop()
        }

        Button
        {
            Layout.alignment: Qt.AlignRight
            text:             "Start Server"
            onClicked:        pageStack.push(statusPage)
        }
    }
}
