#include "updateclient.h"

#include <QFile>
#include <QHostAddress>
#include <QQmlContext>
#include <QDebug>
#include <QFileInfo>
// #include "protocolcommand.h"
// #include "package.h"
#include "updateConfig.h"

UpdateClient::UpdateClient( QObject *parent)
    : QObject(parent)
{
    // flag = false;
    // SYNFlag = 0;
    // DOWNFlag = 0;

    // data.payloadSize = 64*1024;
    // data.localFile = nullptr;
    // data.bytesWritten = 0;
    // data.bytesToWrite = 0;

    // clearNetworkData();

}

void UpdateClient::requestUpdate()
{
    socket.reset(new UpdateSocket(0, this));
    QHostAddress updateHost(UPDATE_SERV_IP);

    connect(socket.data(), &UpdateSocket::listRecieved, this, [this](QStringList list){
        m_updateFileList = list;
        emit fileListReceived();
    });

    socket->bind(updateHost, 11111);
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

QStringList UpdateClient::updateFileList() const
{
    return m_updateFileList;
}

