import QtQuick          2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts  1.1
import app.mcql         1.0

FocusScope
{
    Layout.fillWidth:  true
    Layout.fillHeight: true

    property alias running:    serverLink.running
    property bool closeOnStop: false

    function stopServer()
    {
        closeOnStop = true
        serverLink.stopServer()
    }

    ServerLink
    {
        id:        serverLink
        worldName: rootWindow.worldName

        onOutput: {
            serverOutput.insert(serverOutput.length, text)
            serverOutput.cursorPosition = serverOutput.length
        }

        onRunningChanged: {
            if(!running && closeOnStop)
            {
                rootWindow.close()
            }
        }
    }

    ColumnLayout
    {
        anchors.fill: parent

        Text
        {
            text:           "World Name"
            font.pointSize: 16
        }

        Text
        {
            text: serverLink.worldName
        }

        Text
        {
            text:           "Settings"
            font.pointSize: 16
        }

        Text
        {
            text:           "Players"
            font.pointSize: 16
        }

        ListView
        {
            Layout.fillWidth:  true
            Layout.fillHeight: true
            model:             serverLink.playerList
            delegate:          Text { text: model.name }
        }

        Text
        {
            text:           "Server Output"
            font.pointSize: 16
        }

        Rectangle
        {
            Layout.fillWidth:  true
            Layout.fillHeight: true
            color:             "white"
            radius:            4
            border.color:      "black"

            Flickable
            {
                id:              textFlicker
                anchors.fill:    parent
                anchors.margins: 4
                contentWidth:    serverOutput.paintedWidth
                contentHeight:   serverOutput.paintedHeight
                clip:            true

                 function ensureVisible(r)
                 {
                     if (contentX >= r.x)
                         contentX = r.x;
                     else if (contentX+width <= r.x+r.width)
                         contentX = r.x+r.width-width;
                     if (contentY >= r.y)
                         contentY = r.y;
                     else if (contentY+height <= r.y+r.height)
                         contentY = r.y+r.height-height;
                 }

                TextEdit
                {
                    id:       serverOutput
                    width:    textFlicker.width
                    height:   textFlicker.height
                    focus:    true
                    wrapMode: TextEdit.Wrap
                    readOnly: true

                    onCursorRectangleChanged: textFlicker.ensureVisible(cursorRectangle)
                }
            }
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
                y:                    3
                anchors.left:         parent.left
                anchors.right:        parent.right
                anchors.leftMargin:   4
                anchors.rightMargin:  4
                focus:                true

                onAccepted: {
                    serverLink.sendInput(text)
                    text = ""
                }
            }
        }
    }
}
