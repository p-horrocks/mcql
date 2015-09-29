import QtQuick          2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts  1.1
import app.mcql         1.0

FocusScope
{
    Layout.fillWidth:  true
    Layout.fillHeight: true

    property string importWorld: null
    property var nextPage:       statusPage

    Connections
    {
        target:        rootWindow
        onNextClicked: {
            var name = McqlUtil.genWorldName(worldName.text)
            McqlUtil.importWorld(importWorld, name)
            McqlUtil.initialiseWorld(name, worldType.currentIndex, difficulty.currentIndex, pvp.currentIndex)
            rootWindow.worldName = name
        }
    }

    GridLayout
    {
        anchors.fill: parent
        columns:      2

        Text
        {
            Layout.columnSpan: 2
            text:              "Save Game To Use"
            font.pointSize:    16
        }

        Rectangle
        {
            Layout.fillWidth:  true
            Layout.fillHeight: true
            Layout.columnSpan: 2
            radius:            4
            color:             "white"
            border.color:      "gray"

            ListView
            {
                id:              worldList
                anchors.fill:    parent
                anchors.margins: 4
                model:           McqlUtil.importableWorlds()
                delegate:        Text {
                    anchors.left:  parent.left
                    anchors.right: parent.right
                    text:          modelData
                }
                focus:           true
                highlight:       Rectangle { anchors.left: parent.left; anchors.right: parent.right; color: "lightsteelblue"; radius: 5 }

                onCurrentItemChanged: importWorld = currentItem.text
            }
        }

        Text
        {
            Layout.columnSpan: 2
            text:              "World Settings"
            font.pointSize:    16
        }

        Text
        {
            text: "Name"
        }

        Rectangle
        {
            Layout.fillWidth: true
            height:           childrenRect.height + 6
            color:            "white"
            radius:           4
            border.width:     1
            border.color:     "black"

            TextInput
            {
                id:                   worldName
                y:                    3
                anchors.left:         parent.left
                anchors.right:        parent.right
                anchors.leftMargin:   4
                anchors.rightMargin:  4
                focus:                true
            }
        }

        Text
        {
            text: "Type"
        }

        ComboBox
        {
            id:               worldType
            Layout.fillWidth: true
            model:            ["Creative", "Survival"]
        }

        Text
        {
            text: "Difficulty"
        }

        ComboBox
        {
            id:               difficulty
            Layout.fillWidth: true
            model:            ["Peaceful", "Easy", "Normal", "Hard"]
        }

        Text
        {
            text: "Hurt other players"
        }

        ComboBox
        {
            id:               pvp
            Layout.fillWidth: true
            model:            ["Yes", "No"]
        }
    }
}
