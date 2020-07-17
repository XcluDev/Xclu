#ifndef XCLUPROTECTEDDATA_H
#define XCLUPROTECTEDDATA_H


//Тип защищенных данных с мютексом,
//и класс DataAccess, который блокирует данные в конструкторе, и разблокирует в деструкторе
//Применение:
//Если есть наследник data типа XcluProtectedData *, то
//DataAccess access(data); - создаст блокировку данных
//Это должны делать все, кто работают с данными

#include <QMutex>

class DataAccess;

//класс данных - их можно наследовать
class XcluProtectedData
{
public:
    XcluProtectedData() {}

protected:
    friend DataAccess;
    QMutex mutex_;
    void lock() { mutex_.lock(); }
    void unlock() { mutex_.unlock(); }
};


//класс защиты данных
class DataAccess {
public:
    DataAccess(XcluProtectedData *data) {
        data_ = data;
        data_->lock();
    }
    DataAccess(XcluProtectedData &data) {
        data_ = &data;
        data_->lock();
    }

    ~DataAccess() {
        data_->unlock();
    }

protected:
    XcluProtectedData *data_;

};

#endif // XCLUPROTECTEDDATA_H
