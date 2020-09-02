#include "xcluarray.h"
#include "incl_cpp.h"

//---------------------------------------------------------------------
//размер одного элемента данных
unsigned int XcluArrayDataTypeSize(XcluArrayDataType type) {
    switch (type) {
    case XcluArrayDataType_none:
        return 0;
    case XcluArrayDataType_u8bit:
        return 1;
    case XcluArrayDataType_s8bit:
        return 1;
    case XcluArrayDataType_int16:
        return 2;
    case XcluArrayDataType_uint16:
        return 2;
    case XcluArrayDataType_int32:
        return 4;
    case XcluArrayDataType_uint32:
        return 4;
    case XcluArrayDataType_float:
        return 4;
    case XcluArrayDataType_double:
        return 8;
    default:
        xclu_exception(QString("Unknown XcluArrayDataType %1").arg(type));
        break;
    }
    return 0;
}

//---------------------------------------------------------------------
QString XcluArrayDataType_to_string(XcluArrayDataType type) {
    switch (type) {
    case XcluArrayDataType_none:
        return "";
    case XcluArrayDataType_u8bit:
        return "u8bit";
    case XcluArrayDataType_s8bit:
        return "s8bit";
    case XcluArrayDataType_int16:
        return "int16";
    case XcluArrayDataType_uint16:
        return "uint16";
    case XcluArrayDataType_int32:
        return "int32";
    case XcluArrayDataType_uint32:
        return "uint32";
    case XcluArrayDataType_float:
        return "float";
    case XcluArrayDataType_double:
        return "double";
    default:
        xclu_exception(QString("Unknown XcluArrayDataType %1").arg(type));
        break;
    }
    return 0;
}

//---------------------------------------------------------------------
XcluArrayDataType string_to_XcluArrayDataType(QString type) {
    if (type == "none") return XcluArrayDataType_none;
    if (type == "u8bit") return XcluArrayDataType_u8bit;
    if (type == "s8bit") return XcluArrayDataType_s8bit;
    if (type == "int16") return XcluArrayDataType_int16;
    if (type == "uint16") return XcluArrayDataType_uint16;
    if (type == "int32") return XcluArrayDataType_int32;
    if (type == "uint32") return XcluArrayDataType_uint32;
    if (type == "float") return XcluArrayDataType_float;
    if (type == "double") return XcluArrayDataType_double;
    xclu_exception(QString("Unknown XcluArrayDataType '%1'").arg(type));
    return XcluArrayDataType_none;
}

//---------------------------------------------------------------------
bool is_XcluArrayDataType_integer(XcluArrayDataType type) {
    switch (type) {
    case XcluArrayDataType_none:
        return false;
    case XcluArrayDataType_u8bit:
        return true;
    case XcluArrayDataType_s8bit:
        return true;
    case XcluArrayDataType_int16:
        return true;
    case XcluArrayDataType_uint16:
        return true;
    case XcluArrayDataType_int32:
        return true;
    case XcluArrayDataType_uint32:
        return true;
    case XcluArrayDataType_float:
        return false;
    case XcluArrayDataType_double:
        return false;
    default:
        xclu_exception(QString("Unknown XcluArrayDataType %1").arg(type));
        break;
    }
    return 0;
}

//---------------------------------------------------------------------
bool is_XcluArrayDataType_float(XcluArrayDataType type) {
    if (type == XcluArrayDataType_none) return false;
    return !is_XcluArrayDataType_integer(type);
}

//---------------------------------------------------------------------
XcluArray::XcluArray()
{

}

//---------------------------------------------------------------------
void XcluArray::clear() {
    size_ = 0;
    size_bytes_ = 0;
    elem_size_ = 0;
    data_type_ = XcluArrayDataType_none;
    dim_.clear();
    dims_ = 0;
    data_.clear();
    data_ptr_ = nullptr;

    index_mult_.clear();


}

