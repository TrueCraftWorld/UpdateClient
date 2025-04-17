import QtQuick 2.15
import QtQuick.Controls 2.15

import StratifyLabs.UI 2.0

Dialog {
    property string fileName
    property string version

    contentItem:   SPanel {
        // span: 4;
        style: "panel-primary";
        heading: "Primary";

        SText {
          text: "Обнаружен файл: " + fileName + "с версией" + version + "Обновить ?";
        }

    }

}
