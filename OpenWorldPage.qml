import QtQuick          2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts  1.1
import app.mcql         1.0

FocusScope
{
    Layout.fillWidth:  true
    Layout.fillHeight: true

    property var nextPage: statusPage

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
            clip:              true

            ListView
            {
                id:              worldList
                anchors.fill:    parent
                anchors.margins: 4
                model:           McqlUtil.availableWorlds()
                highlightFollowsCurrentItem: true
                delegate:        Text {
                    anchors.left:  parent.left
                    anchors.right: parent.right
                    text:          modelData

                    function select()
                    {
                        ListView.view.currentIndex = index
                    }

                    MouseArea
                    {
                        anchors.fill: parent
                        onClicked:    select()
                    }
                }
                focus:           true
                highlight:       Rectangle { anchors.left: parent.left; anchors.right: parent.right; color: "lightsteelblue"; radius: 5 }

                onCurrentItemChanged: rootWindow.worldName = currentItem.text
            }
        }
    }
}
