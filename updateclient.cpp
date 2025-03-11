#include "updateclient.h"

#include <QFile>
#include <QHostAddress>
#include <QQmlContext>
#include <QDebug>
#include <QFileInfo>
#include "updateConfig.h"

UpdateClient::UpdateClient( QObject *parent)
    : QObject(parent)
{

}

void UpdateClient::requestUpdate(TransferHeader::FileType type)
{
    socket.reset(new UpdateSocket(0, this));
    QHostAddress updateHost(UPDATE_SERV_IP);

    connect(socket.data(), &UpdateSocket::listRecieved, this, [this](QStringList list){
        m_updateFileList = list;
        emit fileListReceived();
    });
    connect(socket.data(), &UpdateSocket::connected, this, [this, type](){
        socket->requestFileList(type);
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

