#include "./../utility/console.h"
#include "xraster.h"
#include "incl_cpp.h"
#include <QImage>
#include <QImageReader>
#include <QImageWriter>
#include <QPainter>

//---------------------------------------------------------------------
/*XRaster_u8;
 XRaster_u8c3;
XRaster_s8;
XRaster_int16;
 XRaster_u16;
 XRaster_u32;
XRaster_int32;
XRaster_float;
 XRaster_double;
XRaster_vec2;
XRaster_vec3;
XRaster_int2;
*/

//---------------------------------------------------------------------
#define MACRO_XRaster_type(TYPE_RASTER, TYPE_ID) \
template<> XTypeId TYPE_RASTER::type() { \
    return TYPE_ID; \
}

MACRO_XRaster_type(XRaster_u8, XTypeId::u8)
MACRO_XRaster_type(XRaster_u8c3, XTypeId::u8c3)
MACRO_XRaster_type(XRaster_s8, XTypeId::s8)
MACRO_XRaster_type(XRaster_int16, XTypeId::int16)
MACRO_XRaster_type(XRaster_u16, XTypeId::uint16)
MACRO_XRaster_type(XRaster_int32, XTypeId::int32)
MACRO_XRaster_type(XRaster_u32, XTypeId::uint32)
MACRO_XRaster_type(XRaster_float, XTypeId::float32)
MACRO_XRaster_type(XRaster_double, XTypeId::float64)
MACRO_XRaster_type(XRaster_vec2, XTypeId::vec2)
MACRO_XRaster_type(XRaster_vec3, XTypeId::vec3)
MACRO_XRaster_type(XRaster_vec4, XTypeId::vec4)
MACRO_XRaster_type(XRaster_int2, XTypeId::int2)

//---------------------------------------------------------------------
void XRaster::set_type(XTypeId type_id) {
    this->type_id = type_id;
    bytes_per_pixel = XTypeId_bytes(type_id);
}

void XRaster::assert_type(XTypeId type) const {
    xc_assert(type_id == type, QString("XRaster::assert_type error, expected {0} but has {1}")
              .arg(XTypeId_to_string(type)
              .arg(XTypeId_to_string(type_id));
}

// Useful wrapper that checks if data is empty
// Note: it's invalidates and updates after re-allocation, so you must care of it and not use old pointer.
// XRaster_<T> has typed variant: typed_data_pointer()
void* XRaster::data_pointer() {
    if (is_empty()) return nullptr;
    return data_pointer_;
}
const void* XRaster::data_pointer() const {
    if (is_empty()) return nullptr;
    return data_pointer_;
}

int XRaster::data_size() const {
    return bytes_per_pixel*w*h;
}

int XRaster::bytes_per_line() const {
    return bytes_per_pixel*w;
}

//----------------------------------------------------------------------------
// Allocating - allocate own memory for raster
//----------------------------------------------------------------------------

// If 'reallocate is true - then old vector will be cleared.
// It's useful for clearing memory when image size if significantly reduced, but works slower.
void XRaster::allocate(int w, int h, XTypeId Type_id, bool reallocate = false) {
    if (!reallocate && is_owner && this->w == w && this->h == h && this->type_id == Type_id) {
        return;
    }
    if (reallocate) {
        clear();
    }
    set_type(Type_id);
    internal_data_.resize(w*h);
    data_pointer_ = internal_data_.data();
    this->w = w;
    this->h = h;
    is_owner = true;
}

void XRaster::copy_from(void* input_img, int w, int h, XTypeId Type_id) {
    allocate(w, h, Type_id);
    memcpy(data_pointer_, input_img, data_size());
}

void XRaster::clear() {
    w = h = bytes_per_pixel = 0;
    data_pointer_ = nullptr;

    if (is_owner) {
        //clear data (note: data.clear() does not!)
        //https://stackoverflow.com/questions/13944886/is-stdvector-memory-freed-upon-a-clear
        QVector<quint8>().swap(internal_data_);
    }
}
bool XRaster::is_empty() const {
    return data_pointer_ == nullptr || w <= 0 || h <= 0 || bytes_per_pixel <= 0;
}

bool XRaster::is_valid() const {
    if (is_empty()) return false;
    if (!is_owner) return true;
    return internal_data_.size() == data_size();
}

void XRaster::link_data(int w, int h, void* data, XTypeId type) {
    xc_assert(w > 0 && h > 0, "Error XRaster::link() - bad dimensions");
    xc_assert(data, "Error XRaster::link() - data is nullptr");
    clear();
    is_owner = false;
    this->w = w;
    this->h = h;
    set_type(type);
    data_pointer_ = (quint8*) data;
}

//---------------------------------------------------------------------
//maximal difference between two rasters at some point - used for checking if they are equal or different
template<>
float XRaster_<glm::vec2>::distance_C(XRaster_<glm::vec2> &compare_with) {
    float maxx = 0;
    for (int i=0; i<w*h; i++) {
        maxx = qMax(glm::distance2(pixel_unsafe(i), compare_with.pixel_unsafe(i)), maxx);
    }
    return qSqrt(maxx);
}

template<>
float XRaster_<glm::vec3>::distance_C(XRaster_<glm::vec3> &compare_with) {
    float maxx = 0;
    for (int i=0; i<w*h; i++) {
        maxx = qMax(glm::distance2(pixel_unsafe(i), compare_with.pixel_unsafe(i)), maxx);
    }
    return qSqrt(maxx);
}

template<>
float XRaster_<glm::vec4>::distance_C(XRaster_<glm::vec4> &compare_with) {
    float maxx = 0;
    for (int i=0; i<w*h; i++) {
        maxx = qMax(glm::distance2(pixel_unsafe(i), compare_with.pixel_unsafe(i)), maxx);
    }
    return qSqrt(maxx);
}

//-----------------------------------------------------------------------------------
