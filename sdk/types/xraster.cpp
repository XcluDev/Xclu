#include "./../utility/console.h"
#include "xraster.h"
#include "incl_cpp.h"
#include <QImage>
#include <QImageReader>
#include <QImageWriter>
#include <QPainter>

//---------------------------------------------------------------------
/*XRaster_u8;
 XRaster_u8c3;
XRaster_s8;
XRaster_int16;
 XRaster_u16;
 XRaster_u32;
XRaster_int32;
XRaster_float;
 XRaster_double;
XRaster_vec2;
XRaster_vec3;
XRaster_int2;
*/

//---------------------------------------------------------------------
#define MACRO_XRaster_internal_initialize(TYPE_RASTER, TYPE_ID) \
template<> void TYPE_RASTER::internal_type_initialize() { \
    set_type(TYPE_ID); \
}

MACRO_XRaster_internal_initialize(XRaster_u8, XTypeId::u8)
MACRO_XRaster_internal_initialize(XRaster_u8c3, XTypeId::u8c3)
MACRO_XRaster_internal_initialize(XRaster_s8, XTypeId::s8)
MACRO_XRaster_internal_initialize(XRaster_int16, XTypeId::int16)
MACRO_XRaster_internal_initialize(XRaster_u16, XTypeId::uint16)
MACRO_XRaster_internal_initialize(XRaster_int32, XTypeId::int32)
MACRO_XRaster_internal_initialize(XRaster_u32, XTypeId::uint32)
MACRO_XRaster_internal_initialize(XRaster_float, XTypeId::float32)
MACRO_XRaster_internal_initialize(XRaster_double, XTypeId::float64)
MACRO_XRaster_internal_initialize(XRaster_vec2, XTypeId::vec2)
MACRO_XRaster_internal_initialize(XRaster_vec3, XTypeId::vec3)
MACRO_XRaster_internal_initialize(XRaster_vec4, XTypeId::vec4)
MACRO_XRaster_internal_initialize(XRaster_int2, XTypeId::int2)

//---------------------------------------------------------------------
void XRaster::set_type(XTypeId type_id)
{
    this->type_id = type_id;
    bytes_per_pixel = XTypeId_bytes(type_id);
}

//---------------------------------------------------------------------
//maximal difference between two rasters at some point - used for checking if they are equal or different
template<>
float XRaster_<glm::vec2>::distance_C(XRaster_<glm::vec2> &compare_with) {
    float maxx = 0;
    for (int i=0; i<w*h; i++) {
        maxx = qMax(glm::distance2(pixel_unsafe(i), compare_with.pixel_unsafe(i)), maxx);
    }
    return qSqrt(maxx);
}

template<>
float XRaster_<glm::vec3>::distance_C(XRaster_<glm::vec3> &compare_with) {
    float maxx = 0;
    for (int i=0; i<w*h; i++) {
        maxx = qMax(glm::distance2(pixel_unsafe(i), compare_with.pixel_unsafe(i)), maxx);
    }
    return qSqrt(maxx);
}

template<>
float XRaster_<glm::vec4>::distance_C(XRaster_<glm::vec4> &compare_with) {
    float maxx = 0;
    for (int i=0; i<w*h; i++) {
        maxx = qMax(glm::distance2(pixel_unsafe(i), compare_with.pixel_unsafe(i)), maxx);
    }
    return qSqrt(maxx);
}

//-----------------------------------------------------------------------------------
