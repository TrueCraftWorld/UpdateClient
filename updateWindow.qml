import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

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
    SLabel {
        id: screenTitle
        width: background.width
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
        }
        style: "label-primary lg";
        text: qsTr("Скачивание обновлений");
    }

    SColumn {
        id: topButtonRow
        anchors {
            top: screenTitle.bottom
            left: parent.left
            right: listBorder.left
            margins: 15
        }
        rowSpacing: 15

        SButton {
            id: connectButton
            text: qsTr("Подключиться")
            style: "btn-primary lg"
            Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
            Layout.preferredWidth: updateRequester.width * .35

            onClicked: update_handle.connectToServer()
        }
        SButton {
            id: updateButton
            text: qsTr("Обновить список")
            style: "btn-primary lg"
            Layout.alignment: Qt.AlignHCenter |Qt.AlignTop
            Layout.preferredWidth: updateRequester.width * .35
            enabled: false
            onClicked: update_handle.requestUpdate()
        }
    }

    DropDownPanel {
        id: fileTypeSelector
        title: qsTr("Категория файла")
        anchors {
            top: topButtonRow.bottom
            left: parent.left
            right: listBorder.left
            margins: 25
        }

        onDropDownIdxChanged: update_handle.changeFileType(fileTypeSelector.index)
    }

    SBadge {
        id: loadingIcon
        style: "icon-spin";
        // span: 4;

        iconString: Fa.Icon.refresh;
        // label: "Проверка \n локальных файлов";
        // attr.animationPeriod: 2000;
        anchors {
            // top: fileTypeSelector.bottom
            verticalCenter: progressCircle.verticalCenter
            horizontalCenter: topButtonRow.horizontalCenter
            // topMargin: 120
        }
    }

    SProgressCircle {

        id: progressCircle;

        property double stepSize;

        style: "primary";
        value: 0.0;
        visible: false

        anchors {
            top: fileTypeSelector.bottom
            horizontalCenter: topButtonRow.horizontalCenter
            topMargin: height * .75
        }

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
    SButton {
        id: returnButton
        style: "btn-secondary"
        text: qsTr("Назад")
        anchors {
            left:parent.left
            bottom: parent.bottom
            margins: 15
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
            right: parent.right
            bottom: returnButton.bottom
            top: screenTitle.bottom
            margins:15
        }
        SLabel {
            id: listLabel
            style: "label-primary lg"
            text: "Доступные файлы"
            width: parent.width
            anchors {
                top: parent.top
                margins: 0
            }
        }

        ListView {
            id: updateView
            spacing: 15
            clip: true
            anchors {
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
    }

    UpdateClient {
        id: update_handle
    }

    UpdateDialog {
        id: updConfirmDialog
        visible: false
    }

    Connections {
        target: update_handle
        function onSignlaFileListReceived() {
            updateView.model = update_handle.updateFileList()
        }
        function onReady() {
            updateButton.enabled = true;
            fileTypeSelector.enabled = true;
            fileTypeSelector.dropModel = update_handle.fileTypes()
        }
        function onSignalFilePartRecieved(percentage) {
            progressCircle.visible = true;
            progressCircle.value = percentage
        }
        function onSignalUpdateFound(fileInfo, oldVersion) {
            updConfirmDialog.fileName = fileInfo.filename
            updConfirmDialog.version = fileInfo.versionString()

            updConfirmDialog.oldVersion = oldVersion

            // updConfirmDialog.major = fileInfo.major
            // updConfirmDialog.minor = fileInfo.minor
            // updConfirmDialog.fix = fileInfo.fix

            updConfirmDialog.open()
            updConfirmDialog.x = 200
            updConfirmDialog.y = 200
        }
        function onSignalFilesChecked() {
            loadingIcon.visible = false;
        }
    }
    Connections {
        target: updConfirmDialog
        function onAccepted() {
            update_handle.slotDoUpdate()
        }
        function onRejected() {
            update_handle.slotRejectUpdate()
        }
    }
}
