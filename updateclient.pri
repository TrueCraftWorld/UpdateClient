
QT += quick core network qml concurrent
CONFIG += c++17 link_pkgconfig disable-desktop
 

SOURCES += \
    $$PWD/fileversioncheck.cpp \
        $$PWD/updateclient.cpp \
    $$PWD/updatesocket.cpp

RESOURCES += $$PWD/updater.qrc

HEADERS += \
    $$PWD/fileversioncheck.h \
    $$PWD/package.h \
    $$PWD/protocolcommand.h \
    $$PWD/updateConfig.h \
    $$PWD/updateclient.h \
    $$PWD/updatesocket.h

DISTFILES += \
    $$PWD/updateWindow.qml