//---------------------------------------------------------------------
void XcluArray::fill(int v) {
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
void XcluArray::fill(double v) {
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
void XcluArray::allocate(QVector<quint32> dim, XcluArrayDataType data_type) {
    quint32 size = 1;
    for (int i=0; i<dim.size(); i++) {
        size *= dim[i];
    }
    xclu_assert(size>=0, QString("Bad total array size %1").arg(size));
    quint32 elem_size = XcluArrayDataTypeSize(data_type);
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
void XcluArray::allocate_1d(unsigned int size, XcluArrayDataType data_type) {
    QVector<unsigned int> dim(1);
    dim[0] = size;
    allocate(dim, data_type);
}

//---------------------------------------------------------------------
void XcluArray::allocate_image(int channels, int w, int h, XcluArrayDataType data_type) {
    QVector<unsigned int> dim(3);
    dim[0] = channels;
    dim[1] = w;
    dim[2] = h;
    allocate(dim, data_type);
}

//---------------------------------------------------------------------
XcluArrayDataType XcluArray::data_type() const {
    return data_type_;
}

//---------------------------------------------------------------------
unsigned int XcluArray::size() const {    //число элементов
    return size_;
}

//---------------------------------------------------------------------
unsigned int XcluArray::size_bytes() const {  //размер массива в байтах
    return size_bytes_;
}

//---------------------------------------------------------------------
unsigned int XcluArray::elem_size() const {    //размер одного элемента
    return elem_size_;
}

//---------------------------------------------------------------------
bool XcluArray::is_empty() const {
    return size_bytes_ == 0;
}

//---------------------------------------------------------------------
const QVector<quint32> &XcluArray::dim() const {
    return dim_;
}

//---------------------------------------------------------------------
int XcluArray::dims() const {
    return dims_;
}

//---------------------------------------------------------------------
int XcluArray::image_channels() const {
    xclu_assert(dim_.size() == 3, "Can't get image array channels count - it's not an image");
    return dim_.at(0);
}

//---------------------------------------------------------------------
int XcluArray::w() const {
    xclu_assert(dims_ == 3, "Can't get image array width - it's not an image");
    return dim_.at(1);
}

//---------------------------------------------------------------------
int XcluArray::h() const {
    xclu_assert(dims_ == 3, "Can't get image array height - it's not an image");
    return dim_.at(2);
}


//---------------------------------------------------------------------
inline bool XcluArray::is_int() const {      //это целочисленный массив
    return is_XcluArrayDataType_integer(data_type_);
}

//---------------------------------------------------------------------
inline bool XcluArray::is_float() const {    //это массив float
    return data_type_ == XcluArrayDataType_float;
}

//---------------------------------------------------------------------
inline bool XcluArray::is_double() const {    //это массив double
    return data_type_ == XcluArrayDataType_double;
}

//---------------------------------------------------------------------
//перевести вектор индексов в одномерный индекс
inline quint32 XcluArray::to_index(const QVector<quint32> &index_vec) const {
    xclu_assert(index_vec.size() == dims_, "Bad index vector for array access");
    quint32 ind = 1;
    for (int i = 0; i<dims_; i++) {
        ind += index_vec[i] * index_mult_[i];
    }
    return ind;
}

//---------------------------------------------------------------------
inline quint32 XcluArray::pixel_index(int channel, int x, int y) const {
    xclu_assert(dims_ == 3, "Bad dimensions number for image array access");
    return channel + dim_.at(0) * (x + dim_.at(1) * y);
}

//---------------------------------------------------------------------
//получение ссылки на элемент массива
void *XcluArray::item_pointer(qint32 index) {
    return data_ptr_ + (index * elem_size_);
}

void const *XcluArray::item_pointer(qint32 index) const {
    return data_ptr_ + (index * elem_size_);
}

//---------------------------------------------------------------------
void *XcluArray::pixel_pointer(int x, int y) { //для изображений
    return data_ptr_ + pixel_index(0,x,y) * elem_size_;
}

void const *XcluArray::pixel_pointer(int x, int y) const { //для изображений
    return data_ptr_ + pixel_index(0,x,y) * elem_size_;
}

//---------------------------------------------------------------------
int XcluArray::geti(qint32 index) const {
    xclu_assert(index >= 0 && index < size_, "Bad index for array access");
    switch (data_type_) {
    case XcluArrayDataType_u8bit:
        return data_u8bit()[index];
    case XcluArrayDataType_s8bit:
        return data_s8bit()[index];
    case XcluArrayDataType_int16:
        return data_int16()[index];
    case XcluArrayDataType_uint16:
        return data_uint16()[index];
    case XcluArrayDataType_int32:
        return data_int32()[index];
    case XcluArrayDataType_uint32:
        return data_uint32()[index];
    default:
        xclu_exception("Can't get integer value for array");
        break;
    }
    return 0;
}


//---------------------------------------------------------------------
void XcluArray::seti(qint32 index, int v) {
    xclu_assert(index >= 0 && index < size_, "Bad index for array access");
    switch (data_type_) {
    case XcluArrayDataType_u8bit:
        data_u8bit()[index] = v;
        break;
    case XcluArrayDataType_s8bit:
        data_s8bit()[index] = v;
        break;
    case XcluArrayDataType_int16:
        data_int16()[index] = v;
        break;
    case XcluArrayDataType_uint16:
        data_uint16()[index] = v;
        break;
    case XcluArrayDataType_int32:
        data_int32()[index] = v;
        break;
    case XcluArrayDataType_uint32:
        data_uint32()[index] = v;
        break;
    default:
        xclu_exception("Can't set integer value for array");
        break;
    }
}

//---------------------------------------------------------------------
float XcluArray::getf(qint32 index) const {
    xclu_assert(index >= 0 && index < size_, "Bad index for array access");
    switch (data_type_) {
    case XcluArrayDataType_float:
        return data_float()[index];
    case XcluArrayDataType_double:
        return data_double()[index];
    default:
        xclu_exception("Can't get float value for array");
        break;
    }
    return 0;
}

//---------------------------------------------------------------------
void XcluArray::setf(qint32 index, float v) {
    xclu_assert(index >= 0 && index < size_, "Bad index for array access");
    switch (data_type_) {
    case XcluArrayDataType_float:
        data_float()[index] = v;
        break;
    case XcluArrayDataType_double:
        data_double()[index] = v;
        break;
    default:
        xclu_exception("Can't set float value for array");
        break;
    }
}

//---------------------------------------------------------------------
double XcluArray::get_double(qint32 index) const {
    xclu_assert(index >= 0 && index < size_, "Bad index for array access");
    switch (data_type_) {
    case XcluArrayDataType_float:
        return data_float()[index];
    case XcluArrayDataType_double:
        return data_double()[index];
    default:
        xclu_exception("Can't get double value for array");
        break;
    }
    return 0;
}

//---------------------------------------------------------------------
void XcluArray::set_double(qint32 index, double v) {
    xclu_assert(index >= 0 && index < size_, "Bad index for array access");
    switch (data_type_) {
    case XcluArrayDataType_float:
        data_float()[index] = v;
        break;
    case XcluArrayDataType_double:
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
quint8* XcluArray::data_u8bit() {
    if (size_bytes_ == 0) return nullptr;
    xclu_assert(data_type_ == XcluArrayDataType_u8bit, "Array has no " "u8bit" " pointer");
    return (quint8*)(&data_[0]);
}

*/
#define XcluArray_get_data(TYPE_NAME,CPP_TYPE) \
    CPP_TYPE* XcluArray::data_##TYPE_NAME() { \
        if (size_bytes_ == 0) return nullptr; \
        xclu_assert(data_type_ == XcluArrayDataType_##TYPE_NAME, "Array has another type, can't get " #TYPE_NAME " pointer"); \
        return (CPP_TYPE*)(data_ptr_); \
    }

#define XcluArray_get_data_const(TYPE_NAME,CPP_TYPE) \
    CPP_TYPE const* XcluArray::data_##TYPE_NAME() const { \
        if (size_bytes_ == 0) return nullptr; \
        xclu_assert(data_type_ == XcluArrayDataType_##TYPE_NAME, "Array has another type, can't get " #TYPE_NAME " pointer"); \
        return (CPP_TYPE*)(data_ptr_); \
    }

XcluArray_get_data(u8bit, quint8)
XcluArray_get_data(s8bit, qint8)
XcluArray_get_data(int16, qint16)
XcluArray_get_data(uint16, quint16)
XcluArray_get_data(int32, qint32)
XcluArray_get_data(uint32, quint32)
XcluArray_get_data(float, float)
XcluArray_get_data(double, double)


XcluArray_get_data_const(u8bit, quint8)
XcluArray_get_data_const(s8bit, qint8)
XcluArray_get_data_const(int16, qint16)
XcluArray_get_data_const(uint16, quint16)
XcluArray_get_data_const(int32, qint32)
XcluArray_get_data_const(uint32, quint32)
XcluArray_get_data_const(float, float)
XcluArray_get_data_const(double, double)

void* XcluArray::data() {
    return data_ptr_;
}
void const* XcluArray::data() const {
    return data_ptr_;
}


//---------------------------------------------------------------------
