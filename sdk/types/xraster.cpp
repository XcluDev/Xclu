#include "xraster.h"
#include "./../utility/xerrorhandling.h"
#include "incl_cpp.h"

//---------------------------------------------------------------------
void XRaster::set_type(XType type) {
    this->type = type;
    sizeofpixel = XType_bytes(type);
}

void XRaster::assert_type(XType type) const {
    xc_assert(this->type == type, QString("XRaster::assert_type error, expected %1 but has %2")
              .arg(XType_to_string(type))
              .arg(XType_to_string(this->type)));
}

// Useful wrapper that checks if data is empty
// Note: it's invalidates and updates after re-allocation, so you must care of it and not use old pointer.
// XRaster has typed variant: typed_data_pointer()
void* XRaster::data_pointer() {
    if (is_empty()) return nullptr;
    return data_pointer_;
}
const void* XRaster::data_pointer() const {
    if (is_empty()) return nullptr;
    return data_pointer_;
}

//----------------------------------------------------------------------------
int XRaster::data_size_in_bytes() const {
    return sizeofpixel*n;
}

int XRaster::bytes_per_line() const {
    return sizeofpixel*w;
}

//---------------------------------------------------------------------
void* XRaster::pixel_unsafe_ptr(int x, int y) {
    return &data_pointer_[sizeofpixel*(x+y*w)];
}
void* XRaster::pixel_unsafe_ptr(const int2 &p) {
    return &data_pointer_[sizeofpixel*(p.x+p.y*w)];
}
void* XRaster::pixel_unsafe_ptr(int i) {
    return &data_pointer_[sizeofpixel*(i)];
}
const void* XRaster::pixel_unsafe_ptr(int x, int y) const {
    return &data_pointer_[sizeofpixel*(x+y*w)];
}
const void* XRaster::pixel_unsafe_ptr(const int2 &p) const {
    return &data_pointer_[sizeofpixel*(p.x+p.y*w)];
}
const void* XRaster::pixel_unsafe_ptr(int i) const {
    return &data_pointer_[sizeofpixel*(i)];
}

//----------------------------------------------------------------------------
void XRaster::set_pixel_unsafe_ptr(int x, int y, const void *value) { // Note: value size must be sizeofpixel
    memcpy(pixel_unsafe_ptr(x,y), value, sizeofpixel);
}
void XRaster::set_pixel_unsafe_ptr(const int2 &p, const void *value) { // Note: value size must be sizeofpixel
    memcpy(pixel_unsafe_ptr(p), value, sizeofpixel);
}
void XRaster::set_pixel_unsafe_ptr(int i, const void *value) { // Note: value size must be sizeofpixel
    memcpy(pixel_unsafe_ptr(i), value, sizeofpixel);
}

//----------------------------------------------------------------------------
// Allocating - allocate own memory for raster
//----------------------------------------------------------------------------

// If 'reallocate is true - then old vector will be cleared.
// It's useful for clearing memory when image size if significantly reduced, but works slower.
void XRaster::allocate(int w, int h, XType type, bool reallocate) {
    if (!reallocate && is_owner && this->w == w && this->h == h && this->type == type) {
        return;
    }
    if (reallocate) {
        clear();
    }
    set_type(type);
    n = w*h;
    this->w = w;
    this->h = h;
    internal_data_.resize(n*sizeofpixel);
    data_pointer_ = internal_data_.data();
    is_owner = true;
}

//---------------------------------------------------------------------
template<class T> void XRaster::allocate(int w, int h, bool reallocate) {
    allocate(w, h, cpptype_to_XType(type), reallocate);
}

//---------------------------------------------------------------------
void XRaster::copy_from(void* data, int w, int h, XType type) {
    allocate(w, h, type);
    memcpy(data_pointer_, data, data_size_in_bytes());
}

template<class T> void XRaster::copy_from(T* data, int w, int h) {
    copy_from(data, w, h, cpptype_to_XType<T>());
}

//----------------------------------------------------------------------------
XRaster::XRaster(const XRaster& other) {
    *this = other;
}

