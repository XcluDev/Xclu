#pragma once

//--------------------------------------------------
// XRaster
// Raster class definition
// For operations on rasters see XRasterUtils
// TODO There are huge code duplication with XArray, but nuances in "item" and "pixel"
// still stops me from ihheriting XRaster from XArray.
//--------------------------------------------------

#include <QVector>
#include "xtypeid.h"
#include "int2.h"

/// XRaster - raster class.
class XRaster {
public:
    XRaster() {}
    int n = 0;
    int w = 0;
    int h = 0;
    int sizeofpixel = 0;
    XTypeId type_id = XTypeId::none; // To change this value you must call call set_type()

    void set_type(XTypeId type_id); // Must be called instead of directly changing type_id
    void assert_type(XTypeId type) const;
protected:
    bool is_owner = false;   // Does raster hold its own memory, or use external source
    quint8 *data_pointer_ = nullptr;
    QVector<quint8> internal_data_;        // Internal storage

public:
    bool is_empty() const;

    // Checks only internal images
    bool is_valid() const;

    void* data_pointer();
    const void* data_pointer() const;
    int data_size() const;
    int bytes_per_line() const;


    // Pixel access
    void* pixel_unsafe(int x, int y);
    const void* pixel_unsafe(int x, int y) const;
    void* pixel_unsafe(const int2 &p);
    const void* pixel_unsafe(const int2 &p) const;
    void pixel_unsafe(int x, int y, void* &value);
    void pixel_unsafe(const int2 &p, void* &value);

    void set_pixel_unsafe(int x, int y, const void *value); // Note: value size must be sizeofpixel
    void set_pixel_unsafe(int i, const void *value); // Note: value size must be sizeofpixel

    //----------------------------------------------------------------------------
    // Allocating - allocate own memory for raster
    //----------------------------------------------------------------------------

    // If 'reallocate is true - then old vector will be cleared.
    // It's useful for clearing memory when image size if significantly reduced, but works slower.
    void allocate(int w, int h, XTypeId Type_id, bool reallocate = false);

    void copy_from(void* input_img, int w, int h, XTypeId Type_id);

    void clear();

    //----------------------------------------------------------------------------
    // Linking - using external source of pixels, not copying it.
    // Use this mode carefully and control the source data exists while this XRaster is used!
    //----------------------------------------------------------------------------
    void link_data(int w, int h, void* data, XTypeId type);


    // Operations
    void set(const void* value);

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






