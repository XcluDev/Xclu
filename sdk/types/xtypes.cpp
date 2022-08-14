#include "xtypes.h"

#include "incl_cpp.h"

//---------------------------------------------------------------------
//size of one element
unsigned int XTypeIdSize(XTypeId type) {
    switch (type) {
    case XTypeId::none:
        return 0;
    case XTypeId::u8:
        return 1;
    case XTypeId::u8c3:
        return 3;
    case XTypeId::u8c4:
        return 4;
    case XTypeId::s8:
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
        return sizeof(glm::vec2);
    case XTypeId::vec3:
        return sizeof(glm::vec3);
    case XTypeId::vec4:
        return sizeof(glm::vec4);
    case XTypeId::int2:
        return sizeof(int2);
    default:
        xc_exception(QString("Unknown XTypeId %1").arg(int(type)));
        break;
    }
    return 0;
}

//---------------------------------------------------------------------
QString XTypeId_to_string(XTypeId type) {
    switch (type) {
    case XTypeId::none:
        return "";
    case XTypeId::u8:
        return "u8";
    case XTypeId::u8c3:
        return "u8c3";
    case XTypeId::u8c4:
        return "u8c4";
    case XTypeId::s8:
        return "s8";
    case XTypeId::int16:
        return "int16";
    case XTypeId::uint16:
        return "uint16";
    case XTypeId::int32:
        return "int32";
    case XTypeId::uint32:
        return "uint32";
    case XTypeId::float32:
        return "float";
    case XTypeId::float64:
        return "double";
    case XTypeId::vec2:
        return "vec2";
    case XTypeId::vec3:
        return "vec3";
    case XTypeId::vec4:
        return "vec4";
    case XTypeId::int2:
        return "int2";
    default:
        xc_exception(QString("Unknown XTypeId %1").arg(int(type)));
        break;
    }
    return 0;
}

//---------------------------------------------------------------------
//TODO optimize using hashmap
XTypeId string_to_XTypeId(QString type) {
    if (type == "none") return XTypeId::none;
    if (type == "u8") return XTypeId::u8;
    if (type == "u8c3") return XTypeId::u8c3;
    if (type == "u8c4") return XTypeId::u8c4;
    if (type == "s8") return XTypeId::s8;
    if (type == "int16") return XTypeId::int16;
    if (type == "uint16") return XTypeId::uint16;
    if (type == "int32") return XTypeId::int32;
    if (type == "uint32") return XTypeId::uint32;
    if (type == "float") return XTypeId::float32;
    if (type == "double") return XTypeId::float64;
    if (type == "vec2") return XTypeId::vec2;
    if (type == "vec3") return XTypeId::vec3;
    if (type == "vec4") return XTypeId::vec4;
    if (type == "int2") return XTypeId::int2;
    xc_exception(QString("Unknown XTypeId '%1'").arg(type));
    return XTypeId::none;
}

//---------------------------------------------------------------------
bool is_XTypeId_integer(XTypeId type) {
    switch (type) {
    case XTypeId::none:
        return false;
    case XTypeId::u8:
        return true;
    case XTypeId::u8c3:
        return false;
    case XTypeId::u8c4:
        return false;
    case XTypeId::s8:
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
        xc_exception(QString("Unknown XTypeId %1").arg(type));
        break;
    }
    return 0;
}

//---------------------------------------------------------------------
bool is_XTypeId_float(XTypeId type) {
    return (type == XTypeId::float32 || type == XTypeId::float64);
}

//---------------------------------------------------------------------
