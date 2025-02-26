#ifndef PACKAGE_H
#define PACKAGE_H

#include <QtCore>
#include <QSharedPointer>


struct TransferData{
    QSharedPointer<QFile> localFile = nullptr;
    qint64 totalBytes;
    QString fileName;
    QByteArray dataBlock;
    qint64 bytesWritten;
    qint64 bytesToWrite;
    quint64 payloadSize;
    int command;
    quint64 bytesReceived;
    quint64 fileNameSize;
};

#endif // PACKAGE_H
