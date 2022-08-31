#pragma once

// Скаляры и RGB

typedef unsigned char uint8;
typedef unsigned char u8;           // uint8 и u8 идентичны

typedef char int8;
typedef short int16;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef int int32;
typedef unsigned long long int uint64;
const int max_u16 = 65535;
const int u16_n = 65536;

typedef float float32;
typedef double float64;

typedef void* pointer_type;

// Геометрия
#include "xmath_glm.h"

// int2
#include "int2.h"

//convert int <-> vec2
vec2 to_vec2(const int2 &p);
int2 to_int2_truncate(const vec2 &p);

//rectangle
struct rect_int {
    int x = 0;
    int y = 0;
    int w = 0;
    int h = 0;
    rect_int() {}
    rect_int(int x0, int y0, int w0, int h0) : x(x0),y(y0),w(w0),h(h0) {}
    rect_int(int2 pos, int2 size) : x(pos.x), y(pos.y), w(size.x), h(size.y) {}
    bool is_inside(int w0, int h0) {
        return (x >= 0 && y >= 0 && w >= 0 && h >= 0 && x + w <= w0 && y + h <= h0);
    }
    void crop(int w0, int h0);
};

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
    T grayi() const { return (int(v[0])+int(v[1])+int(v[2]))/3; }
    float grayf() const { return (float(v[0])+float(v[1])+float(v[2]))/3; }
    static T grayi(T r, T g, T b) {
        return (int(r)+int(g)+int(b))/3;
    }
    static float grayf(T r, T g, T b) {
        return (float(r)+float(g)+float(b))/3;
    }

    // TODO implement saturation for uint8, int8, uint16, int16, uint32, int32
    rgb_<T> operator+(const rgb_<T>& vec) const;
    rgb_<T>& operator+=(const rgb_<T>& vec);
    rgb_<T> operator-(const rgb_<T>& vec) const;
    rgb_<T>& operator-=(const rgb_<T>& vec);
    rgb_<T> operator*(const rgb_<T>& vec) const;
    rgb_<T>& operator*=(const rgb_<T>& vec);
};

template<typename T>
struct rgba_ {
    T v[4] = {0,0,0,0};
    rgba_() {}
    rgba_(T val, T a) {
        v[0] = v[1] = v[2] = val; v[3] = a;
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
    // TODO implement saturation for uint8, int8, uint16, int16, uint32, int32
    rgba_<T> operator+(const rgba_<T>& vec) const;
    rgba_<T>& operator+=(const rgba_<T>& vec);
    rgba_<T> operator-(const rgba_<T>& vec) const;
    rgba_<T>& operator-=(const rgba_<T>& vec);
    rgba_<T> operator*(const rgba_<T>& vec) const;
    rgba_<T>& operator*=(const rgba_<T>& vec);
};

typedef rgb_<uint8> rgb_u8;
typedef rgb_<float> rgb_float;
typedef rgba_<uint8> rgba_u8;
typedef rgba_<float> rgba_float;


