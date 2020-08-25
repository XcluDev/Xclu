#include "incl_cpp.h"


//---------------------------------------------------------------------
QJsonObject json_object(const QJsonObject &json, QString name) {
    xclu_assert(json.contains(name) && json[name].isObject(),
            "Error parsing JSON, no object '" + name + "'");
    return json[name].toObject();
}

//---------------------------------------------------------------------
QJsonArray json_array(const QJsonObject &json, QString name) {
    xclu_assert(json.contains(name) && json[name].isArray(),
            "Error parsing JSON, no array '" + name + "'");
    return json[name].toArray();
}

//---------------------------------------------------------------------
QJsonObject json_array_object(const QJsonArray &jsonArray, int i) {
    xclu_assert(i >= 0 && i < jsonArray.size() && jsonArray.at(i).isObject(),
            "Error parsing JSON, no array item with index'" + QString::number(i)+ "'");
    return jsonArray.at(i).toObject();
}

//---------------------------------------------------------------------
QString json_string(const QJsonObject &json, QString name) {
    xclu_assert(json.contains(name) && json[name].isString(),
            "Error parsing JSON, no string '" + name + "'");
    return json[name].toString();
}

//---------------------------------------------------------------------
bool json_bool(const QJsonObject &json, QString name) {
    xclu_assert(json.contains(name) && json[name].isBool(),
            "Error parsing JSON, no boolean '" + name + "'");
    return json[name].toBool();
}

//---------------------------------------------------------------------
int json_int(const QJsonObject &json, QString name) {
    xclu_assert(json.contains(name) && json[name].isString(),
            "Error parsing JSON, no int '" + name + "'");
    bool ok;
    int v = json[name].toString().toInt(&ok);
    xclu_assert(ok,  "Error parsing JSON, '" + name + "' must be integer value");
    return v;
}

//---------------------------------------------------------------------
double json_double(const QJsonObject &json, QString name) {
    xclu_assert(json.contains(name) && json[name].isString(),
            "Error parsing JSON, no double '" + name + "'");
    bool ok;
    double v = json[name].toString().toDouble(&ok);
    xclu_assert(ok,  "Error parsing JSON, '" + name + "' must be double value");
    return v;
}

//---------------------------------------------------------------------

