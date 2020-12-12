#ifndef XTYPES_H
#define XTYPES_H

//Basic types used in arrays and rasters
#include <QString>

enum XTypeId : int {
    XTypeId_none = 0,
    XTypeId_u8 = 1,
    XTypeId_u8c3 = 2,
    XTypeId_s8 = 3,
    XTypeId_int16 = 4,
    XTypeId_u16 = 5,
    XTypeId_int32 = 6,
    XTypeId_u32 = 7,
    XTypeId_float = 8,
    XTypeId_double = 9,
    XTypeId_vec2 = 10,
    XTypeId_vec3 = 11,
    XTypeId_vec4 = 12,
    XTypeId_int2 = 13,
    XTypeId_N = 14
};

//size of one element
unsigned int XTypeIdSize(XTypeId type);
QString XTypeId_to_string(XTypeId type);
XTypeId string_to_XTypeId(QString type);
bool is_XTypeId_integer(XTypeId type);
bool is_XTypeId_float(XTypeId type);


#endif // XTYPES_H
