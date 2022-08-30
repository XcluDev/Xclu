#include "xtype.h"
#include "xerrorhandling.h"
#include "xtypes.h"

//---------------------------------------------------------------------
//size of one element
unsigned int XType_bytes(XType type) {
    switch (type) {
    case XType::none:
        return 0;
    case XType::uint8:
        return 1;
    case XType::rgb_u8:
        return 3;
    case XType::rgba_u8:
        return 4;
    case XType::int8:
        return 1;
    case XType::int16:
        return 2;
    case XType::uint16:
        return 2;
    case XType::int32:
        return 4;
    case XType::uint32:
        return 4;
    case XType::float32:
        return 4;
    case XType::float64:
        return 8;
    case XType::vec2:
        return sizeof(vec2);
    case XType::vec3:
        return sizeof(vec3);
    case XType::vec4:
        return sizeof(vec4);
    case XType::int2:
        return sizeof(int2);
    default:
        xc_exception(QString("XType_bytes - not applicable for XType %1 - %2")
                     .arg(int(type))
                     .arg(XType_to_string(type)));
        break;
    }
    return 0;
}

//---------------------------------------------------------------------
int XType_channels(XType type) {
    switch (type) {
    case XType::none:
        return 0;
    case XType::uint8:
        return 1;
    case XType::rgb_u8:
        return 3;
    case XType::rgba_u8:
        return 4;
    case XType::int8:
    case XType::int16:
    case XType::uint16:
    case XType::int32:
    case XType::uint32:
    case XType::float32:
    case XType::float64:
        return 8;
    case XType::vec2:
        return 2;
    case XType::vec3:
        return 3;
    case XType::vec4:
        return 4;
    case XType::int2:
        return 2;
    default:
        xc_exception(QString("XType_channels not applicable for XType %1 - %2")
                     .arg(int(type))
                     .arg(XType_to_string(type)));
        break;
    }
    return 0;
}

//---------------------------------------------------------------------
QString XType_to_string(XType type) {
    switch (type) {
#define  XTYPEDEF(name, id) case XType::name:     return #name;
XTYPESLIST
#undef  XTYPEDEF
    case XType::none:     return "none";
    case XType::Custom:   return "Custom";
    default:
        xc_exception(QString("XType_to_string - unknown XType %1")
                     .arg(int(type)));
        break;
    }
    return 0;
}

//---------------------------------------------------------------------
//TODO optimize using hashmap
XType string_to_XType(QString type) {
#define  XTYPEDEF(name, id) if (type == #name) return XType::name;
XTYPESLIST
#undef  XTYPEDEF
    if (type == "none") return XType::none;
    if (type == "u8") return XType::u8;
    if (type == "Custom") return XType::Custom;

    xc_exception(QString("Unknown XType '%1'").arg(type));
    return XType::none;
}

//---------------------------------------------------------------------
bool is_XType_integer(XType type) {
    switch (type) {
    case XType::none:
        return false;
    case XType::uint8:
        return true;
    case XType::rgb_u8:
        return false;
    case XType::rgba_u8:
        return false;
    case XType::int8:
        return true;
    case XType::int16:
        return true;
    case XType::uint16:
        return true;
    case XType::int32:
        return true;
    case XType::uint32:
        return true;
    case XType::float32:
        return false;
    case XType::float64:
    case XType::vec2:
    case XType::vec3:
    case XType::int2:
        return false;
    default:
        return false;
    }
}

//---------------------------------------------------------------------
bool is_XType_float(XType type) {
    return (type == XType::float32 || type == XType::float64);
}

//---------------------------------------------------------------------
#define  XTYPEDEF(name, id) template<> XType cpptype_to_XType<name>() { return XType::name; }
XTYPESLIST
#undef  XTYPEDEF


//---------------------------------------------------------------------
