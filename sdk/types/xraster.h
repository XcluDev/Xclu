#pragma once

//Raster class definition
//Allows to work with rasters are with the following classes:
//    XRaster_u8    - grayscale 1-channel 8-bit image,
//    XRaster_u8c3  - color 3-channel 8-bit image,
//    XRaster_u16   - grayscale 1-channel 16-bit image,
//    XRaster_float - grayscale 1-channel 8-bit image,
//    XRaster_vec2  - 2-dimensional float vector (glm::vec2) image,
//    XRaster_vec3  - 3-dimensional float vector (glm::vec3) image,
//    XRaster_vec4  - 4-dimensional float vector (glm::vec4) image,
//    XRaster - class containing static functions convert, load, save for converting color
//              rasters to grayscale and back, to QImage and back, and also save and load rasters to disk.

#include "incl_h.h"

#include <QImage>
//class QPainter;
#include <QPainter>
#include "ximageeffect.h"

//--------------------------------------------------
//Color pixel type
//--------------------------------------------------
template<typename T>
struct rgb_ {
    T v[3] = {0,0,0};
    rgb_() {}
    rgb_(T val) {
        v[0] = v[1] = v[2] = val;
    }
    rgb_(T r, T g, T b) {
        v[0] = r; v[1] = g; v[2] = b;
    }
    void set(T r, T g, T b) {
        v[0] = r; v[1] = g; v[2] = b;
    }
    void set(T val) {
        v[0] = v[1] = v[2] = val;
    }
    T grayi() { return (int(v[0])+int(v[1])+int(v[2]))/3; }
    float grayf() { return (float(v[0])+float(v[1])+float(v[2]))/3; }
    static T grayi(T r, T g, T b) {
        return (int(r)+int(g)+int(b))/3;
    }
    static float grayf(T r, T g, T b) {
        return (float(r)+float(g)+float(b))/3;
    }
};

template<typename T>
struct rgba_ {
    T v[4] = {0,0,0,0};
    rgba_() {}
    rgba_(T val, T a) {
        v[0] = v[1] = v[2] = val;
        v[3] = a;
    }
    rgba_(T r, T g, T b, T a) {
        v[0] = r; v[1] = g; v[2] = b; v[3] = a;
    }
    void set(T r, T g, T b, T a) {
        v[0] = r; v[1] = g; v[2] = b; v[3] = a;
    }
    void set(T val, T a) {
        v[0] = v[1] = v[2] = v[3] = val; v[4] = a;
    }
};

typedef rgb_<uint8> rgb_u8;
typedef rgb_<float> rgb_float;
typedef rgba_<uint8> rgba_u8;
//typedef rgba_<uint8> bgra_u8;   //just for convenience of speedup QImage conversion
typedef rgba_<float> rgba_float;


//--------------------------------------------------
//Template raster type XRaster_
//It contains very little operations,
//for more functions see at XRaster:: below
//- it contains functions for convert, load, save, resize, blur
//--------------------------------------------------
template<typename T>
class XRaster_ {
public:
	int w = 0;
	int h = 0;

    QVector<T> data;

    XTypeId type_id();

    uint8 *data_pointer_u8() {
        return (uint8 *) data_pointer();
    }

	//useful wrapper that checks if data is empty
	T* data_pointer() {
		if (is_empty()) return 0;
		else return &data[0];
	}

    int bytesPerLine() {
        return sizeof(T)*w;
    }

	//pixel value - not checking boundaries
	//"unsafe" in name is a remainder that you must be sure that (x,y) is inside raster matrix
	T &pixel_unsafe(int x, int y) {
		return data[x + w * y];
	}
	T pixel_unsafe(int x, int y) const {
		return data[x + w * y];
	}
	T &pixel_unsafe(const int2 &p) {
		return data[p.x + w * p.y];
	}
	T pixel_unsafe(const int2 &p) const {
		return data[p.x + w * p.y];
	}	
	T &pixel_unsafe(int i) {
		return data[i];
	}
	T pixel_unsafe(int i) const {
		return data[i];
	}

    //maximal difference between two rasters at some point - used for checking if they are equal or different
    float distance_C(XRaster_<T> &compare_with);

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

