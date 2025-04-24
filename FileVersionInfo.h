#ifndef FILEVERSIONINFO_H
#define FILEVERSIONINFO_H

#include <QString>
#include <QRegularExpression>

class FileVersionInfo {

// public:
    Q_GADGET
    Q_PROPERTY(QString filename READ filename WRITE setFilename FINAL)
    Q_PROPERTY(int major READ major WRITE setMajor FINAL)
    Q_PROPERTY(int minor READ minor WRITE setMinor FINAL)
    Q_PROPERTY(int fix READ fix WRITE setFix FINAL)
    Q_PROPERTY(int valid READ valid WRITE setFix FINAL)
public:
    void init(const QString& input);

    QString filename() const;
    void setFilename(const QString &newFilename);
    int major() const;
    void setMajor(int newMajor);

    int minor() const;
    void setMinor(int newMinor);

    int fix() const;
    void setFix(int newFix);

    int valid() const;
    void setValid(int newValid);

    static QList<FileVersionInfo> readFromIni(const QString& iniPath);
    static void writeToIni(const QList<FileVersionInfo>& files, const QString& iniPath);

private:
    QString m_filename;
    int m_major;
    int m_minor;
    int m_fix;
    int m_valid;
};



Q_DECLARE_METATYPE(FileVersionInfo)

#endif // FILEVERSIONINFO_H
