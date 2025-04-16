#ifndef UPDATEINTERNALS_H
#define UPDATEINTERNALS_H

#include "abstractupdateprovider.h"

#include <QFileInfo>

class UpdateInternals : public AbstractUpdateProvider
{
public:
    enum Types : int {
        SELF_UPDATE = 0,
        MEDIA_UPDATE,
        CONFIG_UPDATE
    }; //other type should allow to register your own updaters
    explicit UpdateInternals(Types type);
private:
    QFileInfo updateFile;
    int m_type = SELF_UPDATE;
};

#endif // UPDATEINTERNALS_H
