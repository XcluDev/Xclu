#pragma once

//Raster class definition
//Allows to work with rasters are with the following classes:
//    XRaster_u8    - grayscale 1-channel 8-bit image,
//    XRaster_u8c3  - color 3-channel 8-bit image,
//    XRaster_u16   - grayscale 1-channel 16-bit image,
//    XRaster_float - grayscale 1-channel 8-bit image,
//    XRaster_vec2  - 2-dimensional float vector (glm::vec2) image,
//    XRaster_vec3  - 3-dimensional float vector (glm::vec3) image,
//    XRaster - class containing static functions convert, load, save for converting color
//              rasters to grayscale and back, to QImage and back, and also save and load rasters to disk.

#include "incl_h.h"
#include <QImage>

//--------------------------------------------------
//Color pixel type
//--------------------------------------------------
struct u8_rgb {
  uint8 v[3];
  u8_rgb() { v[0] = v[1] = v[2] = 0; }
  u8_rgb(uint8 val) {
      v[0] = v[1] = v[2] = val;
  }
  u8_rgb(uint8 r, uint8 g, uint8 b) {
      v[0] = r; v[1] = g; v[2] = b;
  }
  void set(uint8 r, uint8 g, uint8 b) {
      v[0] = r; v[1] = g; v[2] = b;
  }
  void set(uint8 val) {
      v[0] = v[1] = v[2] = val;
  }
  uint8 gray() { return (int(v[0])+int(v[1])+int(v[2]))/3; }
  static uint8 gray(uint8 r, uint8 g, uint8 b) {
      return (int(r)+int(g)+int(b))/3;
  }
};

//--------------------------------------------------
//Template raster type
//--------------------------------------------------
template<typename T>
class XRaster_ {
public:
	int w = 0;
	int h = 0;
    QVector<T> data;

	//useful wrapper that checks if data is empty
	T* data_pointer() {
		if (is_empty()) return 0;
		else return &data[0];
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
		this->w = w;
		this->h = h;
		data.resize(w*h);
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
		return data.empty();
	}
    /*bool is_zero() const {
		for (int i = 0; i < w*h; i++) {
			if (data[i] != 0) return false;
		}
		return true;
    }*/


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
};

//--------------------------------------------------
//Particular raster types
//--------------------------------------------------
typedef XRaster_<uint8> XRaster_u8;
typedef XRaster_<u8_rgb> XRaster_u8c3;    //color image
typedef XRaster_<uint16> XRaster_u16;
typedef XRaster_<float> XRaster_float;
typedef XRaster_<glm::vec2> XRaster_vec2;
typedef XRaster_<glm::vec3> XRaster_vec3;

//class for static-defined operations:
//converting color raster to grayscale abd back,
//to QImage and back,
//load and save raster to disk

class XRaster {
public:
    //TODO currently for disk operations QImage is used - but faster to use OpenCV, FreeImage or TurboJpeg
    static void convert(XRaster_u8c3 &raster_rgb, XRaster_u8 &raster);
    static void convert(XRaster_u8 &raster, XRaster_u8c3 &raster_rgb);

    static void convert(QImage qimage, XRaster_u8 &raster);
    static void convert(QImage qimage, XRaster_u8c3 &raster);
    static void convert(XRaster_u8 &raster, QImage &qimage);
    static void convert(XRaster_u8c3 &raster, QImage &qimage);

    static void load(QString file_name, XRaster_u8 &raster);
    static void load(QString file_name, XRaster_u8c3 &raster);
    static void save(XRaster_u8 &raster, QString file_name, QString format, int quality = 90);
    static void save(XRaster_u8c3 &raster, QString file_name, QString format, int quality = 90);

};
