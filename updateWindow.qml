import QtQuick 2.15

import BackEnd 1.0
import StratifyLabs.UI 2.0

Item {
    id: updateRequester
    signal returnButtonPressed()

    anchors.fill: parent
    visible: true

    SRow {
        id: topButtonRow
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
            margins: 10
        }

        SButton {
            id: connectButton
            text: qsTr("Подключиться")
            style: "btn-secondary"
            anchors {

                margins: 10
            }
            onClicked: update_handle.connectToServer()
        }
        SButton {
            id: updateButton
            text: qsTr("Обновить список")
            style: "btn-secondary"
            anchors {

                margins: 10
            }
            enabled: false
            onClicked: update_handle.requestUpdate()
        }
        SDropdown {
            id: fileTypeSelector
            enabled: false
            onCurrentIndexChanged: update_handle.changeFileType(fileTypeSelector.currentIndex)
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

    ListView {
        id: updateView
        spacing: 5
        clip: true
        anchors {
            left: parent.left
            right: parent.horizontalCenter
            bottom: returnButton.top
            top: topButtonRow.bottom
            margins: 15
        }
        delegate: SButton {
            required property string modelData
            id: delegate
            width: 500
            height: 60
            style: "btn-outline-primary"
            // color: "burlywood"
            // border.color: "#005c9f"
            // radius: 10
            anchors.margins: 20
            text: modelData
            onClicked: update_handle.requestFile(text)
        }
    }

    SColumn {
        anchors {
            bottom: parent.bottom
            top: topButtonRow.bottom
            right: parent.right
            left: updateView.right
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
        // function onFileRecievingStart(parts) {
        //     progressCircle.stepSize = 1 / parts
        //     progressCircle.visible = true;
        //     // update_handle.filePartRecieved.connect(progressCircle.calculateStep())
        // }
        function onFilePartRecieved(percentage) {
            progressCircle.visible = true;
            progressCircle.value = percentage
        }
    }

}
