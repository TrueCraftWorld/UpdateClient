
QT += quick core network qml concurrent
CONFIG += c++17 link_pkgconfig disable-desktop
 

SOURCES += \
    $$PWD/fileversioncheck.cpp \
        $$PWD/updateclient.cpp \
    $$PWD/updateinternals.cpp \
    $$PWD/updatesocket.cpp

RESOURCES += $$PWD/updater.qrc

HEADERS += \
    $$PWD/abstractupdateprovider.h \
    $$PWD/fileversioncheck.h \
    $$PWD/package.h \
    $$PWD/protocolcommand.h \
    $$PWD/updateConfig.h \
    $$PWD/updateclient.h \
    $$PWD/updateinternals.h \
    $$PWD/updatesocket.h

DISTFILES += \
    $$PWD/updateWindow.qml

