#pragma once

//Raster class definition

#include "incl_h.h"

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

};

//--------------------------------------------------
//Particular raster types
//--------------------------------------------------
typedef Raster_<uint8> Raster_u8;
typedef Raster_<u8_rgb> Raster_u8c3;    //color image
typedef Raster_<uint16> Raster_u16;
typedef Raster_<float> Raster_float;



