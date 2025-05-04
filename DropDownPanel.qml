import QtQuick 2.15
import QtQuick.Layouts 1.15

import StratifyLabs.UI 2.0

// Item {
Rectangle {
    id: panelRoot
    property string title
    signal dropDownIdxChanged();
    property alias index: dropDown.currentIndex
    property alias dropModel: dropDown.model
    // anchors.fill: parent

    SPanel {
        id: panel

        style: "panel-info"
        anchors.fill: parent
        // anchors.leftMargin: 9
        // anchors.rightMargin: -5
        heading: panelRoot.title /*qsTr("Категория файла")*/

        SDropdown {
            id: dropDown
            enabled: panelRoot.enabled
            anchors.left: parent.left
            anchors.right: parent.right
            onCurrentIndexChanged: panelRoot.dropDownIdxChanged()
        }
    }

}
