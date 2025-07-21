import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import StratifyLabs.UI 2.0

Popup {
    id: popupRoot

    // Параметры диалога
    property string fileName: ""
    property string version: ""
    property string oldVersion: ""
    // property int major: 0
    // property int minor: 0
    // property int fix: 0
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
        style: "panel-primary lg";
        heading: qsTr("Обнаружен файл");
        anchors.fill: parent

        ColumnLayout {
            anchors.horizontalCenter: parent.horizontalCenter
            // Текст сообщения
            id: message
            SColumn {

                SText {
                    style: "center lg";
                    text: popupRoot.fileName;
                }
                SText {
                    style: "center";
                    text: qsTr("Версия: ")
                            + popupRoot.version
                          // + popupRoot.major
                          // + "." + popupRoot.minor
                          // + "." + popupRoot.fix;
                }
                SText {
                    style: "center";
                    text: qsTr("Предыдущая Версия: ")
                          + popupRoot.oldVersion
                    // + popupRoot.major
                    // + "." + popupRoot.minor
                    // + "." + popupRoot.fix;
                    visible: (popupRoot.oldVersion.length != 0)
                }
                SText {
                    style: "center";
                    text: qsTr("Обновить?");
                }
            }
        }
        SRow {
            Layout.alignment: Qt.AlignHCenter
            anchors {
                top: message.bottom
                topMargin: 25
                horizontalCenter: parent.horizontalCenter
                left: parent.left
                right: parent.right
            }
            SButton {
                span: 5
                text: qsTr("Да")
                anchors.margins: 25
                onClicked: {
                    popupRoot.accepted()
                    popupRoot.close()
                }
            }

            SButton {
                span: 5
                text: qsTr("Нет")
                anchors.margins: 25
                onClicked: {
                    popupRoot.rejected()
                    popupRoot.close()
                }
            }
        }
    }
}
