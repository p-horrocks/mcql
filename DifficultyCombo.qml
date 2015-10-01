import QtQuick          2.4
import QtQuick.Controls 1.3
import app.mcql         1.0

ComboBox
{
    model: difficultyModel

    property var value

    onCurrentIndexChanged: value = difficultyModel.get(currentIndex).value

    onValueChanged: {
        for(var i = 0; i < difficultyModel.count; ++i)
        {
            if(difficultyModel.get(i).value === value)
            {
                currentIndex = i
                break
            }
        }
    }

    ListModel
    {
        id: difficultyModel
        ListElement { text: "Peaceful"; value: McqlUtil.Peaceful }
        ListElement { text: "Easy";     value: McqlUtil.Easy }
        ListElement { text: "Normal";   value: McqlUtil.Normal }
        ListElement { text: "Hard";     value: McqlUtil.Hard }
    }
}
