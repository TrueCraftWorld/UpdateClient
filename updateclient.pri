
QT += quick core network qml concurrent
CONFIG += c++17 link_pkgconfig disable-desktop
 

SOURCES += \
        $$PWD/updateclient.cpp \
    $$PWD/updatesocket.cpp

RESOURCES += $$PWD/updater.qrc

HEADERS += \
    $$PWD/package.h \
    $$PWD/protocolcommand.h \
    $$PWD/updateConfig.h \
    $$PWD/updateclient.h \
    $$PWD/updatesocket.h

DISTFILES += \
    $$PWD/ServiceButton.qml \
    $$PWD/updateWindow.qml

