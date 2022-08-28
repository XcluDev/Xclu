#include "xtypeid.h"
#include "xerrorhandling.h"

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
        xc_exception(QString("Unknown XTypeId %1").arg(int(type)));
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
        xc_exception(QString("XTypeId_channels - Unknown XTypeId %1").arg(int(type)));
        break;
    }
    return 0;
}

//---------------------------------------------------------------------
QString XTypeId_to_string(XTypeId type) {
    switch (type) {
    case XTypeId::none:
        return "none";
    case XTypeId::uint8:
        return "uint8";
    case XTypeId::rgb_u8:
        return "rgb_u8";
    case XTypeId::rgba_u8:
        return "rgba_u8";
    case XTypeId::int8:
        return "int8";
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
    if (type == "uint8") return XTypeId::uint8;
    if (type == "rgb_u8") return XTypeId::rgb_u8;
    if (type == "rgba_u8") return XTypeId::rgba_u8;
    if (type == "int8") return XTypeId::int8;
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
        xc_exception(QString("Unknown XTypeId %1").arg(int(type)));
        break;
    }
    return 0;
}

//---------------------------------------------------------------------
bool is_XTypeId_float(XTypeId type) {
    return (type == XTypeId::float32 || type == XTypeId::float64);
}

//---------------------------------------------------------------------
template<> XTypeId type_to_XTypeId<uint8>() { return XTypeId::uint8; }
template<> XTypeId type_to_XTypeId<rgb_u8>() { return XTypeId::rgb_u8; }
template<> XTypeId type_to_XTypeId<rgba_u8>() { return XTypeId::rgba_u8; }
template<> XTypeId type_to_XTypeId<int8>() { return XTypeId::int8; }
template<> XTypeId type_to_XTypeId<int16>() { return XTypeId::int16; }
template<> XTypeId type_to_XTypeId<uint16>() { return XTypeId::uint16; }
template<> XTypeId type_to_XTypeId<int32>() { return XTypeId::int32; }
template<> XTypeId type_to_XTypeId<uint32>() { return XTypeId::uint32; }
template<> XTypeId type_to_XTypeId<float>() { return XTypeId::float32; }
template<> XTypeId type_to_XTypeId<double>() { return XTypeId::float64; }
template<> XTypeId type_to_XTypeId<vec2>() { return XTypeId::vec2; }
template<> XTypeId type_to_XTypeId<vec3>() { return XTypeId::vec3; }
template<> XTypeId type_to_XTypeId<vec4>() { return XTypeId::vec4; }
template<> XTypeId type_to_XTypeId<int2>() { return XTypeId::int2; }

//---------------------------------------------------------------------
