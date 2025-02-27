import QtQuick 2.15

Rectangle {
    id: button
    property string text: butText.text
    signal tapped
    width: 300
    height: 80
    color: "darkslateblue"
    border.color: "burlywood"
    anchors {
        left:parent.left
        bottom: parent.bottom
    }
    Text {
        id: butText
        anchors.fill: parent
        color: "burlywood"
        text: ""
    }
    MouseArea {
        anchors.fill: parent
        onClicked: button.tapped()
    }
}
