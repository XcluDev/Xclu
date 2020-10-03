#include "xtypes.h"

#include "incl_cpp.h"

//---------------------------------------------------------------------
//size of one element
unsigned int XTypeIdSize(XTypeId type) {
    switch (type) {
    case XTypeId_none:
        return 0;
    case XTypeId_u8:
        return 1;
    XTypeId_u8c3:
        return 3;
    case XTypeId_s8:
        return 1;
    case XTypeId_int16:
        return 2;
    case XTypeId_u16:
        return 2;
    case XTypeId_int32:
        return 4;
    case XTypeId_u32:
        return 4;
    case XTypeId_float:
        return 4;
    case XTypeId_double:
        return 8;
    case XTypeId_vec2:
        return sizeof(glm::vec2);
    case XTypeId_vec3:
        return sizeof(glm::vec3);
    case XTypeId_int2:
        return sizeof(glm::int2);
    default:
        xclu_exception(QString("Unknown XTypeId %1").arg(type));
        break;
    }
    return 0;
}

//---------------------------------------------------------------------
QString XTypeId_to_string(XTypeId type) {
    switch (type) {
    case XTypeId_none:
        return "";
    case XTypeId_u8:
        return "u8";
    case XTypeId_u8c3:
        return "u8c3";
    case XTypeId_s8:
        return "s8";
    case XTypeId_int16:
        return "int16";
    case XTypeId_u16:
        return "uint16";
    case XTypeId_int32:
        return "int32";
    case XTypeId_u32:
        return "uint32";
    case XTypeId_float:
        return "float";
    case XTypeId_double:
        return "double";
    case XTypeId_vec2:
        return "vec2";
    case XTypeId_vec3:
        return "vec3";
    case XTypeId_int2:
        return "int2";
    default:
        xclu_exception(QString("Unknown XTypeId %1").arg(type));
        break;
    }
    return 0;
}

//---------------------------------------------------------------------
//TODO optimize using hashmap
XTypeId string_to_XTypeId(QString type) {
    if (type == "none") return XTypeId_none;
    if (type == "u8") return XTypeId_u8;
    if (type == "u8c3") return XTypeId_u8c3;
    if (type == "s8") return XTypeId_s8;
    if (type == "int16") return XTypeId_int16;
    if (type == "uint16") return XTypeId_u16;
    if (type == "int32") return XTypeId_int32;
    if (type == "uint32") return XTypeId_u32;
    if (type == "float") return XTypeId_float;
    if (type == "double") return XTypeId_double;
    if (type == "vec2") return XTypeId_vec2;
    if (type == "vec3") return XTypeId_vec3;
    if (type == "int2") return XTypeId_int2;
    xclu_exception(QString("Unknown XTypeId '%1'").arg(type));
    return XTypeId_none;
}

//---------------------------------------------------------------------
bool is_XTypeId_integer(XTypeId type) {
    switch (type) {
    case XTypeId_none:
        return false;
    case XTypeId_u8:
        return true;
    case XTypeId_u8c3:
        return false;
    case XTypeId_s8:
        return true;
    case XTypeId_int16:
        return true;
    case XTypeId_u16:
        return true;
    case XTypeId_int32:
        return true;
    case XTypeId_u32:
        return true;
    case XTypeId_float:
        return false;
    case XTypeId_double:
    case XTypeId_vec2:
    case XTypeId_vec3:
    case XTypeId_int2:
        return false;
    default:
        xclu_exception(QString("Unknown XTypeId %1").arg(type));
        break;
    }
    return 0;
}

//---------------------------------------------------------------------
bool is_XTypeId_float(XTypeId type) {
    return (type == XTypeId_float || type == XTypeId_double);
}

//---------------------------------------------------------------------
