#ifndef FILEVERSIONCHECK_H
#define FILEVERSIONCHECK_H

#include <QString>
#include <QRegularExpression>

class FileVersionInfo {

public:
    FileVersionInfo (const QString& input);




    QString filename;
    int major = 0;
    int minor = 0;
    int fix = 0;
    bool isValid = false;
};

#endif // FILEVERSIONCHECK_H
