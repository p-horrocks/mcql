import QtQuick          2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts  1.1
import app.mcql         1.0

FocusScope
{
    Layout.fillWidth:  true
    Layout.fillHeight: true
    focus:             true

    property var nextPage: statusPage

    Connections
    {
        target:        rootWindow
        onNextClicked: {
            var name = McqlUtil.genWorldName(worldName.text)
            McqlUtil.initialiseWorld(
                        name,
                        worldType.currentIndex,
                        difficulty.value,
                        pvp.currentIndex
                        )
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

        GamemodeCombo
        {
            id:               worldType
            Layout.fillWidth: true
            value:            McqlUtil.Survival
        }

        Text
        {
            text: "Difficulty"
        }

        DifficultyCombo
        {
            id:               difficulty
            Layout.fillWidth: true
            value:            McqlUtil.Normal
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

        Item
        {
            Layout.fillHeight: true
            Layout.columnSpan: 2
        }
    }
}
