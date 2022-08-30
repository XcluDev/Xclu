#include "xtypeid.h"
#include "xerrorhandling.h"
#include "xtypes.h"

//---------------------------------------------------------------------
//size of one element
unsigned int XTypeId_bytes(XTypeId type) {
    switch (type) {
    case XTypeId::none:
        return 0;
    case XTypeId::uint8:
        return 1;
    case XTypeId::rgb_u8:
        return 3;
    case XTypeId::rgba_u8:
        return 4;
    case XTypeId::int8:
        return 1;
    case XTypeId::int16:
        return 2;
    case XTypeId::uint16:
        return 2;
    case XTypeId::int32:
        return 4;
    case XTypeId::uint32:
        return 4;
    case XTypeId::float32:
        return 4;
    case XTypeId::float64:
        return 8;
    case XTypeId::vec2:
        return sizeof(vec2);
    case XTypeId::vec3:
        return sizeof(vec3);
    case XTypeId::vec4:
        return sizeof(vec4);
    case XTypeId::int2:
        return sizeof(int2);
    default:
        xc_exception(QString("XTypeId_bytes - not applicable for XTypeId %1 - %2")
                     .arg(int(type))
                     .arg(XTypeId_to_string(type)));
        break;
    }
    return 0;
}

//---------------------------------------------------------------------
int XTypeId_channels(XTypeId type) {
    switch (type) {
    case XTypeId::none:
        return 0;
    case XTypeId::uint8:
        return 1;
    case XTypeId::rgb_u8:
        return 3;
    case XTypeId::rgba_u8:
        return 4;
    case XTypeId::int8:
    case XTypeId::int16:
    case XTypeId::uint16:
    case XTypeId::int32:
    case XTypeId::uint32:
    case XTypeId::float32:
    case XTypeId::float64:
        return 8;
    case XTypeId::vec2:
        return 2;
    case XTypeId::vec3:
        return 3;
    case XTypeId::vec4:
        return 4;
    case XTypeId::int2:
        return 2;
    default:
        xc_exception(QString("XTypeId_channels not applicable for XTypeId %1 - %2")
                     .arg(int(type))
                     .arg(XTypeId_to_string(type)));
        break;
    }
    return 0;
}

//---------------------------------------------------------------------
QString XTypeId_to_string(XTypeId type) {
    switch (type) {
#define  XTYPEDEF(name, id) case XTypeId::name:     return #name;
XTYPESLIST
#undef  XTYPEDEF
    case XTypeId::none:     return "none";
    case XTypeId::Custom:   return "Custom";
    default:
        xc_exception(QString("XTypeId_to_string - unknown XTypeId %1")
                     .arg(int(type)));
        break;
    }
    return 0;
}

//---------------------------------------------------------------------
//TODO optimize using hashmap
XTypeId string_to_XTypeId(QString type) {
#define  XTYPEDEF(name, id) if (type == #name) return XTypeId::name;
XTYPESLIST
#undef  XTYPEDEF
    if (type == "none") return XTypeId::none;
    if (type == "u8") return XTypeId::u8;
    if (type == "Custom") return XTypeId::Custom;

    xc_exception(QString("Unknown XTypeId '%1'").arg(type));
    return XTypeId::none;
}

//---------------------------------------------------------------------
bool is_XTypeId_integer(XTypeId type) {
    switch (type) {
    case XTypeId::none:
        return false;
    case XTypeId::uint8:
        return true;
    case XTypeId::rgb_u8:
        return false;
    case XTypeId::rgba_u8:
        return false;
    case XTypeId::int8:
        return true;
    case XTypeId::int16:
        return true;
    case XTypeId::uint16:
        return true;
    case XTypeId::int32:
        return true;
    case XTypeId::uint32:
        return true;
    case XTypeId::float32:
        return false;
    case XTypeId::float64:
    case XTypeId::vec2:
    case XTypeId::vec3:
    case XTypeId::int2:
        return false;
    default:
        return false;
    }
}

//---------------------------------------------------------------------
bool is_XTypeId_float(XTypeId type) {
    return (type == XTypeId::float32 || type == XTypeId::float64);
}

//---------------------------------------------------------------------
#define  XTYPEDEF(name, id) template<> XTypeId cpptype_to_XTypeId<name>() { return XTypeId::name; }
XTYPESLIST
#undef  XTYPEDEF


//---------------------------------------------------------------------
