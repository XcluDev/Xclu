#pragma once

//Raster class definition

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
class Raster_ {
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
            Raster_<T> temp = *this; //TODO can be made with swap more effectively...
            this->allocate(h0,w0);
            for (int y=0; y<h0; y++) {
                for (int x=0; x<w0; x++) {
                    data[(h0-1-y) + h0*x] = temp.data[x+w0*y];
                }
            }
        }
        if (angle == 180) {
            Raster_<T> temp = *this; //TODO can be made with swap more effectively...
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
            Raster_<T> temp = *this; //TODO can be made with swap more effectively...
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
typedef Raster_<uint8> Raster_u8;
typedef Raster_<u8_rgb> Raster_u8c3;    //color image
typedef Raster_<uint16> Raster_u16;
typedef Raster_<float> Raster_float;
typedef Raster_<glm::vec2> Raster_vec2;
typedef Raster_<glm::vec3> Raster_vec3;


//Конвертирование растров между собой и QImage, запись и считывание на диск
//TODO при работе с диском используется QImage - быстрее было бы использовать OpenCV или FreeImage или TurboJpeg
void raster_to_raster(Raster_u8c3 &raster_rgb, Raster_u8 &raster);
void raster_to_raster(Raster_u8 &raster, Raster_u8c3 &raster_rgb);

void raster_from_QImage(QImage qimage, Raster_u8 &raster);
void raster_from_QImage(QImage qimage, Raster_u8c3 &raster);
void raster_to_QImage(Raster_u8 &raster, QImage &qimage);
void raster_to_QImage(Raster_u8c3 &raster, QImage &qimage);

void raster_load(QString file_name, Raster_u8 &raster);
void raster_load(QString file_name, Raster_u8c3 &raster);
void raster_save(Raster_u8 &raster, QString file_name, QString format, int quality = 90);
void raster_save(Raster_u8c3 &raster, QString file_name, QString format, int quality = 90);
