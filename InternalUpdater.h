#ifndef INTERNALUPDATER_H
#define INTERNALUPDATER_H

#include "abstractupdateprovider.h"

#include <QFileInfo>

class InternalUpdater : public AbstractUpdateProvider
{
public:
    enum Types : int {
        SELF_UPDATE = 0,
        MEDIA_UPDATE,
        CONFIG_UPDATE
    }; //other type should allow to register your own updaters
    explicit InternalUpdater(Types type);
private:
    QFileInfo updateFile;
    int m_type = SELF_UPDATE;
};

#endif // INTERNALUPDATER_H
