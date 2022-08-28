#ifndef XTYPEID_H
#define XTYPEID_H

#include <QString>
#include "xbasictypes.h"

enum class XTypeId : int {
    none = 0,
    uint8 = 1, u8 = 1,  // используем и uint8 и u8, где как удобнее
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


// Macroses for manipulating types
#define code_for_all_XTypeId(type_id, CODE) \
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
    xc_exception(QString("code_for_all_XTypeId - bad type_id %1 for code %2").arg(XTypeId_to_string(type_id)).arg(#CODE)); \
}

/// Template function converting C++ type to XTypeId
/// Примеры применения:
/// template<class T> void XRaster::copy_from(T* input_img, int w, int h) {
///     copy_from(input_img, w, h, type_to_XTypeId<T>());
/// }
/// template<class T> ... { assert_type(type_to_XTypeId()); ...}
template<class T> XTypeId type_to_XTypeId();


#endif // XTYPEID_H
