import QtQuick                 2.4
import QtQuick.Controls        1.3
import QtQuick.Controls.Styles 1.4

Button
{
    style: ButtonStyle {
        label: Text {
            text:           control.text
            font.pointSize: 16
        }
    }
}
