import QtQuick 2.15
import QtQuick.Controls 2.15

import StratifyLabs.UI 2.0

Item {
    id: blaBla
    property string fileName
    property int major
    property int minor
    property int fix

    Dialog {

    contentItem:   SPanel {
        span: 4;
        style: "panel-primary";
        heading: "Primary";

        SText {
          text: "Обнаружен файл: " + blaBla.fileName
                + "с версией" + blaBla.major + "." + blaBla.minor + "." + blaBla.fix + "."
                + "Обновить ?";
        }

    }

}
}
