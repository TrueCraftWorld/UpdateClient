import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import StratifyLabs.UI 2.0

Popup {
    id: popupRoot

    // Параметры диалога
        property string fileName: ""
        property int major: 0
        property int minor: 0
        property int fix: 0
    // Сигналы
    signal accepted()  // Нажата кнопка "Да"
    signal rejected()  // Нажата кнопка "Нет"

    // Настройки внешнего вида
    width: 640
    // height: 400
    modal: true
    focus: true
    closePolicy: Popup.NoAutoClose

    // Фон
    background: Rectangle {
        // color: "#f0f0f0"
        // border.color: "#cccccc"
        opacity: 0
        radius: 10
        anchors.fill: parent
    }

    contentItem: SPanel {
        id: panel
        style: "panel-primary";
        heading: "Обнаружен файл";
        anchors.fill: parent
        ColumnLayout {
            // Текст сообщения
            id: message
            SColumn {
                SText {
                    style: "left";
                    text: popupRoot.fileName;
                }
                SText {
                    style: "left";
                    text: qsTr("Версия: ")
                          + popupRoot.major
                          + "." + popupRoot.minor
                          + "." + popupRoot.fix;
                }
                SText {
                    style: "left";
                    text: qsTr("Обновить?");
                }
            }
        }
        SRow {
            Layout.alignment: Qt.AlignHCenter
            anchors.top: message.bottom
            anchors.topMargin: 25
            anchors.horizontalCenter: parent.horizontalCenter

            SButton {
                span: 4
                text: "Да"
                anchors.margins: 25
                onClicked: {
                    popupRoot.accepted()
                    popupRoot.close()
                }
            }

            SButton {
                span: 4
                text: "Нет"
                anchors.margins: 25
                onClicked: {
                    popupRoot.rejected()
                    popupRoot.close()
                }
            }
        }
    }

}
