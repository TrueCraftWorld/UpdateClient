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

    /**
     * @brief запрос обновления
     * @details попытка подключения к захардкоженому адресу сервера обновлений
     * успешным результатом должно стать получение от сервера списка доступных
     * к выгрузке файлов
     */
    Q_INVOKABLE void requestUpdate();

    /**
     * @brief updateFileList
     * @return возвращает текущий список доступных к загрузке файлов
     */
    Q_INVOKABLE QStringList updateFileList() const;

    /**
     * @brief выполянет регистрацию класса в qml
     */
    static void registerUpdateClient();

signals:
    /**
     * @brief сигнал об успешной загрузке файла
     * @param полный путь к файлу вместе с именем
     */
    void fileReceived(const QString& path);

    /**
     * @brief сигнал об успешном получении списка файлов
     */
    void fileListReceived();
private:
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
