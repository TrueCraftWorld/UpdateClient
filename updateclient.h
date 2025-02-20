#ifndef UPDATECLIENT_H
#define UPDATECLIENT_H

#include <QTcpSocket>
#include <QObject>
#include <QDataStream>
#include <QQmlEngine>

#include "package.h"

class UpdateClient : public QObject
{
    Q_OBJECT
public:
    enum {
        IDLE = 0,
        RECEIVING,
        SENDING,
    };
    explicit UpdateClient(QObject *parent = nullptr);
    Q_INVOKABLE void requestUpdate();

    /**
     * @brief выполянет регистрацию класса в qml
     */
    static void registerUpdateClient();
    QStringList updateFileList() const;

signals:
    void fileReceived(const QString& path);
    void fileListReceived();
private:
    void receiveFile2();
    void receiveFile();
    void clearNetworkData();

private:
    TransferData data;

    bool flag;
    int SYNFlag;
    int DOWNFlag;
    QString tempFileName;

    int bytesAwaited= -1;
    QTcpSocket* updateSocket;
    QByteArray updateFile;
    QByteArray message;
    QDataStream in;
    QString m_FileName;
    QStringList m_updateFileList;
    bool headerReaded;

    bool isWaitingForWholeMessage = false;
    bool isWaitingForHeader = false;
    int currentCommand = 0;
    int currentState = IDLE;
};

#endif // UPDATECLIENT_H
