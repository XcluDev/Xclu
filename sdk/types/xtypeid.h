#ifndef XTYPEID_H
#define XTYPEID_H

#include <QString>

//------------------------------------------------
// Перечисление типов для XTypeId
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
                           \
    XTYPEDEF(QString, 15)\
    XTYPEDEF(QStringList, 16)\
                            \
    XTYPEDEF(XArray, 17)\
    XTYPEDEF(XRaster, 18)\
                              \
    XTYPEDEF(XSoundFormat, 19)\
    XTYPEDEF(XSoundBuffer, 20)\
                                   \
    XTYPEDEF(XCallCreateWidget, 21)\
    XTYPEDEF(XCallSoundBufferAdd, 22)\
    XTYPEDEF(XCallSoundBufferReceived, 23)
// При изменении списка, следует обновить значение Custom ниже
//------------------------------------------------

// Объявление класса XTypeId
enum class XTypeId : int {
#define  XTYPEDEF(name, id) name = id,
XTYPESLIST
#undef  XTYPEDEF
    none = 0,
    u8 = uint8,       // Используем и uint8 и u8, где как удобнее
    Custom = 24,      // Это значение должно быть максимальному значению в списке XTYPESLIST плюс 1
    N = Custom + 1
};

// Размеры типов - применимо только к базовым
unsigned int XTypeId_bytes(XTypeId type);
int XTypeId_channels(XTypeId type);
QString XTypeId_to_string(XTypeId type);
XTypeId string_to_XTypeId(QString type);
bool is_XTypeId_integer(XTypeId type);
bool is_XTypeId_float(XTypeId type);


// Macros for enrolling code for all basic types
#define code_for_all_basic_XTypeId(type_id, CODE) \
switch(type_id) {\
case XTypeId::uint8:    { typedef uint8 T; CODE } break;\
case XTypeId::rgb_u8:   { typedef rgb_u8 T; CODE } break;\
case XTypeId::rgba_u8:  { typedef rgba_u8 T; CODE } break;\
case XTypeId::int8:     { typedef int8 T; CODE } break;\
case XTypeId::int16:    { typedef int16 T; CODE } break;\
case XTypeId::uint16:   { typedef uint16 T; CODE } break;\
case XTypeId::int32:    { typedef int32 T; CODE } break;\
case XTypeId::uint32:   { typedef uint32 T; CODE } break;\
case XTypeId::float32:  { typedef float32 T; CODE } break;\
case XTypeId::float64:  { typedef float64 T; CODE } break;\
case XTypeId::vec2:     { typedef vec2 T; CODE } break;\
case XTypeId::vec3:     { typedef vec3 T; CODE } break;\
case XTypeId::vec4:     { typedef vec4 T; CODE } break;\
case XTypeId::int2:     { typedef int2 T; CODE } break;\
default: \
    xc_exception(QString("code_for_all_basic_XTypeId - bad type_id %1 for code %2").arg(XTypeId_to_string(type_id)).arg(#CODE)); \
}

/// Template function converting C++ type to XTypeId
/// Примеры применения:
/// template<class T> void XRaster::copy_from(T* input_img, int w, int h) {
///     copy_from(input_img, w, h, cpptype_to_XTypeId<T>());
/// }
/// template<class T> ... { assert_type(cpptype_to_XTypeId()); ...}
template<class T> XTypeId cpptype_to_XTypeId();


#endif // XTYPEID_H
