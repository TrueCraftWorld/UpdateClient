include($$PWD/3rdParty/PullToRefreshHandler.pri)

QT += quick core network qml concurrent
CONFIG += c++17 link_pkgconfig disable-desktop
 

SOURCES += \
        $$PWD/updateclient.cpp \

RESOURCES += $$PWD/updater.qrc

HEADERS += \
    $$PWD/package.h \
    $$PWD/protocolcommand.h \
    $$PWD/updateConfig.h \
    $$PWD/updateclient.h

