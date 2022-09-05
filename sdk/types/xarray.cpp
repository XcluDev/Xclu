#include "xarray.h"
#include "./../utility/xerrorhandling.h"
#include "incl_cpp.h"

//---------------------------------------------------------------------
void XArray::set_type(XType type) {
    this->type = type;
    sizeofitem = XType_bytes(type);
}

void XArray::assert_type(XType type) const {
    xc_assert(type == type, QString("XArray::assert_type error, expected %1 but has %2")
              .arg(XType_to_string(type))
              .arg(XType_to_string(type)));
}

// Useful wrapper that checks if data is empty
// Note: it's invalidates and updates after re-allocation, so you must care of it and not use old pointer.
// XArray has typed variant: typed_data_pointer()
void* XArray::data_pointer() {
    if (is_empty()) return nullptr;
    return data_pointer_;
}
const void* XArray::data_pointer() const {
    if (is_empty()) return nullptr;
    return data_pointer_;
}

template<class T> T* XArray::data() {
    if (is_empty()) return nullptr;
    assert_type(cpptype_to_XType<T>());
    return (T*)data_pointer_;
}
template<class T> const T* XArray::data() const {
    if (is_empty()) return nullptr;
    assert_type(cpptype_to_XType<T>());
    return (T*)data_pointer_;
}

//----------------------------------------------------------------------------
int XArray::data_size_in_bytes() const {
    return sizeofitem*n;
}

//----------------------------------------------------------------------------
void* XArray::item_unsafe_ptr(int i) {
    return &data_pointer_[sizeofitem*(i)];
}
const void* XArray::item_unsafe_ptr(int i) const {
    return &data_pointer_[sizeofitem*(i)];
}
void XArray::set_item_unsafe_ptr(int i, const void *value) { // Note: value size must be sizeofitem
    memcpy(item_unsafe_ptr(i), value, sizeofitem);
}

//----------------------------------------------------------------------------
// Allocating - allocate own memory for raster
//----------------------------------------------------------------------------

// If 'reallocate is true - then old vector will be cleared.
// It's useful for clearing memory when image size if significantly reduced, but works slower.
void XArray::allocate(int n, XType type, bool reallocate) {
    if (!reallocate && is_owner && this->type == type) {
        return;
    }
    if (reallocate) {
        clear();
    }
    set_type(type);
    this->n = n;
    internal_data_.resize(n);
    data_pointer_ = internal_data_.data();
    is_owner = true;
}

//---------------------------------------------------------------------
template<class T> void XArray::allocate(int n, bool reallocate) {
    allocate(n, cpptype_to_XType(type), reallocate);
}

//---------------------------------------------------------------------
void XArray::copy_from(void* data, int n, XType type) {
    allocate(n, type);
    memcpy(data_pointer_, data, data_size_in_bytes());
}

template<class T> void XArray::copy_from(T* data, int n) {
    copy_from(data, n, cpptype_to_XType<T>());
}

//----------------------------------------------------------------------------
XArray::XArray(const XArray& other) {
    *this = other;
}

//----------------------------------------------------------------------------
XArray& XArray::operator=(const XArray& other)
{
    // Guard self assignment
    if (this == &other)
        return *this;

    n = other.n;
    sizeofitem = other.sizeofitem;
    type = other.type;
    is_owner = other.is_owner;
    internal_data_ = other.internal_data_;

    // Основная цель определения оператора копирования - правильно поставить data_pointer_
    data_pointer_ = (is_owner) ? internal_data_.data() : other.data_pointer_;

    return *this;
}

//---------------------------------------------------------------------
void XArray::clear() {
    n = sizeofitem = 0;
    data_pointer_ = nullptr;

    if (is_owner) {
        //clear data (note: data.clear() does not!)
        //https://stackoverflow.com/questions/13944886/is-stdvector-memory-freed-upon-a-clear
        QVector<quint8>().swap(internal_data_);
    }
}

//---------------------------------------------------------------------
bool XArray::is_empty() const {
    return data_pointer_ == nullptr || n <= 0 || sizeofitem <= 0;
}

//---------------------------------------------------------------------
bool XArray::is_valid() const {
    if (is_empty()) return false;
    if (!is_owner) return true;
    return internal_data_.size() == data_size_in_bytes();
}

//---------------------------------------------------------------------
void XArray::link_data(void* data, int n, XType type) {
    xc_assert(n > 0, "Error XArray::link() - bad dimensions");
    xc_assert(data, "Error XArray::link() - data is nullptr");
    clear();
    is_owner = false;
    this->n = n;
    set_type(type);
    data_pointer_ = (quint8*) data;
}

template<class T> void XArray::link_data(T* data, int n) {
    link_data(data, n, cpptype_to_XType<T>());
}

//---------------------------------------------------------------------
void XArray::add_inplace(const XArray &a) {
    xc_assert(a.n == n, "XArray add error, argument raster has different size");
    code_for_all_basic_XType(type, \
    for (int i=0; i<n; i++) { \
        item_unsafe<T>(i) += a.item_unsafe<const T>(i); \
    });
}

//---------------------------------------------------------------------
void XArray::mult_inplace(const XArray &a) {
    xc_assert(a.n, "XArray mult_by error, argument raster has different size");
    code_for_all_basic_XType(type, \
    for (int i=0; i<n; i++) { \
        item_unsafe<T>(i) *= a.item_unsafe<T>(i); \
    });
}

//---------------------------------------------------------------------

//---------------------------------------------------------------------
//Crop
XArray XArray::crop(int i0, int n0) const {
    xc_assert(i0 >= 0 && n0 >= 0 && i0+n0 <= n,
              "XArray crop - bad arguments");
    XArray array;
    array.allocate(n0, type);
    for (int i = 0; i < n0; i++) {
        array.set_item_unsafe(i, item_unsafe<void*>(i0+i));
    }
    return array;
}

//---------------------------------------------------------------------
/*float pixel_linear(float x) {
   alg_assert(x >= 0 && y >= 0 && x <= w - 1 && y <= h - 1, "pixel_bilinear error - bad coords", Alg_Error_Algorithm);
   int xi = int(x);
   int yi = int(y);
   float tx = x - xi;
   float ty = y - yi;
   int xi1 = min(xi + 1, w - 1);
   int yi1 = min(yi + 1, h - 1);
   return item_unsafe(xi, yi) * (1 - tx) * (1 - ty)
       + item_unsafe(xi1, yi) * (tx) * (1 - ty)
       + item_unsafe(xi1, yi1) * (tx) * (ty)
       + item_unsafe(xi, yi1) * (1 - tx) * (ty);
}*/
//-----------------------------------------------------------------------------------
