#ifndef UPDATECLIENT_H
#define UPDATECLIENT_H

#include <QTcpSocket>
#include <QObject>
#include <QDataStream>
#include <QQmlEngine>

// #include "package.h"
#include "fileversioncheck.h"
#include "updatesocket.h"

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
    Q_INVOKABLE void connectToServer();

    /**
     * @brief updateFileList
     * @return возвращает текущий список доступных к загрузке файлов
     */
    Q_INVOKABLE QStringList updateFileList() const;

    /**
     * @brief выполянет регистрацию класса в qml
     */
    static void registerUpdateClient();

    Q_INVOKABLE void requestFile(const QString& file);

    Q_INVOKABLE void changeFileType(int type);

    Q_INVOKABLE QStringList fileTypes() const;

    /**
     * @brief запрос обновления списка файлов
     */
    Q_INVOKABLE void requestUpdate();

    void setBinaries(const QList<FileVersionInfo> &newBinaries);

signals:
    /**
     * @brief сигнал об успешной загрузке файла
     * @param полный путь к файлу вместе с именем
     */
    void signalFileReceived(const QString& path);

    /**
     * @brief сигнал об успешном получении списка файлов
     */
    void signlaFileListReceived();

    /**
     * @brief сигнал о готовности к работе, успешно подключились к серверу
     */
    void ready();

    // void fileRecievingStart(int partsAwaited);
    void signalFilePartRecieved(double percentage);

    void signalUpdateFound(const FileVersionInfo&);

    // void signalUpdateDial
private slots:
    void slotCheckUpdate(const QString&);

private:
    void sendData(int written);
    void clearNetworkData();
    void initFileTracker();


private:
    QSharedPointer<UpdateSocket> socket;
    QStringList m_updateFileList;
    int m_type = 0;
    QList<FileVersionInfo> m_binaries;
};

#endif // UPDATECLIENT_H
