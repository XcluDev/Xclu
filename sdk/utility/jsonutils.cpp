#include "jsonutils.h"
#include "incl_cpp.h"


//---------------------------------------------------------------------
QJsonObject JsonUtils::json_object(const QJsonObject &json, QString name) {
    xc_assert(json.contains(name) && json[name].isObject(),
            "Error parsing JSON, no object '" + name + "'");
    return json[name].toObject();
}

//---------------------------------------------------------------------
QJsonArray JsonUtils::json_array(const QJsonObject &json, QString name) {
    xc_assert(json.contains(name) && json[name].isArray(),
            "Error parsing JSON, no array '" + name + "'");
    return json[name].toArray();
}

//---------------------------------------------------------------------
QJsonObject JsonUtils::json_array_object(const QJsonArray &jsonArray, int i) {
    xc_assert(i >= 0 && i < jsonArray.size() && jsonArray.at(i).isObject(),
            "Error parsing JSON, no array item with index'" + QString::number(i)+ "'");
    return jsonArray.at(i).toObject();
}

//---------------------------------------------------------------------
QString JsonUtils::json_string(const QJsonObject &json, QString name) {
    xc_assert(json.contains(name) && json[name].isString(),
            "Error parsing JSON, no string '" + name + "'");
    return json[name].toString();
}

//---------------------------------------------------------------------
bool JsonUtils::json_bool(const QJsonObject &json, QString name) {
    xc_assert(json.contains(name) && json[name].isBool(),
            "Error parsing JSON, no boolean '" + name + "'");
    return json[name].toBool();
}

//---------------------------------------------------------------------
int JsonUtils::json_int(const QJsonObject &json, QString name) {
    xc_assert(json.contains(name) && json[name].isString(),
            "Error parsing JSON, no int '" + name + "'");
    bool ok;
    int v = json[name].toString().toInt(&ok);
    xc_assert(ok,  "Error parsing JSON, '" + name + "' must be integer value");
    return v;
}

//---------------------------------------------------------------------
double JsonUtils::json_double(const QJsonObject &json, QString name) {
    xc_assert(json.contains(name) && json[name].isString(),
            "Error parsing JSON, no double '" + name + "'");
    bool ok;
    double v = json[name].toString().toDouble(&ok);
    xc_assert(ok,  "Error parsing JSON, '" + name + "' must be double value");
    return v;
}

//---------------------------------------------------------------------
//Read values and use default value if not exists
QString JsonUtils::json_string(const QJsonObject &json, QString name, QString def) {
    if (json.contains(name)) return json_string(json, name);
    return def;
}

//---------------------------------------------------------------------
bool JsonUtils::json_bool(const QJsonObject &json, QString name, bool def) {
    if (json.contains(name)) return json_bool(json, name);
    return def;
}

//---------------------------------------------------------------------
int JsonUtils::json_int(const QJsonObject &json, QString name, int def) {
    if (json.contains(name)) return json_int(json, name);
    return def;
}

//---------------------------------------------------------------------
double JsonUtils::json_double(const QJsonObject &json, QString name, double def) {
    if (json.contains(name)) return json_double(json, name);
    return def;
}

//---------------------------------------------------------------------
