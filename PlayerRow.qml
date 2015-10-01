import QtQuick  2.4
import app.mcql 1.0

Row
{
    anchors.left:  parent.left
    anchors.right: parent.right

    Text
    {
        text:  model.name
        width: parent.width / 3
    }

    GamemodeCombo
    {
        width: 2 * parent.width / 3
        value: model.mode

        onValueChanged: serverLink.setPlayerMode(model.name, value)
    }
}
