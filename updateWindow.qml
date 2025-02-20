import QtQuick 2.15

import BackEnd 1.0
Item {
    id: updateRequester
    signal returnButtonPressed()
    width: 640
    height: 480
    visible: true


    Rectangle {
        id: exitButton
        anchors {
            left:parent.left
            top: parent.top
        }
        MouseArea {
            anchors.fill: parent
            onClicked: returnButtonPressed()
        }
        width: 55
        height: 55
        color: "darkblue"
    }
    Rectangle {
        id: updateButton
        width: 400
        height: 100
        color: "green"
        anchors {
            top: parent.top
            topMargin: 15
        }
        Text {
            id: textButt
            anchors {
                fill: parent
            }
            text: qsTr("text")
        }
        MouseArea {
            anchors.fill: parent
            onClicked: {
                    update_handle.requestUpdate()
            }
        }
    }
    Rectangle {
        id: returnButton
        anchors {
            left:parent.left
            bottom: parent.bottom
        }
        MouseArea {
            anchors.fill: parent
            onClicked: updateRequester.returnButtonPressed()
        }
        width: 55
        height: 55
        color: "darkblue"
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
            color: "white"
            Text {
                id: text
                text: parent.modelData
                anchors.fill: parent
                color: "black"
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
        // function onUpdateMe() {
        //     wifi_handle.updateWiFiInfo()
        // }
    }

}
