#include "xarray_multi.h"
#include "incl_cpp.h"

//---------------------------------------------------------------------
XArrayMulti::XArrayMulti()
{

}

//---------------------------------------------------------------------
void XArrayMulti::clear() {
    size_ = 0;
    size_bytes_ = 0;
    elem_size_ = 0;
    data_type_ = XTypeId_none;
    dim_.clear();
    dims_ = 0;
    data_.clear();
    data_ptr_ = nullptr;

    index_mult_.clear();


}

//---------------------------------------------------------------------
void XArrayMulti::fill(int v) {
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
void XArrayMulti::fill(double v) {
    if (is_empty()) return;
    xc_assert(is_float() || is_double(), "It's allowed to fill only float and double arrays with floats");
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
void XArrayMulti::allocate(QVector<quint32> dim, XTypeId data_type) {
    quint32 size = 1;
    for (int i=0; i<dim.size(); i++) {
        size *= dim[i];
    }
    xc_assert(size>=0, QString("Bad total array size %1").arg(size));
    quint32 elem_size = XTypeIdSize(data_type);
    quint32 size_bytes = elem_size * size;

    //данные
    if (size_bytes != size_bytes_) {
        data_.resize(size_bytes);
        data_ptr_ = &data_[0];
    }

    //быстрое вычисление индексов
    if (dim != dim_) {
        int dims = dim.size();
        if (dims > 1) {
            index_mult_.resize(dims-1);
            quint32 mult = 1;
            for (int i=0; i<dims-1; i++) {
                mult *= dim[i];
                index_mult_[i] = mult;
            }
        }
        else {
            index_mult_.clear();
        }
    }

    //основные параметры
    data_type_ = data_type;
    dim_ = dim;
    dims_ = dim.size();
    size_ = size;
    size_bytes_ = size_bytes;
    elem_size_ = elem_size;


}

//---------------------------------------------------------------------
void XArrayMulti::allocate_1d(unsigned int size, XTypeId data_type) {
    QVector<unsigned int> dim(1);
    dim[0] = size;
    allocate(dim, data_type);
}

//---------------------------------------------------------------------
void XArrayMulti::allocate_image(int channels, int w, int h, XTypeId data_type) {
    QVector<unsigned int> dim(3);
    dim[0] = channels;
    dim[1] = w;
    dim[2] = h;
    allocate(dim, data_type);
}

//---------------------------------------------------------------------
XTypeId XArrayMulti::data_type() const {
    return data_type_;
}

//---------------------------------------------------------------------
unsigned int XArrayMulti::size() const {    //число элементов
    return size_;
}

//---------------------------------------------------------------------
unsigned int XArrayMulti::size_bytes() const {  //размер массива в байтах
    return size_bytes_;
}

//---------------------------------------------------------------------
unsigned int XArrayMulti::elem_size() const {    //размер одного элемента
    return elem_size_;
}

//---------------------------------------------------------------------
bool XArrayMulti::is_empty() const {
    return size_bytes_ == 0;
}

//---------------------------------------------------------------------
const QVector<quint32> &XArrayMulti::dim() const {
    return dim_;
}

//---------------------------------------------------------------------
int XArrayMulti::dims() const {
    return dims_;
}

//---------------------------------------------------------------------
int XArrayMulti::image_channels() const {
    xc_assert(dim_.size() == 3, "Can't get image array channels count - it's not an image");
    return dim_.at(0);
}

//---------------------------------------------------------------------
int XArrayMulti::w() const {
    xc_assert(dims_ == 3, "Can't get image array width - it's not an image");
    return dim_.at(1);
}

//---------------------------------------------------------------------
int XArrayMulti::h() const {
    xc_assert(dims_ == 3, "Can't get image array height - it's not an image");
    return dim_.at(2);
}


//---------------------------------------------------------------------
inline bool XArrayMulti::is_int() const {      //это целочисленный массив
    return is_XTypeId_integer(data_type_);
}

//---------------------------------------------------------------------
inline bool XArrayMulti::is_float() const {    //это массив float
    return data_type_ == XTypeId_float;
}

//---------------------------------------------------------------------
inline bool XArrayMulti::is_double() const {    //это массив double
    return data_type_ == XTypeId_double;
}

//---------------------------------------------------------------------
//перевести вектор индексов в одномерный индекс
inline quint32 XArrayMulti::to_index(const QVector<quint32> &index_vec) const {
    xc_assert(index_vec.size() == dims_, "Bad index vector for array access");
    quint32 ind = 1;
    for (int i = 0; i<dims_; i++) {
        ind += index_vec[i] * index_mult_[i];
    }
    return ind;
}

//---------------------------------------------------------------------
inline quint32 XArrayMulti::pixel_index(int channel, int x, int y) const {
    xc_assert(dims_ == 3, "Bad dimensions number for image array access");
    return channel + dim_.at(0) * (x + dim_.at(1) * y);
}

//---------------------------------------------------------------------
//получение ссылки на элемент массива
void *XArrayMulti::item_pointer(qint32 index) {
    return data_ptr_ + (index * elem_size_);
}

void const *XArrayMulti::item_pointer(qint32 index) const {
    return data_ptr_ + (index * elem_size_);
}

//---------------------------------------------------------------------
void *XArrayMulti::pixel_pointer(int x, int y) { //для изображений
    return data_ptr_ + pixel_index(0,x,y) * elem_size_;
}

void const *XArrayMulti::pixel_pointer(int x, int y) const { //для изображений
    return data_ptr_ + pixel_index(0,x,y) * elem_size_;
}

//---------------------------------------------------------------------
int XArrayMulti::geti(qint32 index) const {
    xc_assert(index >= 0 && index < size_, "Bad index for array access");
    switch (data_type_) {
    case XTypeId_u8:
        return data_u8()[index];
    case XTypeId_s8:
        return data_s8()[index];
    case XTypeId_int16:
        return data_int16()[index];
    case XTypeId_uint16:
        return data_uint16()[index];
    case XTypeId_int32:
        return data_int32()[index];
    case XTypeId_uint32:
        return data_uint32()[index];
    default:
        xc_exception("Can't get integer value for array");
        break;
    }
    return 0;
}


//---------------------------------------------------------------------
void XArrayMulti::seti(qint32 index, int v) {
    xc_assert(index >= 0 && index < size_, "Bad index for array access");
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
    case XTypeId_uint16:
        data_uint16()[index] = v;
        break;
    case XTypeId_int32:
        data_int32()[index] = v;
        break;
    case XTypeId_uint32:
        data_uint32()[index] = v;
        break;
    default:
        xc_exception("Can't set integer value for array");
        break;
    }
}

//---------------------------------------------------------------------
float XArrayMulti::getf(qint32 index) const {
    xc_assert(index >= 0 && index < size_, "Bad index for array access");
    switch (data_type_) {
    case XTypeId_float:
        return data_float()[index];
    case XTypeId_double:
        return data_double()[index];
    default:
        xc_exception("Can't get float value for array");
        break;
    }
    return 0;
}

//---------------------------------------------------------------------
void XArrayMulti::setf(qint32 index, float v) {
    xc_assert(index >= 0 && index < size_, "Bad index for array access");
    switch (data_type_) {
    case XTypeId_float:
        data_float()[index] = v;
        break;
    case XTypeId_double:
        data_double()[index] = v;
        break;
    default:
        xc_exception("Can't set float value for array");
        break;
    }
}

//---------------------------------------------------------------------
double XArrayMulti::get_double(qint32 index) const {
    xc_assert(index >= 0 && index < size_, "Bad index for array access");
    switch (data_type_) {
    case XTypeId_float:
        return data_float()[index];
    case XTypeId_double:
        return data_double()[index];
    default:
        xc_exception("Can't get double value for array");
        break;
    }
    return 0;
}

//---------------------------------------------------------------------
void XArrayMulti::set_double(qint32 index, double v) {
    xc_assert(index >= 0 && index < size_, "Bad index for array access");
    switch (data_type_) {
    case XTypeId_float:
        data_float()[index] = v;
        break;
    case XTypeId_double:
        data_double()[index] = v;
        break;
    default:
        xc_exception("Can't set double value for array");
        break;
    }
}

//---------------------------------------------------------------------
/*
получение массивов данных для быстрой работы
quint8* XArrayMulti::data_u8() {
    if (size_bytes_ == 0) return nullptr;
    xc_assert(data_type_ == XTypeId_u8, "Array has no " "u8" " pointer");
    return (quint8*)(&data_[0]);
}

*/
#define XArray_get_data(TYPE_NAME,CPP_TYPE) \
    CPP_TYPE* XArrayMulti::data_##TYPE_NAME() { \
        if (size_bytes_ == 0) return nullptr; \
        xc_assert(data_type_ == XTypeId_##TYPE_NAME, "Array has another type, can't get " #TYPE_NAME " pointer"); \
        return (CPP_TYPE*)(data_ptr_); \
    }

#define XArray_get_data_const(TYPE_NAME,CPP_TYPE) \
    CPP_TYPE const* XArrayMulti::data_##TYPE_NAME() const { \
        if (size_bytes_ == 0) return nullptr; \
        xc_assert(data_type_ == XTypeId_##TYPE_NAME, "Array has another type, can't get " #TYPE_NAME " pointer"); \
        return (CPP_TYPE*)(data_ptr_); \
    }

XArray_get_data(u8, quint8)
XArray_get_data(s8, qint8)
XArray_get_data(int16, qint16)
XArray_get_data(uint16, quint16)
XArray_get_data(int32, qint32)
XArray_get_data(uint32, quint32)
XArray_get_data(float, float)
XArray_get_data(double, double)


XArray_get_data_const(u8, quint8)
XArray_get_data_const(s8, qint8)
XArray_get_data_const(int16, qint16)
XArray_get_data_const(uint16, quint16)
XArray_get_data_const(int32, qint32)
XArray_get_data_const(uint32, quint32)
XArray_get_data_const(float, float)
XArray_get_data_const(double, double)

void* XArrayMulti::data() {
    return data_ptr_;
}
void const* XArrayMulti::data() const {
    return data_ptr_;
}


//---------------------------------------------------------------------
