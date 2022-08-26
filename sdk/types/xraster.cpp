#include "./../utility/console.h"
#include "xraster.h"
#include "incl_cpp.h"
#include <QImage>
#include <QImageReader>
#include <QImageWriter>
#include <QPainter>

//---------------------------------------------------------------------
void XRaster::set_type(XTypeId type_id) {
    this->type_id = type_id;
    sizeofpixel = XTypeId_bytes(type_id);
}

void XRaster::assert_type(XTypeId type) const {
    xc_assert(type_id == type, QString("XRaster::assert_type error, expected {0} but has {1}")
              .arg(XTypeId_to_string(type))
              .arg(XTypeId_to_string(type_id)));
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

int XRaster::data_size() const {
    return sizeofpixel*n;
}

int XRaster::bytes_per_line() const {
    return sizeofpixel*w;
}

//----------------------------------------------------------------------------
// Pixel access
void* XRaster::pixel_unsafe(int x, int y) {
    return (void*)&data_pointer_[sizeofpixel*(x+y*w)];
}

const void* XRaster::pixel_unsafe(int x, int y) const {
    return (const void*)&data_pointer_[sizeofpixel*(x+y*w)];
}

void* XRaster::pixel_unsafe(const int2 &p) {
    return (void*)&data_pointer_[sizeofpixel*(p.x+p.y*w)];
}

const void* XRaster::pixel_unsafe(const int2 &p) const {
    return (const void*)&data_pointer_[sizeofpixel*(p.x+p.y*w)];
}

void XRaster::pixel_unsafe(int x, int y, void* &value) {
    value = &data_pointer_[sizeofpixel*(x+y*w)];
}

void XRaster::pixel_unsafe(const int2 &p, void* &value) {
    value = &data_pointer_[sizeofpixel*(p.x+p.y*w)];
}

void XRaster::set_pixel_unsafe(int x, int y, const void *value) { // Note: value size must be sizeofpixel
    memcpy(pixel_unsafe(x,y), value, sizeofpixel);
}

void XRaster::set_pixel_unsafe(int i, const void *value) { // Note: value size must be sizeofpixel
    memcpy(pixel_unsafe(i), value, sizeofpixel);
}

//----------------------------------------------------------------------------
// Allocating - allocate own memory for raster
//----------------------------------------------------------------------------

// If 'reallocate is true - then old vector will be cleared.
// It's useful for clearing memory when image size if significantly reduced, but works slower.
void XRaster::allocate(int w, int h, XTypeId Type_id, bool reallocate) {
    if (!reallocate && is_owner && this->w == w && this->h == h && this->type_id == Type_id) {
        return;
    }
    if (reallocate) {
        clear();
    }
    set_type(Type_id);
    n = w*h;
    this->w = w;
    this->h = h;
    internal_data_.resize(n);
    data_pointer_ = internal_data_.data();
    is_owner = true;
}

//---------------------------------------------------------------------
void XRaster::copy_from(void* input_img, int w, int h, XTypeId Type_id) {
    allocate(w, h, Type_id);
    memcpy(data_pointer_, input_img, data_size());
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
    return internal_data_.size() == data_size();
}

//---------------------------------------------------------------------
void XRaster::link_data(int w, int h, void* data, XTypeId type) {
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

//---------------------------------------------------------------------
//maximal difference between two rasters at some point - used for checking if they are equal or different
float XRaster::distance_C(const XRaster &compare_with) const {
    xc_assert(type_id == compare_with.type_id, "XRaster::distance_C - different types");
    float maxx = 0;
    switch (type_id) {
    case XTypeId::vec2:
        for (int i=0; i<n; i++) {
            maxx = qMax(glm::distance2(XVAL(vec2,pixel_unsafe(i)), XVAL(vec2,compare_with.pixel_unsafe(i))), maxx);
        }
        break;
    case XTypeId::vec3:
        for (int i=0; i<n; i++) {
            maxx = qMax(glm::distance2(XVAL(vec3,pixel_unsafe(i)), XVAL(vec3,compare_with.pixel_unsafe(i))), maxx);
        }
        break;
    case XTypeId::vec4:
        for (int i=0; i<n; i++) {
            maxx = qMax(glm::distance2(XVAL(vec4,pixel_unsafe(i)), XVAL(vec4,compare_with.pixel_unsafe(i))), maxx);
        }
        break;
   default:
        xc_exception("XRaster::distance_C not implemented for this type of rasters");
    }

    return qSqrt(maxx);
}

//---------------------------------------------------------------------
void XRaster::set(const void* v) {
    for (int i=0; i<n; i++) {
        set_pixel_unsafe(i, v);
    }
}

//---------------------------------------------------------------------
void XRaster::add_inplace(const XRaster &r) {
    xc_assert(r.w == w && r.h == h, "XRaster add error, argument raster has different size");
    code_for_all_XTypeId(type_id, \
    for (int i=0; i<n; i++) { \
        XVAL(T,pixel_unsafe(i)) += XVAL(const T,r.pixel_unsafe(i)); \
    });
                             //TODO implement rgb+= and rgba+=, *=, +, *
}

//---------------------------------------------------------------------
void XRaster::mult_inplace(const XRaster &r) {
    xc_assert(r.w == w && r.h == h, "XRaster mult_by error, argument raster has different size");
    code_for_all_XTypeId(type_id, \
    for (int i=0; i<n; i++) { \
        XVAL(T,pixel_unsafe(i)) *= XVAL(const T,r.pixel_unsafe(i)); \
    });
}

//---------------------------------------------------------------------
//mirror
void XRaster::mirror_inplace(bool mirrorx, bool mirrory) {
    code_for_all_XTypeId(type_id, \
    if (mirrorx) { \
        int w2 = w/2; \
        for (int y=0; y<h; y++) { \
            for (int x=0; x<w2; x++) { \
                qSwap(XVAL(T,pixel_unsafe(x,y)), XVAL(T,pixel_unsafe(w-1-x,y))); \
            } \
        } \
    } \
    if (mirrory) { \
        int h2 = h/2; \
        for (int y=0; y<h2; y++) { \
            for (int x=0; x<w; x++) { \
                qSwap(XVAL(T,pixel_unsafe(x,y)), XVAL(T,pixel_unsafe(x,h-1-y))); \
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
        this->allocate(h0, w0, type_id);
        for (int y=0; y<h0; y++) {
            for (int x=0; x<w0; x++) {
                set_pixel_unsafe(h0-1-y, x, temp.pixel_unsafe(x,y));
            }
        }
    }
    if (angle == 180) {
        XRaster temp = *this; // Copy. TODO can be made with swap more effectively...
        for (int y=0; y<h; y++) {
            for (int x=0; x<w; x++) {
                set_pixel_unsafe(w-1-x, h-1-y, temp.pixel_unsafe(x,y));
            }
        }
    }
    if (angle == 270) {
        //rotate(90);
        //rotate(180);
        int w0 = w;
        int h0 = h;
        XRaster temp = *this; // Copy. TODO can be made with swap more effectively...
        this->allocate(h0, w0, type_id);
        for (int y=0; y<h0; y++) {
            for (int x=0; x<w0; x++) {
                set_pixel_unsafe(y, w0-1-x, temp.pixel_unsafe(x,y));
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
    image.allocate(w0, h0, type_id);
    for (int y = 0; y < h0; y++) {
        for (int x = 0; x < w0; x++) {            
            image.set_pixel_unsafe(x, y, pixel_unsafe(x0+x, y0+y));
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
