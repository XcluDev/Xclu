#pragma once
#include <QString>


//------------------------------------------------
// Перечисление типов для XType
//------------------------------------------------
#define XTYPESLIST \
    XTYPEDEF(uint8, 1) \
    XTYPEDEF(rgb_u8, 2)\
    XTYPEDEF(rgba_u8, 3)\
    XTYPEDEF(int8, 4)\
    XTYPEDEF(int16, 5)\
    XTYPEDEF(uint16, 6)\
    XTYPEDEF(int32, 7)\
    XTYPEDEF(uint32, 8)\
    XTYPEDEF(float32, 9)\
    XTYPEDEF(float64, 10)\
    XTYPEDEF(vec2, 11)\
    XTYPEDEF(vec3, 12)\
    XTYPEDEF(vec4, 13)\
    XTYPEDEF(int2, 14)\
    XTYPEDEF(pointer_type, 15)\
                           \
    XTYPEDEF(QString, 16)\
    XTYPEDEF(QStringList, 17)\
                            \
    XTYPEDEF(XArray, 18)\
    XTYPEDEF(XRaster, 19)\
                              \
    XTYPEDEF(XSoundFormat, 20)\
    XTYPEDEF(XSoundBuffer, 21) \
    XTYPEDEF(XCallDataCreateWidget, 22)

// При изменении списка, следует обновить значение Custom ниже
//------------------------------------------------

// Объявление класса XType
enum class XType : int {
#define  XTYPEDEF(name, id) name = id,
XTYPESLIST
#undef  XTYPEDEF
    none = 0,
    u8 = uint8,       // Используем и uint8 и u8, где как удобнее
    Custom = 23,      // Это значение должно быть максимальному значению в списке XTYPESLIST плюс 1
    N = Custom + 1
};

// Размеры типов - применимо только к базовым
unsigned int XType_bytes(XType type);
int XType_channels(XType type);
QString XType_to_string(XType type);
XType string_to_XType(QString type);
bool is_XType_integer(XType type);
bool is_XType_float(XType type);


// Macros for enrolling code for all basic types
#define code_for_all_basic_XType(type, CODE) \
switch(type) {\
case XType::uint8:    { typedef uint8 T; CODE } break;\
case XType::rgb_u8:   { typedef rgb_u8 T; CODE } break;\
case XType::rgba_u8:  { typedef rgba_u8 T; CODE } break;\
case XType::int8:     { typedef int8 T; CODE } break;\
case XType::int16:    { typedef int16 T; CODE } break;\
case XType::uint16:   { typedef uint16 T; CODE } break;\
case XType::int32:    { typedef int32 T; CODE } break;\
case XType::uint32:   { typedef uint32 T; CODE } break;\
case XType::float32:  { typedef float32 T; CODE } break;\
case XType::float64:  { typedef float64 T; CODE } break;\
case XType::vec2:     { typedef vec2 T; CODE } break;\
case XType::vec3:     { typedef vec3 T; CODE } break;\
case XType::vec4:     { typedef vec4 T; CODE } break;\
case XType::int2:     { typedef int2 T; CODE } break;\
default: \
    xc_exception(QString("code_for_all_basic_XType - bad type %1 for code %2").arg(XType_to_string(type)).arg(#CODE)); \
}


