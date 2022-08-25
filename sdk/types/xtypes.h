#ifndef XTYPES_H
#define XTYPES_H

//Basic types used in arrays and rasters
#include <QString>


// Geometry
#include "xmath_glm.h"

// int-vectors
#include "int2.h"

typedef unsigned char uint8;
typedef char int8;
typedef short int16;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef int int32;

const int max_u16 = 65535;
const int u16_n = 65536;
typedef unsigned long long int uint64;

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

//convert int <-> float points
vec2 to_vec2(const int2 &p);
int2 to_int2_truncate(const vec2 &p);

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


enum class XTypeId : int {
    none = 0,
    uint8 = 1,
    rgb_u8 = 2,
    rgba_u8 = 3,
    int8 = 4,
    int16 = 5,
    uint16 = 6,
    int32 = 7,
    uint32 = 8,
    float32 = 9,
    float64 = 10,
    vec2 = 11,
    vec3 = 12,
    vec4 = 13,
    int2 = 14,
    N = 15
};

//size of one element
unsigned int XTypeId_bytes(XTypeId type);
int XTypeId_channels(XTypeId type);
QString XTypeId_to_string(XTypeId type);
XTypeId string_to_XTypeId(QString type);
bool is_XTypeId_integer(XTypeId type);
bool is_XTypeId_float(XTypeId type);


// Macroses for manupulating types

// Convert void* to type value, for example, XVAL(float, data) is *(float*(data))
#define XVAL(newtype, voidptr_data) (*(newtype *)(voidptr_data))


// Produce code for each XTypeId variant with locally defined T
#define FOR_ALL_XTypeId(type_id, CODE) \
switch(type_id) {\
case XTypeId::uint8:    { typedef uint8 T; CODE } break;\
case XTypeId::rgb_u8:   { typedef rgb_u8 T; CODE } break;\
case XTypeId::rgba_u8:  { typedef rgba_u8 T; CODE } break;\
case XTypeId::int8:     { typedef int8 T; CODE } break;\
case XTypeId::int16:    { typedef int16 T; CODE } break;\
case XTypeId::uint16:   { typedef uint16 T; CODE } break;\
case XTypeId::int32:    { typedef int32 T; CODE } break;\
case XTypeId::uint32:   { typedef uint32 T; CODE } break;\
case XTypeId::float32:  { typedef float T; CODE } break;\
case XTypeId::float64:  { typedef double T; CODE } break;\
case XTypeId::vec2:     { typedef vec2 T; CODE } break;\
case XTypeId::vec3:     { typedef vec3 T; CODE } break;\
case XTypeId::vec4:     { typedef vec4 T; CODE } break;\
case XTypeId::int2:     { typedef int2 T; CODE } break;\
default: \
    xc_exception("FOR_ALL_XTypeId - bad type_id for code " + #CODE); \
}


#endif // XTYPES_H
