#include "updateclient.h"
#include "fileversioncheck.h"

#include <QFile>
#include <QHostAddress>
#include <QQmlContext>
#include <QDebug>
#include <QFileInfo>

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

}

void UpdateClient::connectToServer()
{
    socket.reset(new UpdateSocket(0, this));
    QHostAddress updateHost(UPDATE_SERV_IP);

    connect(socket.data(), &UpdateSocket::signalListRecieved, this, [this](QStringList list){
        m_updateFileList = list;
        emit signlaFileListReceived();
    });
    connect(socket.data(), &UpdateSocket::connected, this, &UpdateClient::requestUpdate);
    connect(socket.data(), &UpdateSocket::connected, this, &UpdateClient::ready);
    // connect(socket.data(), &UpdateSocket::fileRecievingStarted, this, &UpdateClient::fileRecievingStart);
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

void UpdateClient::slotCheckUpdate(const QString &name)
{
    FileVersionInfo info;
    info.init(name);
    if (!info.valid())
        return;

    for (const auto &item : qAsConst(m_binaries)) {
        if (item.filename() != info.filename())
            continue;
        if (item.major() < info.major())
            emit signalUpdateFound(info);
        else if (item.major() == info.major()
                 && item.minor() < info.minor())
            emit signalUpdateFound(info);
        else if (item.major() == info.major()
                 && item.minor() == info.minor()
                 && item.fix() < info.fix())
            emit signalUpdateFound(info);
    }

}

void UpdateClient::setBinaries(const QList<FileVersionInfo> &newBinaries)
{
    m_binaries = newBinaries;
}

QStringList UpdateClient::updateFileList() const
{
    return m_updateFileList;
}

