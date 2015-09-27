import QtQuick          2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts  1.1

FocusScope
{
    Layout.fillWidth:  true
    Layout.fillHeight: true

    ColumnLayout
    {
        anchors.fill: parent

        BigButton
        {
            Layout.alignment: Qt.AlignHCenter
            text:             "Start Minecraft"
            onClicked:        pageStack.push(startMinecraftPage)
        }

        BigButton
        {
            Layout.alignment: Qt.AlignHCenter
            text:             "Start Server"
            onClicked:        pageStack.push(startServerPage)
        }

        Item { Layout.fillHeight: true }

        Button
        {
            Layout.alignment: Qt.AlignLeft
            text:             "Back"
            enabled:          false
        }
    }
}
