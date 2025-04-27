#ifndef INTERNALUPDATER_H
#define INTERNALUPDATER_H

#include "abstractupdateprovider.h"

#include <QFileInfo>

const QStringList UpdateSubFolds = {
    (""),
    ("Firmware/"),
    ("Software/"),
    ("Media/"),
    ("Settings/"),
    ("Recommendation/")
};

class InternalUpdater : public AbstractUpdateProvider
{
public:
    // enum Types : int {
    //     SELF_UPDATE = 0,
    //     MEDIA_UPDATE,
    //     CONFIG_UPDATE
    // };
    //other types should allow to register your own updaters

    enum Types : int {
        DevelopmentFiles = 0, /**< режим для разработки, просто файлы из папки */
        FirmwareUpdate, /**< файлы прошивок стм-ок */
        SoftwareUpdate, /**< файлы обновления ПО одноплатника */
        MediaUpdate, /**< файл с медиаконтентом - обучение, инструкции, реклама */
        SettingsUpdate,  /**< файлы настроек и конфигов */
        RecommendationUpdate /**< файлы установок встроенных программ, будь то архив с конфигами ил файлы базы данных */
    };
    explicit InternalUpdater(Types type);
private:
    QFileInfo updateFile;
    int m_type = DevelopmentFiles;
};

#endif // INTERNALUPDATER_H
