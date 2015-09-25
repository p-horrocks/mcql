import QtQuick          2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts  1.1

ColumnLayout
{
    anchors.fill: parent

    GroupBox
    {
        Layout.fillWidth: true
        title:            qsTr("Server")
        flat:             false

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
                text: "open"
            }

            Button
            {
                text: "new"
            }

            Button
            {
                text: "import"
            }
        }
    }

    GroupBox
    {
        Layout.fillWidth:  true
        Layout.fillHeight: true
        title:             qsTr("Players")
        flat:              false
    }
}
