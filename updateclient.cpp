#include "updateclient.h"
#include "FileVersionInfo.h"
#include "InternalUpdater.h"

#include <QFile>
#include <QHostAddress>
#include <QQmlContext>
#include <QDebug>
#include <QFileInfo>
#include <QDir>
#include <QSettings>

#include "updateConfig.h"

/**
 * @brief UpdateClient::UpdateClient
 * @param parent
 * @todo прописать парсинг директории извесных бинарей на наличие инишника и нужной файловой структуры
 * если не нашли создать. если уже есть файлы - просписать их как нулевую версию в инишник
 * заполнить по инишнику инфу об известных бинарях
 */
UpdateClient::UpdateClient( QObject *parent)
    : QObject(parent)
{
    initFileTracker();
}

void UpdateClient::connectToServer()
{
    socket.reset(new UpdateSocket(0, this));
    QHostAddress updateHost(UPDATE_SERV_IP);

    connect(socket.data(), &UpdateSocket::signalListRecieved, this, [this] (const QStringList& list) {
        m_updateFileList = list;
        emit signlaFileListReceived();
    });
    connect(socket.data(), &UpdateSocket::connected, this, &UpdateClient::requestUpdate);
    connect(socket.data(), &UpdateSocket::connected, this, &UpdateClient::ready);
    connect(socket.data(), &UpdateSocket::signalFileRecieved, this, &UpdateClient::slotCheckUpdate);
    connect(socket.data(), &UpdateSocket::signalFilePartRecieved, this, &UpdateClient::signalFilePartRecieved);

    socket->bind(updateHost, 12345, QAbstractSocket::ShareAddress | QAbstractSocket::ReuseAddressHint);
    socket->connectToHost(updateHost,11111);
}

void UpdateClient::registerUpdateClient()
{
    qmlRegisterType<UpdateClient>("BackEnd", 1, 0, "UpdateClient");
}

void UpdateClient::requestFile(const QString &file)
{

    socket->requestFile(file);
}

void UpdateClient::changeFileType(int type)
{
    if (type < TransferHeader::DevelopmentFiles || type > TransferHeader::RecommendationUpdate )
        return;
    m_type = type;
    requestUpdate();
}

QStringList UpdateClient::fileTypes() const
{
    return TransferHeader::fileTypes();
}

void UpdateClient::requestUpdate()
{
    socket->requestFileList(static_cast<TransferHeader::FileType>(m_type));
}

void UpdateClient::slotDoUpdate()
{
    if (pendingUpdate.has_value()) {
        InternalUpdater upd(static_cast<InternalUpdater::Types>(pendingUpdate->fileType()));
        QDir dir(DOWNLOAD_PATH);
        QStringList filters;
        filters << ("*" + pendingUpdate->filename() + "*");
        QFileInfoList list = dir.entryInfoList(filters,
                                               QDir::Files | QDir::NoDotAndDotDot,
                                               QDir::Time);
        if (list.size()) {
            QString absFileName = QString(BINARIES_PATH)
                                  + UpdateSubFolds.at(pendingUpdate->fileType())
                                  + pendingUpdate->filename();

            if (!list.at(0).suffix().isEmpty())
                absFileName += "."
                            + list.at(0).suffix();

            upd.executeUpdate(list.at(0).absoluteFilePath(), absFileName);
        }
    }
}

void UpdateClient::slotRejectUpdate()
{
    pendingUpdate.reset();
}

void UpdateClient::slotCheckUpdate(const QString &name, int /*fileType*/)
{
    FileVersionInfo info;
    info.init(name);
    if (!info.valid())
        return;
    int count = 0;
    info.setFileType(m_type);
    for (const auto &item : qAsConst(m_binaries)) {
        if (item.filename() != info.filename()) {
            ++count;
            continue;
        }
        if (item.major() < info.major()) {
            prepareUpdate(info);
            return;
        } else if (item.major() == info.major()
                   && item.minor() < info.minor()) {
            prepareUpdate(info);
            return;
        } else if (item.major() == info.major()
                 && item.minor() == info.minor()
                   && item.fix() < info.fix()) {
            prepareUpdate(info);
            return;
        }
    }
    if (count == m_binaries.size())
        prepareUpdate(info);
}

void UpdateClient::initFileTracker()
{
// BINARIES_PATH
    QString mainStr(BINARIES_PATH);
    QStringList paths;
    QFileInfoList filesFound;
    paths.append(mainStr);
    paths.append(mainStr + QString("Firmware"));
    paths.append(mainStr + QString("Media"));
    paths.append(mainStr + QString("Recommendation"));
    paths.append(mainStr + QString("Settings"));
    paths.append(mainStr);
    // paths.append(mainStr + QString("Software"));


    for (const QString& item : paths) {
        QDir dir(item);
        if (!dir.exists()) {
            dir.mkpath(item);

            continue;
        }
        filesFound.append(dir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot | QDir::NoSymLinks));
    }
    QFileInfo iniFile(mainStr + QString("file-versions.ini"));

    QList<FileVersionInfo> knownFiles;
    QList<FileVersionInfo> unknownFiles;

    if (iniFile.exists()) {
        knownFiles = FileVersionInfo::readFromIni(iniFile.absoluteFilePath());
        auto iter = filesFound.begin();
        while (iter != filesFound.end()) {
            for (const auto& item : qAsConst(knownFiles)) {
                if (item.filename() == iter->baseName()) {
                    iter = filesFound.erase(iter);
                    continue;
                }
            }
            FileVersionInfo newFile;
            newFile.setFilename(iter->baseName());
            newFile.setMajor(0);
            newFile.setMinor(0);
            newFile.setFix(0);
            newFile.setValid(true);
            unknownFiles.append(newFile);
            ++iter;
        }
    }

    FileVersionInfo::writeToIni(unknownFiles, iniFile.absoluteFilePath());

    m_binaries = knownFiles + unknownFiles;
}

void UpdateClient::prepareUpdate(const FileVersionInfo& upd)
{
    pendingUpdate.emplace(upd);
    emit signalUpdateFound(upd);
}

void UpdateClient::setBinaries(const QList<FileVersionInfo> &newBinaries)
{
    m_binaries = newBinaries;
}

QStringList UpdateClient::updateFileList() const
{
    return m_updateFileList;
}

