import QtQuick 2.15
import QtQuick.Controls 2.15

import BackEnd 1.0
import StratifyLabs.UI 2.0

Item {
    id: updateRequester
    signal returnButtonPressed()

    anchors.fill: parent
    visible: true
    Rectangle {
        id: background
        anchors.fill: parent
        color: "darkslategray"
    }

    SRow {
        id: topButtonRow
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
            margins: 10
        }
        height: 60

        SButton {
            id: connectButton
            span: 3
            text: qsTr("Подключиться")
            style: "btn-secondary lg"
            anchors {

                margins: 10
            }
            onClicked: update_handle.connectToServer()
        }
        SButton {
            id: updateButton
            text: qsTr("Обновить список")
            style: "btn-primary lg"
            span: 3
            anchors {

                margins: 10
            }
            enabled: false
            onClicked: update_handle.requestUpdate()
        }
        SPanel {
            // id: bu
            span: 4
            style: "btn-naked lg"
            SRow {
                SLabel{
                    // span: 6
                    style: "btn-naked lg"
                    text: "Категория файла"
                    color: "black"
                }

                SDropdown {
                    id: fileTypeSelector
                    style: "lg"
                    // span: 6

                    enabled: false
                    onCurrentIndexChanged: update_handle.changeFileType(fileTypeSelector.currentIndex)
                }
            }
        }
    }
    SButton {
        id: returnButton
        style: "btn-secondary"
        text: qsTr("Назад")
        anchors {
            left:parent.left
            bottom: parent.bottom
            margins: 10
        }
        onClicked: updateRequester.returnButtonPressed()
    }

    Rectangle {
        id: listBorder
        width: parent.width * .6
        radius: 10
        color: "transparent"
        border.width: 1
        border.color: "lightgray"
        anchors {
            left: parent.left
            bottom: returnButton.top
            top: topButtonRow.bottom
            topMargin: 70
            bottomMargin: 10
            leftMargin: 20
            rightMargin: 10
        }
        // Rectangle {
        //     anchors.fill: parent
            SLabel{
                id: listLabel
                style: "label-primary lg"
                text: "Доступные файлы"
                width: parent.width
                anchors{
                    top: parent.top
                    margins: 0
                }
            }

            ListView {
                id: updateView
                spacing: 15
                clip: true
                anchors{
                    left: parent.left
                    right: parent.right
                    bottom: parent.bottom
                    top: listLabel.bottom
                    margins: 10
                }

                delegate: SButton {
                    required property string modelData
                    id: delegate
                    width: updateView.width * 0.9
                    anchors.horizontalCenter: parent.horizontalCenter
                    height: 60
                    style: "btn-outline-primary"
                    anchors.margins: 20
                    text: modelData
                    clip: true
                    onClicked: update_handle.requestFile(text)
                }
            }
        // }

    }

    SColumn {
        anchors {
            bottom: parent.bottom
            top: topButtonRow.bottom
            right: parent.right
            left: listBorder.right
        }

      SProgressCircle {
        id: progressCircle;

        property double stepSize;

        style: "primary";
        value: 0.0;
        visible: false


        SIcon {
          anchors.centerIn: parent;
          style: "text-h1";
          iconString: Fa.Icon.download;
        }
        MouseArea {
            anchors.fill: parent
            onClicked: {
                if (parent.value == 1.0) {
                    parent.visible = false;
                    parent.value = 0;
                }
            }
        }
        onValueChanged: {
            if (value == 1.0)
                style = "success"
            else
                style = "primary"
        }
      }
    }

    UpdateClient {
        id: update_handle

    }
    Connections {
        target: update_handle
        function onFileListReceived() {
            updateView.model = update_handle.updateFileList()
        }
        function onReady() {
            updateButton.enabled = true;
            fileTypeSelector.enabled = true;
            fileTypeSelector.model = update_handle.fileTypes()
        }
        function onFilePartRecieved(percentage) {
            progressCircle.visible = true;
            progressCircle.value = percentage
        }
    }

}