	void allocate(int w, int h) {
        if (this->w != w || this->h != h) {
            this->w = w;
            this->h = h;
            data.resize(w*h);
        }
	}
	void copy_from(T *input_img, int w, int h) {
		allocate(w, h);
		for (int i = 0; i < w*h; i++) {
			data[i] = input_img[i];		//TODO can use memcpy
		}
	}

	void clear() {		
		w = h = 0;
		//clear data (note: data.clear() does not!) 
		//https://stackoverflow.com/questions/13944886/is-stdvector-memory-freed-upon-a-clear
        QVector<T>().swap(data);
	}
    bool is_empty() const {
        return data.empty() || w <= 0 || h <= 0;
    }
    bool is_valid() const {
        return !is_empty() && data.size() == w * h;
    }
    /*bool is_zero() const {
        for (int i = 0; i < w*h; i++) {
            if (data[i] != 0) return false;
        }
        return true;
    }*/

    void set(const T &v) {
        for (int i=0; i<w*h; i++) {
            data[i] = v;
        }
    }

    template<typename T1>
    void add(const XRaster_<T1> &r) {
        xc_assert(r.w == w && r.h == h, "XRaster add error, argument raster has different size");
        for (int i=0; i<w*h; i++) {
            data[i] += r.pixel_unsafe(i);
        }
    }

    template<typename T1>
    void mult_by(const XRaster_<T1> &r) {
        xc_assert(r.w == w && r.h == h, "XRaster mult_by error, argument raster has different size");
        for (int i=0; i<w*h; i++) {
            data[i] *= r.pixel_unsafe(i);
        }
    }

