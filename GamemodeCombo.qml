import QtQuick          2.4
import QtQuick.Controls 1.3
import app.mcql         1.0

ComboBox
{
    model: gamemodeModel

    property var value

    onCurrentIndexChanged: value = gamemodeModel.get(currentIndex).value

    onValueChanged: {
        for(var i = 0; i < gamemodeModel.count; ++i)
        {
            if(gamemodeModel.get(i).value === value)
            {
                currentIndex = i
                break
            }
        }
    }

    ListModel
    {
        id: gamemodeModel
        ListElement { text: "Survival"; value: McqlUtil.Survival }
        ListElement { text: "Creative"; value: McqlUtil.Creative }
    }
}
