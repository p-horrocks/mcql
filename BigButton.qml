import QtQuick                 2.4
import QtQuick.Layouts  1.1

Rectangle
{
    Layout.fillWidth:  true
    Layout.fillHeight: true
    color:             (nextPage === ourPage) ? "blue" : "white"
    radius:            4
    border.color:      "black"

    property var ourPage: null
    property alias text:  label.text

    Text
    {
        id:               label
        anchors.centerIn: parent
        text:             "Start Minecraft"
    }

    MouseArea
    {
        anchors.fill: parent
        onClicked:    nextPage = ourPage
    }
}
