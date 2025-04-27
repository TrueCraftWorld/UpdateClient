import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import StratifyLabs.UI 2.0

// Dialog {
//     id: blaBla
//     property string fileName
//     property int major
//     property int minor
//     property int fix

//     // Dialog {
//     anchors.centerIn: root

//     contentItem:   SPanel {
//         span: 4;
//         style: "panel-primary";
//         heading: "Обнаружен файл";

//         SText {
//           text: "Обнаружен файл: " + blaBla.fileName
//                 + "с версией" + blaBla.major + "." + blaBla.minor + "." + blaBla.fix + "."
//                 + "Обновить ?";
//         }

//     }

// // }
// }

Popup {
    id: popupRoot

    // Параметры диалога
    // property string message: ""  // Текст сообщения
        property string fileName: ""
        property int major: 0
        property int minor: 0
        property int fix: 0
    // Сигналы
    signal accepted()  // Нажата кнопка "Да"
    signal rejected()  // Нажата кнопка "Нет"

    // Настройки внешнего вида
    width: 300
    height: 150
    modal: true
    focus: true
    closePolicy: Popup.NoAutoClose

    // Фон
    background: Rectangle {
        color: "#f0f0f0"
        border.color: "#cccccc"
        radius: 5
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 10

        // Текст сообщения
        Text {
            id: messageText
            Layout.fillWidth: true
            Layout.fillHeight: true
            text: "Обнаружен файл: " + popupRoot.fileName
                    + "\n версия: " + popupRoot.major + "." + popupRoot.minor + "." + popupRoot.fix + "."
                    + "\n Обновить ?";
            wrapMode: Text.Wrap
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }

        // Кнопки
        RowLayout {
            Layout.alignment: Qt.AlignHCenter

            Button {
                text: "Да"
                onClicked: {
                    popupRoot.accepted()
                    popupRoot.close()
                }
            }

            Button {
                text: "Нет"
                onClicked: {
                    popupRoot.rejected()
                    popupRoot.close()
                }
            }
        }
    }
}
