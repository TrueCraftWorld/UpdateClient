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
            centerIn: parent
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
                    // console.log("update_press")
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
    UpdateClient {
        id: update_handle
    }

}
