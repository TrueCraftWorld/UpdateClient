#ifndef FILEVERSIONINFO_H
#define FILEVERSIONINFO_H

#include <QString>
#include <QRegularExpression>
#include <QFileInfo>


class FileVersionInfo {

    Q_GADGET
    Q_PROPERTY(QString filename READ filename WRITE setFilename FINAL)
    Q_PROPERTY(int major READ major WRITE setMajor FINAL)
    Q_PROPERTY(int minor READ minor WRITE setMinor FINAL)
    Q_PROPERTY(int fix READ fix WRITE setFix FINAL)
    Q_PROPERTY(int valid READ valid WRITE setFix FINAL)
    Q_PROPERTY(QString checkSum READ checkSum FINAL)

public:
    // FileVersionInfo() = default;
    void init(const QString& input);

    const QString& filename() const;
    void setFilename(const QString &newFilename);
    int major() const;
    void setMajor(int newMajor);

    int minor() const;
    void setMinor(int newMinor);

    int fix() const;
    void setFix(int newFix);

    int valid() const;
    void setValid(int newValid);

    Q_INVOKABLE QString completeName();
    Q_INVOKABLE QString versionString();

    static QList<FileVersionInfo> readFromIni(const QString& iniPath);
    static void writeToIni(const QList<FileVersionInfo>& files, const QString& iniPath);

    int fileType() const;
    void setFileType(int newFileType);

    const QString& checkSum() const;
    void setCheckSum(const QString & checkSum);

private:
    QFileInfo m_internalInfo;
    QString m_filename;
    int m_major;
    int m_minor;
    int m_fix;
    int m_valid;
    int m_fileType;
    QString m_checkSum;
};

Q_DECLARE_METATYPE(FileVersionInfo)

#endif // FILEVERSIONINFO_H
