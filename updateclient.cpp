#include "updateclient.h"

#include <QFile>
#include <QHostAddress>
#include <QQmlContext>
#include <QDebug>
#include <QFileInfo>
#include "protocolcommand.h"
#include "package.h"
#include "updateConfig.h"

UpdateClient::UpdateClient( QObject *parent)
    : QObject(parent)
{
    flag = false;
    SYNFlag = 0;
    DOWNFlag = 0;

    data.payloadSize = 64*1024;
    data.localFile = nullptr;
    data.bytesWritten = 0;
    data.bytesToWrite = 0;

    clearNetworkData();

}

void UpdateClient::requestUpdate()
{
    updateSocket = new QTcpSocket(this);

    QHostAddress updateHost(UPDATE_SERV_IP);

    connect(updateSocket, &QTcpSocket::connected, this, [this](){
        headerReaded=false;
    });
    connect(updateSocket, &QTcpSocket::readyRead, this, &UpdateClient::receiveFile);
    connect(updateSocket, &QTcpSocket::bytesWritten, this, &UpdateClient::receiveFile);
    updateFile.clear();

    updateSocket->bind(updateHost, 11111);
    updateSocket->connectToHost(updateHost,11111);
}

void UpdateClient::registerUpdateClient()
{
    qmlRegisterType<UpdateClient>("BackEnd", 1, 0, "UpdateClient");
}

/**
 * @brief UpdateClient::receiveFile
 * @details Пока для себя - передаём всегда минимум три юинт64 в датастриме (т.е. как минимум всегда хэдер)
 * первый юинт - полное количество байт этого сообщения (может прийти не за один раз)
 * второй юинт - команда, т.е. что именно передаём
 * третий юинт - размер дополнительных данных в хэдере
 * процесс получения такой
 * 1. проверяем флаг незаконченного сообщения - если есть, просто докидываем все недостающие байты в дата блок
 * 2. если сообщение новое - проверяем полностью ли пришёл хедер. да - читаем, нет - ждём
 * 3. читаем хэдер, если пришло байт меньше чем ждём - ставим флаг.
 * 4. если наконец получили всё сообщение - обрабатываем данные согласно команде, затираем флаги, затираем датаблок.
 */
void UpdateClient::receiveFile()
{

    int downflag = 0  ,  synfilelistflag = 0,   transferfileflag = 0;
    qint32 temp;

    if(updateSocket->bytesAvailable()<=0)
    {
        return;
    }
    QDataStream in(updateSocket);
    in.setVersion(QDataStream::Qt_5_15);
    if(data.bytesReceived <= sizeof(qint64)*3)
    {
        if(updateSocket->bytesAvailable() >= sizeof(qint64)*3
            && (data.fileNameSize==0))
        {
            in >> data.totalBytes >> data.command
                >> data.fileNameSize >> temp;
            data.bytesReceived += sizeof(qint64)*3;
        }

    }
    switch(data.command)
    {
    case _TRANSFER_FILE_ :
    {
        transferfileflag = 1;
        if(!data.fileName.isEmpty()) {
            tempFileName = "/usr/share/qtpr/";
            tempFileName += data.fileName;
            if (!data.localFile || !data.localFile->isOpen()) {
                data.localFile = new QFile(tempFileName);
                if(!data.localFile->open(QFile::WriteOnly))
                    return;
            }
        } else  if(updateSocket->bytesAvailable() >= data.fileNameSize
                && data.fileNameSize!=0) {
            in >> data.fileName;
            data.bytesReceived += data.fileNameSize;
        }
    }
    break;
    case _TRANSFER_LIST_:
    {
        synfilelistflag = 1;
        if(updateSocket->bytesAvailable() >= data.fileNameSize
            && data.fileNameSize!=0) {
            in >> data.fileName;
            data.bytesReceived += data.fileNameSize;
        }

    }
    case _TRANSFER_ACK_ :
    {
        qDebug()<<"Send file success!";
    }
    break;
    default:
        qDebug()<<"Receive command nulity!";
    }
    if(data.bytesReceived < data.totalBytes)
    {
        data.bytesReceived += updateSocket->bytesAvailable();
        data.dataBlock = updateSocket->readAll();
        data.localFile->write(data.dataBlock);
        data.dataBlock.resize(0);
    }
    if(data.bytesReceived == data.totalBytes)
    {
        if(transferfileflag == 1) {
            transferfileflag = 0;
            data.localFile->close();
            emit fileReceived(data.fileName);
            qDebug()<<"Receive file success!";
        } else if(synfilelistflag == 1) {
            synfilelistflag = 0;
            m_updateFileList = data.fileName.split('%');
            if (!m_updateFileList.empty()) {
                emit fileListReceived();
            }
            qDebug()<<"Request file list success!";
        } else if(downflag == 1) {
            downflag = 0;
            qDebug()<<"Download file success!";
        }
        clearNetworkData();
    }
}

void UpdateClient::clearNetworkData()
{
    data.totalBytes = 0;
    data.bytesReceived = 0;
    data.fileNameSize = 0;
    data.dataBlock.resize(0);
}

QStringList UpdateClient::updateFileList() const
{
    return m_updateFileList;
}

