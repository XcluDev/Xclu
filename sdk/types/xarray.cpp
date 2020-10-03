#include "xarray.h"
#include "incl_cpp.h"

//---------------------------------------------------------------------
XArray::XArray()
{

}

//---------------------------------------------------------------------
void XArray::clear() {
    size_ = 0;
    size_bytes_ = 0;
    elem_size_ = 0;
    data_type_ = XTypeId_none;
    data_.clear();
    data_ptr_ = nullptr;

}

//---------------------------------------------------------------------
void XArray::fill(int v) {
    if (is_empty()) return;
    if (is_int()) {
        for (quint32 i=0; i<size_; i++) {
            seti(i, v);
        }
        return;
    }
    fill(double(v));
}

//---------------------------------------------------------------------
void XArray::fill(double v) {
    if (is_empty()) return;
    xclu_assert(is_float() || is_double(), "It's allowed to fill only float and double arrays with floats");
    if (is_float()) {
        for (quint32 i=0; i<size_; i++) {
            setf(i, v);
        }
    }
    if (is_double()) {
        for (quint32 i=0; i<size_; i++) {
            set_double(i, v);
        }
    }
}


//---------------------------------------------------------------------
void XArray::allocate(unsigned int size, XTypeId data_type) {
    xclu_assert(size>=0, QString("Bad total array size %1").arg(size));
    quint32 elem_size = XTypeIdSize(data_type);
    quint32 size_bytes = elem_size * size;

    //data
    if (size_bytes != size_bytes_) {
        data_.resize(size_bytes);
        data_ptr_ = &data_[0];
    }

    //parameters
    data_type_ = data_type;
    size_ = size;
    size_bytes_ = size_bytes;
    elem_size_ = elem_size;
}


//---------------------------------------------------------------------
XTypeId XArray::data_type() const {
    return data_type_;
}

//---------------------------------------------------------------------
unsigned int XArray::size() const {    //число элементов
    return size_;
}

//---------------------------------------------------------------------
unsigned int XArray::size_bytes() const {  //размер массива в байтах
    return size_bytes_;
}

//---------------------------------------------------------------------
unsigned int XArray::elem_size() const {    //размер одного элемента
    return elem_size_;
}

//---------------------------------------------------------------------
bool XArray::is_empty() const {
    return size_bytes_ == 0;
}


//---------------------------------------------------------------------
inline bool XArray::is_int() const {      //это целочисленный массив
    return is_XTypeId_integer(data_type_);
}

//---------------------------------------------------------------------
inline bool XArray::is_float() const {    //это массив float
    return data_type_ == XTypeId_float;
}

//---------------------------------------------------------------------
inline bool XArray::is_double() const {    //это массив double
    return data_type_ == XTypeId_double;
}

//---------------------------------------------------------------------
//получение ссылки на элемент массива
void *XArray::item_pointer(qint32 index) {
    return data_ptr_ + (index * elem_size_);
}

void const *XArray::item_pointer(qint32 index) const {
    return data_ptr_ + (index * elem_size_);
}

//---------------------------------------------------------------------
int XArray::geti(qint32 index) const {
    xclu_assert(index >= 0 && index < size_, "Bad index for array access");
    switch (data_type_) {
    case XTypeId_u8:
        return data_u8()[index];
    case XTypeId_s8:
        return data_s8()[index];
    case XTypeId_int16:
        return data_int16()[index];
    case XTypeId_u16:
        return data_u16()[index];
    case XTypeId_int32:
        return data_int32()[index];
    case XTypeId_u32:
        return data_u32()[index];
    default:
        xclu_exception("Can't get integer value for array");
        break;
    }
    return 0;
}


