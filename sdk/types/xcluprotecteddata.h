#ifndef XCLUPROTECTEDDATA_H
#define XCLUPROTECTEDDATA_H

#include <QMutex>
#include <QReadWriteLock>
#include "incl_h.h"

//Wrapper for data protection, with multiple-read and single-write features
//Classes: XProtectedData_<T>, XProtectedRead_<T>, XProtectedWrite_<T>
//Usage:
//1. define object
//    XProtectedData_<float> value;
//2. write by creating 'write' value in scope
//    auto write = value.write();
//    float &data = write.data();   //- can change data now
//when `write` goes out of scope and descructed - it unlocks `value`
//3. read by creating
//    auto read = value.read();
//    const float &data = read.data();   //- readed data
//when `read` goes out of scope and desctructed - it unlocks `value`
//
//For single operation - can use value.read().data(), value.write(), but be careful,
//not use such obtained data below in next code lines, you need mutex to do all correctly!

template<typename T>
class XProtectedRead_;

template<typename T>
class XProtectedWrite_;

//class for representing data
template<typename T>
class XProtectedData_ {
public:
    XProtectedData_() { data_.reset(new T); }
    XProtectedData_(T *data) { data_.reset(data); }
    //creates reader
    XProtectedRead_<T> read() { return XProtectedRead_<T>(this); }
    //creates writer
    XProtectedWrite_<T> write() { return XProtectedWrite_<T>(this); }
protected:
    QScopedPointer<T> data_;
    QReadWriteLock lock_;
    friend XProtectedRead_<T>;
    friend XProtectedWrite_<T>;
};

//class for reading data (multiple access)
template<typename T>
class XProtectedRead_ {
public:
    XProtectedRead_(XProtectedData_<T> *value) { lock(value); }
    XProtectedRead_(XProtectedData_<T> &value) { lock(&value); }
    ~XProtectedRead_() { unlock(); }
    const T &data() { return *value_->data_.data(); }
    const T *pointer() { return value_->data_.data(); }
protected:
    XProtectedData_<T> *value_ = nullptr;

    void lock(XProtectedData_<T> *value) {
        value_ = value;
        value_->lock_.lockForRead();
    }
    void unlock() { value_->lock_.unlock(); }
};

//class for writing data (single access)
template<typename T>
class XProtectedWrite_ {
public:
    XProtectedWrite_(XProtectedData_<T> *value) { lock(value); }
    XProtectedWrite_(XProtectedData_<T> &value) { lock(&value); }
    ~XProtectedWrite_() { unlock(); }
    T &data() { return *value_->data_.data(); }
    T *pointer() { return value_->data_.data(); }
    void reset(T *data) { value_->data_.reset(data); }
protected:
    XProtectedData_<T> *value_ = nullptr;

    void lock(XProtectedData_<T> *value) {
        value_ = value;
        value_->lock_.lockForWrite();
    }
    void unlock() { value_->lock_.unlock(); }
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