//----------------------------------------------------------------------------
XRaster& XRaster::operator=(const XRaster& other)
{
    // Guard self assignment
    if (this == &other)
        return *this;

    n = other.n;
    w = other.w;
    h = other.h;
    sizeofpixel = other.sizeofpixel;
    type = other.type;
    is_owner = other.is_owner;
    internal_data_ = other.internal_data_;

    // Основная цель определения оператора копирования - правильно поставить data_pointer_
    data_pointer_ = (is_owner) ? internal_data_.data() : other.data_pointer_;

    return *this;
}

//---------------------------------------------------------------------
void XRaster::clear() {
    n = w = h = sizeofpixel = 0;
    data_pointer_ = nullptr;

    if (is_owner) {
        //clear data (note: data.clear() does not!)
        //https://stackoverflow.com/questions/13944886/is-stdvector-memory-freed-upon-a-clear
        QVector<quint8>().swap(internal_data_);
    }
}

//---------------------------------------------------------------------
bool XRaster::is_empty() const {
    return data_pointer_ == nullptr || n <= 0 || w <= 0 || h <= 0 || sizeofpixel <= 0;
}

//---------------------------------------------------------------------
bool XRaster::is_valid() const {
    if (is_empty()) return false;
    if (!is_owner) return true;
    return internal_data_.size() == data_size_in_bytes();
}

//---------------------------------------------------------------------
void XRaster::link_data(void* data, int w, int h, XType type) {
    xc_assert(w > 0 && h > 0, "Error XRaster::link() - bad dimensions");
    xc_assert(data, "Error XRaster::link() - data is nullptr");
    clear();
    is_owner = false;
    this->n = w * h;
    this->w = w;
    this->h = h;
    set_type(type);
    data_pointer_ = (quint8*) data;
}

template<class T> void XRaster::link_data(T* data, int w, int h) {
    link_data(data, w, h, cpptype_to_XType<T>());
}

//---------------------------------------------------------------------
//maximal difference between two rasters at some point - used for checking if they are equal or different
float XRaster::distance_C(const XRaster &compare_with) const {
    xc_assert(type == compare_with.type, "XRaster::distance_C - different types");
    float maxx = 0;
    switch (type) {
    case XType::vec2:
        for (int i=0; i<n; i++) {
            maxx = qMax(glm::distance2(pixel_unsafe<vec2>(i),compare_with.pixel_unsafe<vec2>(i)), maxx);
        }
        break;
    case XType::vec3:
        for (int i=0; i<n; i++) {
            maxx = qMax(glm::distance2(pixel_unsafe<vec3>(i), compare_with.pixel_unsafe<vec3>(i)), maxx);
        }
        break;
    case XType::vec4:
        for (int i=0; i<n; i++) {
            maxx = qMax(glm::distance2(pixel_unsafe<vec4>(i), compare_with.pixel_unsafe<vec4>(i)), maxx);
        }
        break;
   default:
        xc_exception("XRaster::distance_C not implemented for this type of rasters");
    }

    return qSqrt(maxx);
}

//---------------------------------------------------------------------
void XRaster::add_inplace(const XRaster &r) {
    xc_assert(r.w == w && r.h == h, "XRaster add error, argument raster has different size");
    code_for_all_basic_XType(type, \
    for (int i=0; i<n; i++) { \
        pixel_unsafe<T>(i) +=r.pixel_unsafe<const T>(i); \
    });
}

//---------------------------------------------------------------------
void XRaster::mult_inplace(const XRaster &r) {
    xc_assert(r.w == w && r.h == h, "XRaster mult_by error, argument raster has different size");
    code_for_all_basic_XType(type, \
    for (int i=0; i<n; i++) { \
        pixel_unsafe<T>(i) *= r.pixel_unsafe<const T>(i); \
    });
}