    //mirror
    void mirror(bool mirrorx, bool mirrory = false) {
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
    void rotate(int angle) {
        if (angle == 90) {
            int w0 = w;
            int h0 = h;
            XRaster_<T> temp = *this; //TODO can be made with swap more effectively...
            this->allocate(h0,w0);
            for (int y=0; y<h0; y++) {
                for (int x=0; x<w0; x++) {
                    data[(h0-1-y) + h0*x] = temp.data[x+w0*y];
                }
            }
        }
        if (angle == 180) {
            XRaster_<T> temp = *this; //TODO can be made with swap more effectively...
            for (int y=0; y<h; y++) {
                for (int x=0; x<w; x++) {
                    data[(w-1-x) + w*(h-1-y)] = temp.data[x+w*y];
                }
            }
        }
        if (angle == 270) {
            //rotate(90);
            //rotate(180);
            int w0 = w;
            int h0 = h;
            XRaster_<T> temp = *this; //TODO can be made with swap more effectively...
            this->allocate(h0,w0);
            for (int y=0; y<h0; y++) {
                for (int x=0; x<w0; x++) {
                    data[y + h0*(w0-1-x)] = temp.data[x+w0*y];
                }
            }
        }

    }

    //Crop
    XRaster_<T> crop(int x0, int y0, int w0, int h0) const {
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
    XRaster_<T> crop_to_square() const {
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
typedef XRaster_<rgb_float> XRaster_float3; //see XRaster_vec3 below!
typedef XRaster_<double> XRaster_double;
typedef XRaster_<glm::vec2> XRaster_vec2;
typedef XRaster_<glm::vec3> XRaster_vec3;
typedef XRaster_<glm::vec4> XRaster_vec4;
typedef XRaster_<int2> XRaster_int2;


//class for static-defined operations:
//converting color raster to grayscale abd back,
//to QImage and back,
//load and save raster to disk

class XRaster {
public:
    //Convert - copies data
    static void convert(XRaster_u8c3 &raster_rgb, XRaster_u8 &raster);
    static void convert(XRaster_u8 &raster, XRaster_u8c3 &raster_rgb);

    static void convert(QImage qimage, XRaster_u8 &raster);
    static void convert(QImage qimage, XRaster_u8c3 &raster);
    static void convert_rgba(QImage qimage, XRaster_u8c4 &raster);
    static void convert_bgra(QImage qimage, XRaster_u8c4 &raster);  //Fast, expected QImage img(w,h,QImage::Format_ARGB32);
    static void convert(XRaster_u8 &raster, QImage &qimage);
    static void convert(XRaster_u8c3 &raster, QImage &qimage);

    //Resize
    template<typename T>
    static void resize_nearest(XRaster_<T> &input, XRaster_<T> &output, int new_w, int new_h) {
        int w = input.w;
        int h = input.h;
        xc_assert(input.data_pointer() != output.data_pointer(), "resize_nearest, input and output must be different images");
        xc_assert(w > 0 && h > 0, "resize_nearest error, input image must have positive size");
        xc_assert(new_w > 0 && new_h > 0, "resize_nearest error, resized image must have positive size");
        output.allocate(new_w, new_h);
        for (int y=0; y<new_h; y++) {
            for (int x=0; x<new_w; x++) {
                output.pixel_unsafe(x, y) = input.pixel_unsafe(x * w / new_w, y * h / new_h);
            }
        }
    }

    template<typename T>
    static void resize_nearest(XRaster_<T> &input, XRaster_<T> &output, float scale) {
        int new_w = int(input.w * scale);
        int new_h = int(input.h * scale);
        resize_nearest(input, output, new_w, new_h);
    }

    //Link - create image without copying pixels raster
    //Much faster than `convert`, but requires care
    static QImage link(XRaster_u8 &raster);
    static QImage link(XRaster_u8c3 &raster);

    //Draw raster on painter
    template<typename T>
    static void draw(QPainter *painter, XRaster_<T> &raster, int x, int y, int sx = 0, int sy = 0, int sw = -1, int sh = -1) {
        painter->drawImage(x, y, link(raster), sx, sy, sw, sh);
    }

    //draw to a given rectangle
    template<typename T>
    static void draw(QPainter *painter, XRaster_<T> &raster, const QRectF &r) {
        painter->drawImage(r, link(raster));
    }
    template<typename T>
    static void draw(QPainter *painter, XRaster_<T> &raster, const QRectF &targetRect, const QRectF &sourceRect) {
        painter->drawImage(targetRect, link(raster), sourceRect);
    }
    template<typename T>
    static void draw(QPainter *painter, XRaster_<T> &raster, const QRect &targetRect, const QRect &sourceRect) {
        painter->drawImage(targetRect, link(raster), sourceRect);
    }
    template<typename T>
    static void draw(QPainter *painter, XRaster_<T> &raster, const QPointF &p, const QRectF &sr) {
        painter->drawImage(p, link(raster), sr);
    }
    template<typename T>
    static void draw(QPainter *painter, XRaster_<T> &raster, const QPoint &p, const QRect &sr) {
        painter->drawImage(p, link(raster), sr);
    }
    template<typename T>
    static void draw(QPainter *painter, XRaster_<T> &raster, const QRect &r) {
        painter->drawImage(r, link(raster));
    }
    template<typename T>
    static void draw(QPainter *painter, XRaster_<T> &raster, const QPointF &p) {
        painter->drawImage(p, link(raster));
    }
    template<typename T>
    static void draw(QPainter *painter, XRaster_<T> &raster, const QPoint &p) {
        painter->drawImage(p, link(raster));
    }

    //save and load
    //TODO currently for disk operations QImage is used - but faster to use OpenCV, FreeImage or TurboJpeg
    static void load(QString file_name, XRaster_u8 &raster);
    static void load(QString file_name, XRaster_u8c3 &raster);
    static void save(XRaster_u8 &raster, QString file_name, QString format, int quality = 90);
    static void save(XRaster_u8c3 &raster, QString file_name, QString format, int quality = 90);

    //blur
    //Works in-place!
    //Note: not very optimal implementation, but made on pure Qt. For better performance, use OpenCV.
    template<typename T>
    static void blur(XRaster_<T> &raster, XRaster_<T> &result, float blur_radius) {
        xc_assert(!raster.is_empty(), "XRaster::blur - input raster is empty");
        xc_assert(blur_radius>=0, "XRaster::blur - blur radius must be non-negative");
        QImage img;
        convert(raster, img);
        img = XImageEffect::blur(img, blur_radius);
        convert(img, result);
    }
};