//---------------------------------------------------------------------
void XArray::seti(qint32 index, int v) {
    xclu_assert(index >= 0 && index < size_, "Bad index for array access");
    switch (data_type_) {
    case XTypeId_u8:
        data_u8()[index] = v;
        break;
    case XTypeId_s8:
        data_s8()[index] = v;
        break;
    case XTypeId_int16:
        data_int16()[index] = v;
        break;
    case XTypeId_u16:
        data_u16()[index] = v;
        break;
    case XTypeId_int32:
        data_int32()[index] = v;
        break;
    case XTypeId_u32:
        data_u32()[index] = v;
        break;
    default:
        xclu_exception("Can't set integer value for array");
        break;
    }
}

//---------------------------------------------------------------------
float XArray::getf(qint32 index) const {
    xclu_assert(index >= 0 && index < size_, "Bad index for array access");
    switch (data_type_) {
    case XTypeId_float:
        return data_float()[index];
    case XTypeId_double:
        return data_double()[index];
    default:
        xclu_exception("Can't get float value for array");
        break;
    }
    return 0;
}

//---------------------------------------------------------------------
void XArray::setf(qint32 index, float v) {
    xclu_assert(index >= 0 && index < size_, "Bad index for array access");
    switch (data_type_) {
    case XTypeId_float:
        data_float()[index] = v;
        break;
    case XTypeId_double:
        data_double()[index] = v;
        break;
    default:
        xclu_exception("Can't set float value for array");
        break;
    }
}

//---------------------------------------------------------------------
double XArray::get_double(qint32 index) const {
    xclu_assert(index >= 0 && index < size_, "Bad index for array access");
    switch (data_type_) {
    case XTypeId_float:
        return data_float()[index];
    case XTypeId_double:
        return data_double()[index];
    default:
        xclu_exception("Can't get double value for array");
        break;
    }
    return 0;
}

//---------------------------------------------------------------------
void XArray::set_double(qint32 index, double v) {
    xclu_assert(index >= 0 && index < size_, "Bad index for array access");
    switch (data_type_) {
    case XTypeId_float:
        data_float()[index] = v;
        break;
    case XTypeId_double:
        data_double()[index] = v;
        break;
    default:
        xclu_exception("Can't set double value for array");
        break;
    }
}

//---------------------------------------------------------------------
/*
получение массивов данных для быстрой работы
quint8* XArray::data_u8() {
    if (size_bytes_ == 0) return nullptr;
    xclu_assert(data_type_ == XTypeId_u8, "Array has no " "u8" " pointer");
    return (quint8*)(&data_[0]);
}

*/
#define XArray_get_data(TYPE_NAME,CPP_TYPE) \
    CPP_TYPE* XArray::data_##TYPE_NAME() { \
        if (size_bytes_ == 0) return nullptr; \
        xclu_assert(data_type_ == XTypeId_##TYPE_NAME, "Array has another type, can't get " #TYPE_NAME " pointer"); \
        return (CPP_TYPE*)(data_ptr_); \
    }

#define XArray_get_data_const(TYPE_NAME,CPP_TYPE) \
    CPP_TYPE const* XArray::data_##TYPE_NAME() const { \
        if (size_bytes_ == 0) return nullptr; \
        xclu_assert(data_type_ == XTypeId_##TYPE_NAME, "Array has another type, can't get " #TYPE_NAME " pointer"); \
        return (CPP_TYPE*)(data_ptr_); \
    }

XArray_get_data(u8, quint8)
XArray_get_data(s8, qint8)
XArray_get_data(int16, qint16)
XArray_get_data(u16, quint16)
XArray_get_data(int32, qint32)
XArray_get_data(u32, quint32)
XArray_get_data(float, float)
XArray_get_data(double, double)


XArray_get_data_const(u8, quint8)
XArray_get_data_const(s8, qint8)
XArray_get_data_const(int16, qint16)
XArray_get_data_const(u16, quint16)
XArray_get_data_const(int32, qint32)
XArray_get_data_const(u32, quint32)
XArray_get_data_const(float, float)
XArray_get_data_const(double, double)

void* XArray::data() {
    return data_ptr_;
}
void const* XArray::data() const {
    return data_ptr_;
}


//---------------------------------------------------------------------
