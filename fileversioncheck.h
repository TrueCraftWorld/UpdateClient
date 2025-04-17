#ifndef FILEVERSIONCHECK_H
#define FILEVERSIONCHECK_H

#include <QString>
#include <QRegularExpression>

class FileVersionInfo {

// public:
    Q_GADGET
    Q_PROPERTY(QString filename READ filename WRITE setFilename FINAL)
    Q_PROPERTY(int major READ major WRITE setMajor FINAL)
    Q_PROPERTY(int minor READ minor WRITE setMinor FINAL)
    Q_PROPERTY(int fix READ fix WRITE setFix FINAL)
    Q_PROPERTY(int valid READ valid)
public:
    void init(const QString& input);
    // FileVersionInfo (const QString& input);



    // QString filename;
    // int major = 0;
    // int minor = 0;
    // int fix = 0;
    // bool isValid = false;
    QString filename() const;
    void setFilename(const QString &newFilename);
    int major() const;
    void setMajor(int newMajor);

    int minor() const;
    void setMinor(int newMinor);

    int fix() const;
    void setFix(int newFix);

    int valid() const;

private:
    QString m_filename;
    int m_major;
    int m_minor;
    int m_fix;
    int m_valid;
};

Q_DECLARE_METATYPE(FileVersionInfo)

#endif // FILEVERSIONCHECK_H
