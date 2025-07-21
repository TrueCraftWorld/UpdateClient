
QT += quick core network qml concurrent
CONFIG += c++17 link_pkgconfig disable-desktop
 

SOURCES += \
    $$PWD/FileChecker.cpp \
    $$PWD/FileVersionInfo.cpp \
    $$PWD/InternalUpdater.cpp \
        $$PWD/updateclient.cpp \
    $$PWD/updatesocket.cpp

RESOURCES += $$PWD/updater.qrc

HEADERS += \
    $$PWD/FileChecker.h \
    $$PWD/FileVersionInfo.h \
    $$PWD/InternalUpdater.h \
    $$PWD/abstractupdateprovider.h \
    $$PWD/package.h \
    $$PWD/protocolcommand.h \
    $$PWD/updateConfig.h \
    $$PWD/updateclient.h \
    $$PWD/updatesocket.h

DISTFILES += \
    $$PWD/DropDownPanel.qml \
    $$PWD/UpdateDialog.qml \
    $$PWD/updateWindow.qml

