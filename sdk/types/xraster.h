#pragma once

//--------------------------------------------------
// XRaster
// Raster class definition
// Allows to work with rasters are with the following classes:
//     XRaster_u8    - grayscale 1-channel 8-bit image,
//     XRaster_u8c3  - color 3-channel 8-bit image,
//     XRaster_u16   - grayscale 1-channel 16-bit image,
//     XRaster_float - grayscale 1-channel 8-bit image,
//     XRaster_vec2  - 2-dimensional float vector (glm::vec2) image,
//     XRaster_vec3  - 3-dimensional float vector (glm::vec3) image,
//     XRaster_vec4  - 4-dimensional float vector (glm::vec4) image,
//     XRaster - class containing static functions convert, load, save for converting color
//               rasters to grayscale and back, to QImage and back, and also save and load rasters to disk.
// For operations on rasters see XRasterUtils
//--------------------------------------------------

#include "incl_h.h"

//--------------------------------------------------
/// XRaster - base raster class.
/// For particular rasters see XRaster_<T>.
//--------------------------------------------------
class XRaster {
public:
    XRaster() {}
    int w = 0;
    int h = 0;
    int bytes_per_pixel = 0;
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

    // Useful wrapper that checks if data is empty
    // Note: it's invalidates and updates after re-allocation, so you must care of it and not use old pointer.
    // XRaster_<T> has typed variant: typed_data_pointer()
    void* data_pointer();
    const void* data_pointer() const;
    int data_size() const;
    int bytes_per_line() const;

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
};

//--------------------------------------------------
// Template raster type XRaster_ of particular type
// it contains functions for convert, load, save, resize, blur
// used as a set of static functions over XRaster
//--------------------------------------------------
template<typename T>
class XRaster_ {
protected:
    static XTypeId type();

public:
    static void allocate(XRaster &raster, int w, int h, bool reallocate = false)
    {
        raster.allocate(w, h, type(), reallocate);
    }

    static T* typed_data_pointer(XRaster &raster) {
        raster.assert_type(type());
        return (T*)raster.data_pointer();
    }
    static const T* typed_data_pointer(const XRaster &raster) {
        raster.assert_type(type());
        return (T*)raster.data_pointer();
    }


    // pixel value - not checking boundaries
    // "unsafe" in name is a remainder that you must be sure that (x,y) is inside raster matrix
    static T &pixel_unsafe(XRaster &raster, int x, int y) {
        raster.assert_type(type());
        return data_pointer_(raster)[x + raster.w * y];
	}
    static T pixel_unsafe(const XRaster &raster, int x, int y) {
        return data_pointer_(raster)[x + raster.w * y];
	}
    static T &pixel_unsafe(XRaster &raster, const int2 &p) {
        return data_pointer_(raster)[p.x + raster.w * p.y];
	}
    static T pixel_unsafe(const XRaster &raster, const int2 &p) {
        return data_pointer_(raster)[p.x + raster.w * p.y];
    }
    static T &pixel_unsafe(XRaster &raster, int i) {
        return data_pointer_(raster)[i];
	}
    T pixel_unsafe(const XRaster &raster, int i) const {
        return data_pointer_(raster)[i];
	}

    //maximal difference between two rasters at some point - used for checking if they are equal or different
    static float distance_C(XRaster_<T> &compare_with);

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




    static void set(const T &v) {
        for (int i=0; i<w*h; i++) {
            data_pointer_[i] = v;
        }
    }

    template<typename T1>
    static void add(const XRaster_<T1> &r) {
        xc_assert(r.w == w && r.h == h, "XRaster add error, argument raster has different size");
        for (int i=0; i<w*h; i++) {
            data_pointer_[i] += r.pixel_unsafe(i);
        }
    }

    template<typename T1>
    static void mult_by(const XRaster_<T1> &r) {
        xc_assert(r.w == w && r.h == h, "XRaster mult_by error, argument raster has different size");
        for (int i=0; i<w*h; i++) {
            data_pointer_[i] *= r.pixel_unsafe(i);
        }
    }

