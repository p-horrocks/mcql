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

        GroupBox
        {
            Layout.fillWidth:  true
            Layout.fillHeight: true
            title:             qsTr("World Settings")

            GridLayout
            {
                anchors.fill: parent
                columns:      2

                Text     { text: qsTr("Name") }
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

                Text     { text: qsTr("Type") }
                ComboBox { id: worldType; Layout.fillWidth: true; model: [qsTr("Creative"), qsTr("Survival")] }

                Text     { text: qsTr("Difficulty") }
                ComboBox { id: difficulty; Layout.fillWidth: true; model: [qsTr("Peaceful"), qsTr("Easy"), qsTr("Normal"), qsTr("Hard")] }

                Text     { text: qsTr("Hurting") }
                ComboBox { id: hurting; Layout.fillWidth: true; model: [qsTr("Yes"), qsTr("No")] }

                Item
                {
                    Layout.fillHeight: true
                    width:             1
                }
            }
        }

        RowLayout
        {
            Layout.fillWidth: true

            Item
            {
                Layout.fillWidth: true
            }

            Button
            {
                text:      qsTr("Create & Start")
                onClicked:
                {
                    McqlUtil.initialiseWorld(worldName.text, worldType.currentText, difficulty.currentIndex, hurting.currentIndex)
                    pageStack.pop()
                }
            }

            Button
            {
                text:      qsTr("Exit")
                onClicked: pageStack.pop()
            }
        }
    }
}
