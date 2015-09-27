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
            text:             "Start A New World"
            onClicked:        pageStack.push(newWorldPage)
        }

        BigButton
        {
            Layout.alignment: Qt.AlignHCenter
            text:             "Start An Old World"
            onClicked:        pageStack.push(openWorldPage)
        }

        BigButton
        {
            Layout.alignment: Qt.AlignHCenter
            text:             "Create World From Saved Game"
            onClicked:        pageStack.push(saveGamePage)
        }

        Item { Layout.fillHeight: true }

        Button
        {
            Layout.alignment: Qt.AlignLeft
            text:             "Back"
            onClicked:        pageStack.pop()
        }
    }
}
