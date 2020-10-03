#ifndef XCLUPROTECTEDDATA_H
#define XCLUPROTECTEDDATA_H

#include <QMutex>
#include <QReadWriteLock>
#include "incl_h.h"

//Wrapper for data protection, with multiple-read and single-write features
//Classes: XProtectedData_<T>, XProtectedRead_<T>, XProtectedWrite_<T>
//Usage:
//1. define object XProtectedData_<float> value;
//2. write by creating XProtectedWrite_<float> write(value), and read/write its `data`
//when `write` gos out of scope - it unlocks `value`
//3. read by creating XProtectedRead_<float> read(value), and read its `data`
//when `read` gos out of scope - it unlocks `value`

template<typename T>
class XProtectedRead_;

template<typename T>
class XProtectedWrite_;

template<typename T>
class XProtectedData_ {
    XProtectedData_() {}
    XProtectedData_(T *data) {
        data_.reset(data);
    }
protected:
    QScopedPointer<T> data_;
    QReadWriteLock lock_;
    friend XProtectedRead_<T>;
    friend XProtectedWrite_<T>;
};

template<typename T>
class XProtectedRead_ {
    XProtectedRead_(XProtectedData_<T> *value);
    XProtectedRead_(XProtectedData_<T> &value);
    ~XProtectedRead_();
    const T &data();
protected:
    void lock(XProtectedData_<T> *value);
    void unlock();
    XProtectedData_<T> *value_ = nullptr;
};

template<typename T>
class XProtectedWrite_ {
    XProtectedWrite_(XProtectedData_<T> *value);
    XProtectedWrite_(XProtectedData_<T> &value);
    ~XProtectedWrite_();
    T &data();
    void reset(T *data);
protected:
    void lock(XProtectedData_<T> *value);
    void unlock();
    XProtectedData_<T> *value_ = nullptr;
};

//---------------------------------------
//Тип защищенных данных с мютексом,
//и класс DataAccess, который блокирует данные в конструкторе, и разблокирует в деструкторе
//Применение:
//Если есть наследник data типа XcluProtectedData *, то
//DataAccess access(data); - создаст блокировку данных
//Это должны делать все, кто работают с данными

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
