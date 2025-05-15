#include "FileVersionInfo.h"

#include <QSettings>
#include <QFileInfo>

static QRegularExpression regex("^(.*?)_(\\d+)-(\\d+)-(\\d+)$");

void FileVersionInfo::init(const QString &input)
{
    m_internalInfo = QFileInfo(input);
    QRegularExpressionMatch match = regex.match(m_internalInfo.baseName());

    if (match.hasMatch()) {
        m_filename = match.captured(1);
        m_major = match.captured(2).toInt();
        m_minor = match.captured(3).toInt();
        m_fix = match.captured(4).toInt();
        m_valid = true;
    }
}

QString FileVersionInfo::filename() const
{
    return m_filename;
}

void FileVersionInfo::setFilename(const QString &newFilename)
{
    m_filename = newFilename;
}

int FileVersionInfo::major() const
{
    return m_major;
}

void FileVersionInfo::setMajor(int newMajor)
{
    m_major = newMajor;
}

int FileVersionInfo::minor() const
{
    return m_minor;
}

void FileVersionInfo::setMinor(int newMinor)
{
    m_minor = newMinor;
}

int FileVersionInfo::fix() const
{
    return m_fix;
}

void FileVersionInfo::setFix(int newFix)
{
    m_fix = newFix;
}

int FileVersionInfo::valid() const
{
    return m_valid;
}

void FileVersionInfo::setValid(int newValid)
{
    m_valid = newValid;
}

QString FileVersionInfo::completeName()
{
    return (m_internalInfo.baseName() + "." + m_internalInfo.completeSuffix());
}

QList<FileVersionInfo> FileVersionInfo::readFromIni(const QString &iniPath)
{
    QList<FileVersionInfo> files;
    QSettings settings(iniPath, QSettings::IniFormat);

    QStringList sections = settings.childGroups();

    for (const QString& section : qAsConst(sections)) {

        settings.beginGroup(section);

        FileVersionInfo file;
        file.setFilename(section);
        file.setMajor(settings.value("major").toUInt());
        file.setMinor(settings.value("minor").toUInt());
        file.setFix(settings.value("fix").toUInt());
        file.setValid(settings.value("valid").toBool());

        files.append(file);
        settings.endGroup();
    }

    return files;
}

void FileVersionInfo::writeToIni(const QList<FileVersionInfo> &files, const QString &iniPath)
{
    QSettings settings(iniPath, QSettings::IniFormat);

    for (const FileVersionInfo& file :files) {
        // Use filename (without suffix) as section name
        settings.beginGroup(file.filename());

        // Write file information
        settings.setValue("major", file.major());
        settings.setValue("minor", file.minor());
        settings.setValue("fix", file.fix());
        settings.setValue("valid", file.valid());

        settings.endGroup();
    }
    // settings.
}

int FileVersionInfo::fileType() const
{
    return m_fileType;
}

void FileVersionInfo::setFileType(int newFileType)
{
    m_fileType = newFileType;
}