    //mirror
    static void mirror(bool mirrorx, bool mirrory = false) {
        if (mirrorx) {
            int w2 = w/2;
            for (int y=0; y<h; y++) {
                for (int x=0; x<w2; x++) {
                    qSwap(pixel_unsafe(x,y), pixel_unsafe(w-1-x,y));
                }
            }
        }
        if (mirrory) {
            int h2 = h/2;
            for (int y=0; y<h2; y++) {
                for (int x=0; x<w; x++) {
                    qSwap(pixel_unsafe(x,y), pixel_unsafe(x,h-1-y));
                }
            }
        }
    }

    //rotate on 0, 90, 180, 270 angles
    //TODO only works with 1-channel images (?)
    // works only with internal images
    static void rotate(int angle) {
        xc_assert(is_owner, "XRaster::rotate() is implemented only for internal rasters");
        if (angle == 90) {
            int w0 = w;
            int h0 = h;
            XRaster_<T> temp = *this; // Copy. TODO can be made with swap more effectively...
            auto *temp_data = temp.data_pointer();
            this->allocate(h0,w0);
            for (int y=0; y<h0; y++) {
                for (int x=0; x<w0; x++) {
                    data_pointer_[(h0-1-y) + h0*x] = temp_data[x+w0*y];
                }
            }
        }
        if (angle == 180) {
            XRaster_<T> temp = *this; // Copy. TODO can be made with swap more effectively...
            auto *temp_data = temp.data_pointer();

            auto *data = data_pointer();

            for (int y=0; y<h; y++) {
                for (int x=0; x<w; x++) {
                    data[(w-1-x) + w*(h-1-y)] = temp_data[x+w*y];
                }
            }
        }
        if (angle == 270) {
            //rotate(90);
            //rotate(180);
            int w0 = w;
            int h0 = h;
            XRaster_<T> temp = *this; // Copy. TODO can be made with swap more effectively...
            auto *temp_data = temp.data_pointer();
            this->allocate(h0,w0);

            auto *data = data_pointer();

            for (int y=0; y<h0; y++) {
                for (int x=0; x<w0; x++) {
                    data[y + h0*(w0-1-x)] = temp_data[x+w0*y];
                }
            }
        }

    }

    //Crop
    static XRaster_<T> crop(int x0, int y0, int w0, int h0) const {
        xc_assert(x0 >= 0 && y0 >= 0 && w0 >= 0 && h0 >= 0 && x0+w0 <= w && y0+h0 <= h,
                  "XRaster_<T> crop - bad arguments");
        XRaster_<T> image;
        image.allocate(w0, h0);
        for (int y = 0; y < h0; y++) {
            for (int x = 0; x < w0; x++) {
                image.pixel_unsafe(x, y) = pixel_unsafe(x0+x, y0+y);
            }
        }
        return image;
    }


    //Crop to square
   static XRaster_<T> crop_to_square() const {
        int w0 = qMin(w,h);
        int h0 = w0;
        int x0 = (w-w0)/2;
        int y0 = (h-h0)/2;
        return crop(x0,y0,w0,h0);
    }

    //More raster functions - convert, load, save, resize, blur - see at XRaster:: below
};

//--------------------------------------------------
//Particular raster types
//--------------------------------------------------
typedef XRaster_<uint8> XRaster_u8;
typedef XRaster_<rgb_u8> XRaster_u8c3;    //color RGB image
typedef XRaster_<rgba_u8> XRaster_u8c4;    //color RGBA image
typedef XRaster_<int8> XRaster_s8;
typedef XRaster_<int16> XRaster_int16;
typedef XRaster_<uint16> XRaster_u16;
typedef XRaster_<uint32> XRaster_u32;
typedef XRaster_<int32> XRaster_int32;
typedef XRaster_<float> XRaster_float;
typedef XRaster_<double> XRaster_double;
typedef XRaster_<glm::vec2> XRaster_vec2;
typedef XRaster_<glm::vec3> XRaster_vec3;
typedef XRaster_<glm::vec4> XRaster_vec4;
typedef XRaster_<int2> XRaster_int2;

