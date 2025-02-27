import QtQuick 2.15

import BackEnd 1.0
Item {
    id: updateRequester
    signal returnButtonPressed()

    anchors.fill: parent
    visible: true

    ServiceButton {
        id: updateButton
        text: qsTr("Подключиться")
        anchors {
            top: parent.top
            topMargin: 15
        }
        onTapped: update_handle.requestUpdate()
    }
    ServiceButton {
        id: returnButton
        text: qsTr("Назад")
        anchors {
            left:parent.left
            bottom: parent.bottom
        }
        onTapped: updateRequester.returnButtonPressed()
    }

    ListView {
        id: updateView
        spacing: 5
        clip: true
        anchors {
            left: returnButton.right
            right: parent.right
            bottom: parent.bottom
            top: updateButton.bottom
            margins: 15
        }
        delegate: Rectangle {
            required property string modelData
            width: 500
            height: 60
            color: "burlywood"
            border.color: "#005c9f"
            radius: 10
            anchors.margins: 20

            Text {
                id: text
                text: parent.modelData
                anchors.fill: parent
                color: "black"
            }
            TapHandler {
                onTapped: {
                    update_handle.requestFile(text.text)
                }
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
    }

}
