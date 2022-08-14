#ifndef XTYPES_H
#define XTYPES_H

//Basic types used in arrays and rasters
#include <QString>

enum class XTypeId : int {
    none = 0,
    u8 = 1,
    u8c3 = 2,
    u8c4 = 3,
    s8 = 4,
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
unsigned int XTypeIdSize(XTypeId type);
QString XTypeId_to_string(XTypeId type);
XTypeId string_to_XTypeId(QString type);
bool is_XTypeId_integer(XTypeId type);
bool is_XTypeId_float(XTypeId type);


#endif // XTYPES_H
