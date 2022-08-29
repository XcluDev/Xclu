#ifndef XCLUPROTECTEDDATA_H
#define XCLUPROTECTEDDATA_H

#include <QMutex>
#include <QReadWriteLock>
#include "incl_h.h"
#include "xwaschanged.h"


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

//Class for representing data.
//Also it supports tracing of changes automatically, at calling "write"
//It's ok, because nobody can "read" while writing
template<typename T>
class XProtectedData_: public XWasChangedKeeper {
public:
    XProtectedData_() { data_.reset(new T); }
    XProtectedData_(T *data) { data_.reset(data); }
    //creates reader
    XProtectedRead_<T> read() { return XProtectedRead_<T>(this); }
    //creates writer
    XProtectedWrite_<T> write() {
        //touch() will be called during XProtectedWrite_<T>::lock()
        return XProtectedWrite_<T>(this);
    }

    //clear - only for those supports it!
    //Note: it's uses write(), so use with care - not use if other write() for object created
    void clear() {
        write().data().clear();
    }

    //Mechanism for test changing
    //Mark that value was changed - it's done automatically at "write" calling
    //void touch();

    //Check if was change relative to the checker
    //bool was_changed(XWasChangedChecker &checker) const;

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
    virtual ~XProtectedRead_() { unlock(); }
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

    virtual ~XProtectedWrite_() { unlock(); }
    T &data() { return *value_->data_.data(); }
    T *pointer() { return value_->data_.data(); }
    void reset(T *data) { value_->data_.reset(data); }
protected:
    XProtectedData_<T> *value_ = nullptr;

    void lock(XProtectedData_<T> *value) {
        value_ = value;
        value_->lock_.lockForWrite();

        //notify keeper about value change!
        value_->touch();
    }
    void unlock() { value_->lock_.unlock(); }
};


#endif // XCLUPROTECTEDDATA_H
