#include "xcluprotecteddata.h"
#include "incl_cpp.h"

//---------------------------------------------------------------------
template<typename T>
XProtectedData_<T>::XProtectedData_(T *data) {
    data_.reset(data);
}

//---------------------------------------------------------------------
template<typename T>
XProtectedRead_<T> XProtectedData_<T>::read() {  //creates reader
    return XProtectedRead_<T>(this);
}

//---------------------------------------------------------------------
template<typename T>
XProtectedWrite_<T> XProtectedData_<T>::write() { //created writer
    return XProtectedWrite_<T>(this);
}

//---------------------------------------------------------------------
template<typename T>
XProtectedRead_<T>::XProtectedRead_(XProtectedData_<T> *value) {
    lock(value);
}

//---------------------------------------------------------------------
template<typename T>
XProtectedRead_<T>::XProtectedRead_(XProtectedData_<T> &value) {
    lock(&value);
}

//---------------------------------------------------------------------
template<typename T>
XProtectedRead_<T>::~XProtectedRead_() {
    unlock();
}

//---------------------------------------------------------------------
template<typename T>
void XProtectedRead_<T>::lock(XProtectedData_<T> *value) {
    value_ = value;
    value_->lock_.lockForRead();
}

//---------------------------------------------------------------------
template<typename T>
void XProtectedRead_<T>::unlock() {
    value_->lock_.unlock();
}

//---------------------------------------------------------------------
template<typename T>
const T &XProtectedRead_<T>::data() {
    return *value_->data_.data();
}

//---------------------------------------------------------------------
//---------------------------------------------------------------------
//---------------------------------------------------------------------
template<typename T>
XProtectedWrite_<T>::XProtectedWrite_(XProtectedData_<T> *value) {
    lock(value);
}

//---------------------------------------------------------------------
template<typename T>
XProtectedWrite_<T>::XProtectedWrite_(XProtectedData_<T> &value) {
    lock(&value);
}

//---------------------------------------------------------------------
template<typename T>
XProtectedWrite_<T>::~XProtectedWrite_() {
    unlock();
}

//---------------------------------------------------------------------
template<typename T>
T &XProtectedWrite_<T>::data() {
    return *value_->data_.data();
}

//---------------------------------------------------------------------
template<typename T>
void XProtectedWrite_<T>::reset(T *data) {
    return *value_->data_.reset(data);
}

//---------------------------------------------------------------------
template<typename T>
void XProtectedWrite_<T>::lock(XProtectedData_<T> *value) {
    value_ = value;
    value_->lock_.lockForWrite();
}

//---------------------------------------------------------------------
template<typename T>
void XProtectedWrite_<T>::unlock() {
    value_->lock_.unlock();
}

//---------------------------------------------------------------------
