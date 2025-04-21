#include "fileversioncheck.h"

static QRegularExpression regex("^(.*?)_(\\d+)-(\\d+)-(\\d+)$");

// FileVersionInfo::FileVersionInfo()
// {
    // QRegularExpressionMatch match = regex.match(input);

    // if (match.hasMatch()) {
    //     m_filename = match.captured(1);
    //     major = match.captured(2).toInt();
    //     minor = match.captured(3).toInt();
    //     fix = match.captured(4).toInt();
    //     isValid = true;
    // }
// }

void FileVersionInfo::init(const QString &input)
{
    QRegularExpressionMatch match = regex.match(input);

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

QList<FileVersionInfo> FileVersionInfo::readFromIni(const QString &iniPath)
{

}

void FileVersionInfo::writeToIni(const QList<FileVersionInfo> &files, const QString &iniPath)
{

}
