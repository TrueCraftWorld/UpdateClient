#ifndef ABSTRACTUPDATEPROVIDER_H
#define ABSTRACTUPDATEPROVIDER_H

#include <functional>

#include <QFileInfo>
#include <QString>

class AbstractUpdateProvider
{
    using UpdateFunction = std::function<void(const QFileInfo& file, const QString& targetPath)>;
public:

    AbstractUpdateProvider() : doUpdate(nullptr) {}

    // Виртуальный деструктор
    virtual ~AbstractUpdateProvider() = default;

    // Вызов внутренней функции при наличии
    virtual void executeUpdate(const QFileInfo& file, const QString& targetPath) {
        if (doUpdate) {
            doUpdate(file, targetPath);
        }
    }

    // Метод для регистрации функции обновления
    virtual int registerUpdateHandler(UpdateFunction func) {
        if(doUpdate)
            return -1;

        doUpdate = func;
        return 0;
    }

protected:
    UpdateFunction doUpdate;
};

#endif // ABSTRACTUPDATEPROVIDER_H
