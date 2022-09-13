#pragma once

//--------------------------------------------------
// XRaster
// Raster class definition
// For operations on rasters see XRasterUtils
// TODO There are huge code duplication with XArray, but nuances in "item" and "pixel"
// still stops me from ihheriting XRaster from XArray.
//--------------------------------------------------

#include <QVector>
#include "xtype.h"
#include "xtypeconvertor.h"
#include "int2.h"

/// XRaster - raster class.
class XRaster {
public:
    XRaster() {}
    int n = 0;
    int w = 0;
    int h = 0;
    int sizeofpixel = 0;
    XType type = XType::none; // To change this value you must call call set_type()
protected:
    bool is_owner = false;   // Does raster hold its own memory, or use external source
    quint8 *data_pointer_ = nullptr;
    QVector<quint8> internal_data_;        // Internal storage

    // Внимание: При добавлении членов - корректировать operator=

public:
    XRaster(const XRaster& other);
    XRaster& operator=(const XRaster& other);

    void set_type(XType type); // Must be called instead of directly changing type
    void assert_type(XType type) const;

    static void test();     // Тестирование

    bool is_empty() const;

    // Checks only internal images
    bool is_valid() const;

    void* data_pointer();
    const void* data_pointer() const;
    int data_size_in_bytes() const;
    int bytes_per_line() const;

    template<class T> T* data();
    template<class T> const T* data() const;    

    // Типизированный доступ к пикселям
    // - Для безопасности - стараться проверять assert_type().
    template<class T> T& pixel_unsafe(int x, int y);
    template<class T> const T& pixel_unsafe(int x, int y) const;
    template<class T> T& pixel_unsafe(const int2 &p);
    template<class T> const T& pixel_unsafe(const int2 &p) const;
    template<class T> T& pixel_unsafe(int i);
    template<class T> const T& pixel_unsafe(int i) const;

    template<class T> void set_pixel_unsafe(int x, int y, const T &value); // Note: value size must be sizeofpixel
    template<class T> void set_pixel_unsafe(const int2 &p, const T &value); // Note: value size must be sizeofpixel
    template<class T> void set_pixel_unsafe(int i, const T &value); // Note: value size must be sizeofpixel

    // Нетипизированный доступ к пикселям, используется для универсальных операций
    void* pixel_unsafe_ptr(int x, int y);
    void* pixel_unsafe_ptr(const int2 &p);
    void* pixel_unsafe_ptr(int i);
    const void* pixel_unsafe_ptr(int x, int y) const;
    const void* pixel_unsafe_ptr(const int2 &p) const;
    const void* pixel_unsafe_ptr(int i) const;

    void set_pixel_unsafe_ptr(int x, int y, const void *value); // Note: value size must be sizeofpixel
    void set_pixel_unsafe_ptr(const int2 &p, const void *value); // Note: value size must be sizeofpixel
    void set_pixel_unsafe_ptr(int i, const void *value); // Note: value size must be sizeofpixel

    /// Заполнить растр значениями
    template<class T> void set(const T &value);

    //----------------------------------------------------------------------------
    // Allocating - allocate own memory for raster
    //----------------------------------------------------------------------------

    // If 'reallocate is true - then old vector will be cleared.
    // It's useful for clearing memory when image size if significantly reduced, but works slower.
    void allocate(int w, int h, XType type, bool reallocate = false);
    template<class T> void allocate(int w, int h, bool reallocate = false);

    void clear();

    //----------------------------------------------------------------------------
    // Copying
    //----------------------------------------------------------------------------
    void copy_from(void* data, int w, int h, XType type);
    template<class T> void copy_from(T* data, int w, int h);

    //----------------------------------------------------------------------------
    // Linking - using external source of pixels, not copying it.
    // Use this mode carefully and control the source data exists while this XRaster is used!
    //----------------------------------------------------------------------------
    void link_data(void* data, int w, int h, XType type);
    template<class T> void link_data(T* data, int w, int h);

    // Operations
    void add_inplace(const XRaster &r);
    void mult_inplace(const XRaster &r);

    //mirror
    void mirror_inplace(bool mirrorx, bool mirrory = false);

    //rotate on 0, 90, 180, 270 angles
    //TODO only works with 1-channel images (?)
    // works only with internal images
    void rotate_inplace(int angle);
    //Crop
    XRaster crop(int x0, int y0, int w0, int h0) const;

    //Crop to square
   XRaster crop_to_square() const;

   //maximal difference between two rasters at some point - used for checking if they are equal or different
   float distance_C(const XRaster &compare_with) const;

   // float pixel_bilinear(float x, float y);

};

//----------------------------------------------------------------------------
template<class T> T* XRaster::data() {
    if (is_empty()) return nullptr;
    assert_type(cpptype_to_XType<T>());
    return (T*)data_pointer_;
}
template<class T> const T* XRaster::data() const {
    if (is_empty()) return nullptr;
    assert_type(cpptype_to_XType<T>());
    return (T*)data_pointer_;
}

//----------------------------------------------------------------------------
template<class T> T& XRaster::pixel_unsafe(int x, int y) {
    return *(T*)&data_pointer_[sizeofpixel*(x+y*w)];
}
template<class T> const T& XRaster::pixel_unsafe(int x, int y) const {
    return *(const T*)&data_pointer_[sizeofpixel*(x+y*w)];
}
template<class T> T& XRaster::pixel_unsafe(const int2 &p) {
    return *(T*)&data_pointer_[sizeofpixel*(p.x+p.y*w)];
}
template<class T> const T& XRaster::pixel_unsafe(const int2 &p) const {
    return *(const T*)&data_pointer_[sizeofpixel*(p.x+p.y*w)];
}
template<class T> T& XRaster::pixel_unsafe(int i) {
    return *(T*)&data_pointer_[sizeofpixel*(i)];
}
template<class T> const T& XRaster::pixel_unsafe(int i) const {
    return *(const T*)&data_pointer_[sizeofpixel*(i)];
}

template<class T> void XRaster::set_pixel_unsafe(int x, int y, const T &value) { // Note: value size must be sizeofpixel
    memcpy(pixel_unsafe<void*>(x,y), &value, sizeofpixel);
}
template<class T> void XRaster::set_pixel_unsafe(const int2 &p, const T &value) { // Note: value size must be sizeofpixel
    memcpy(pixel_unsafe<void*>(p), &value, sizeofpixel);
}
template<class T> void XRaster::set_pixel_unsafe(int i, const T &value) { // Note: value size must be sizeofpixel
    memcpy(pixel_unsafe<void*>(i), &value, sizeofpixel);
}

template<class T> void XRaster::set(const T &value) {
    assert_type(cpptype_to_XType());
    for (int i=0; i<n; i++) {
        set_pixel_unsafe<T>(i, value);
    }
}

//----------------------------------------------------------------------------




