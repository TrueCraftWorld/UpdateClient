import QtQuick 2.15

import BackEnd 1.0
Item {
    id: updateRquester
    width: 640
    height: 480
    visible: true
    signal returnButtonPressed()

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
        anchors {
            left:parent.left
            top: parent.top
        }
        MouseArea {
            anchors.fill: parent
            onClicked: {
                    // console.log("update_press")
                    update_handle.requestUpdate()
            }
        }
        width: 400
        height: 100
        color: "darkblue"
    }
    UpdateClient {
        id: update_handle
    }

}