//---------------------------------------------------------------------
// mirror
// TODO Реализовать без qSwap, а используя размер пикселя
void XRaster::mirror_inplace(bool mirrorx, bool mirrory) {
    code_for_all_basic_XType(type, \
    if (mirrorx) { \
        int w2 = w/2; \
        for (int y=0; y<h; y++) { \
            for (int x=0; x<w2; x++) { \
                qSwap(pixel_unsafe<T>(x,y), pixel_unsafe<T>(w-1-x,y)); \
            } \
        } \
    } \
    if (mirrory) { \
        int h2 = h/2; \
        for (int y=0; y<h2; y++) { \
            for (int x=0; x<w; x++) { \
                qSwap(pixel_unsafe<T>(x,y), pixel_unsafe<T>(x,h-1-y)); \
            } \
        } \
    });
}

//---------------------------------------------------------------------
//rotate on 0, 90, 180, 270 angles
//TODO only works with 1-channel images (?)
// works only with internal images
void XRaster::rotate_inplace(int angle) {
    xc_assert(is_owner, "XRaster::rotate() is implemented only for internal rasters");
    if (angle == 90) {
        int w0 = w;
        int h0 = h;
        XRaster temp = *this; // Copy. TODO can be made with swap more effectively...
        this->allocate(h0, w0, type);
        for (int y=0; y<h0; y++) {
            for (int x=0; x<w0; x++) {
                set_pixel_unsafe_ptr(h0-1-y, x, temp.pixel_unsafe_ptr(x,y));
            }
        }
    }
    if (angle == 180) {
        XRaster temp = *this; // Copy. TODO can be made with swap more effectively...
        for (int y=0; y<h; y++) {
            for (int x=0; x<w; x++) {
                set_pixel_unsafe_ptr(w-1-x, h-1-y, temp.pixel_unsafe_ptr(x,y));
            }
        }
    }
    if (angle == 270) {
        //rotate(90);
        //rotate(180);
        int w0 = w;
        int h0 = h;
        XRaster temp = *this; // Copy. TODO can be made with swap more effectively...
        this->allocate(h0, w0, type);
        for (int y=0; y<h0; y++) {
            for (int x=0; x<w0; x++) {
                set_pixel_unsafe_ptr(y, w0-1-x, temp.pixel_unsafe_ptr(x,y));
            }
        }
    }

}

//---------------------------------------------------------------------
//Crop
XRaster XRaster::crop(int x0, int y0, int w0, int h0) const {
    xc_assert(x0 >= 0 && y0 >= 0 && w0 >= 0 && h0 >= 0 && x0+w0 <= w && y0+h0 <= h,
              "XRaster crop - bad arguments");
    XRaster image;
    image.allocate(w0, h0, type);
    for (int y = 0; y < h0; y++) {
        for (int x = 0; x < w0; x++) {            
            image.set_pixel_unsafe_ptr(x, y, pixel_unsafe_ptr(x0+x, y0+y));
        }
    }
    return image;
}


//---------------------------------------------------------------------
//Crop to square
XRaster XRaster::crop_to_square() const {
    int w0 = qMin(w,h);
    int h0 = w0;
    int x0 = (w-w0)/2;
    int y0 = (h-h0)/2;
    return crop(x0,y0,w0,h0);
}


//---------------------------------------------------------------------
/*float pixel_bilinear(float x, float y) {
   alg_assert(x >= 0 && y >= 0 && x <= w - 1 && y <= h - 1, "pixel_bilinear error - bad coords", Alg_Error_Algorithm);
   int xi = int(x);
   int yi = int(y);
   float tx = x - xi;
   float ty = y - yi;
   int xi1 = min(xi + 1, w - 1);
   int yi1 = min(yi + 1, h - 1);
   return pixel_unsafe(xi, yi) * (1 - tx) * (1 - ty)
       + pixel_unsafe(xi1, yi) * (tx) * (1 - ty)
       + pixel_unsafe(xi1, yi1) * (tx) * (ty)
       + pixel_unsafe(xi, yi1) * (1 - tx) * (ty);
}*/

//-----------------------------------------------------------------------------------
void XRaster::test() {     // Тестирование
    qDebug() << "Raster test";
    // тест растров
    XRaster raster;
    raster.allocate(100,100,XType::rgb_u8);
    XRaster crop = raster.crop(20,20,40,40);
}

//-----------------------------------------------------------------------------------
