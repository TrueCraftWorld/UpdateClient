#include "fileversioncheck.h"

static QRegularExpression regex("^(.*?)_(\\d+)-(\\d+)-(\\d+)$");

FileVersionInfo::FileVersionInfo(const QString& input)
{
    QRegularExpressionMatch match = regex.match(input);

    if (match.hasMatch()) {
        filename = match.captured(1);
        major = match.captured(2).toInt();
        minor = match.captured(3).toInt();
        fix = match.captured(4).toInt();
        isValid = true;
    }
}
