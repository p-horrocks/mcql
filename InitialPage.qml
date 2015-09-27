import QtQuick          2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts  1.1

FocusScope
{
    Layout.fillWidth:  true
    Layout.fillHeight: true

    property var nextPage: startServerPage

    ColumnLayout
    {
        anchors.fill: parent

        BigButton
        {
            text:    "Start Minecraft"
            ourPage: startMinecraftPage
        }

        BigButton
        {
            text:    "Start Server"
            ourPage: startServerPage
        }
    }
}
