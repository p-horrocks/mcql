import QtQuick          2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts  1.1

FocusScope
{
    Layout.fillWidth:  true
    Layout.fillHeight: true

    property var nextPage: openWorldPage

    ColumnLayout
    {
        anchors.fill: parent

        BigButton
        {
            text:    "Start A New World"
            ourPage: newWorldPage
        }

        BigButton
        {
            text:    "Start An Old World"
            ourPage: openWorldPage
        }

        BigButton
        {
            text:    "Create New World From Saved Game"
            ourPage: importWorldPage
        }
    }
}
