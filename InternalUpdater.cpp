#include "InternalUpdater.h"

#include <QGuiApplication>
#include <QFile>

namespace {

void updateApp(const QFileInfo& file, const QString& targetPath) {
    if (!file.exists() || !file.isFile())
        return;
    QFileInfo target(targetPath);
    //переименовываем старый файл во что-то (авось обновление ревёртить надо а он тут как тут)
    if (target.exists() && target.isFile()) {
        QFile oldfile(target.absoluteFilePath());
        oldfile.rename(target.fileName() + ".old");
    }
    QFile newFile(file.absoluteFilePath());
    newFile.copy(targetPath);

    //need to call for app restart somehow
    //if we use a systemd service - it should reopen the app for us
    //otherwise we're on our own (there're methods but they all need
    //testing for compatibility with systemd service)

    //calling with some exit code that can be used later
    //and should tell systemd that we "crashed"
    qApp->exit(123);
}

void updateNonExecFiles(const QFileInfo& file, const QString& targetPath) {

    if (!file.exists() || !file.isFile())
        return;
    QFileInfo target(targetPath);
    //старый файл в корзину - это в любом случае какой-то медиаконтент
    if (target.exists() && target.isFile()) {
        QFile oldfile(target.absoluteFilePath());
        oldfile.moveToTrash();
    }
    QFile newFile(file.absoluteFilePath());
    newFile.copy(targetPath);

}

}

InternalUpdater::InternalUpdater(Types type)
    : m_type(type)
{
    switch (type) {
    case SoftwareUpdate:
    case FirmwareUpdate:
    case DevelopmentFiles:
        registerUpdateHandler(updateApp);
        break;
    case MediaUpdate:
    case RecommendationUpdate:
    case SettingsUpdate:
        registerUpdateHandler(updateNonExecFiles);
        break;
    default:
        break;
    }
}
