#ifndef JSONUTILS_H
#define JSONUTILS_H

//Functions for JSOn parsing - checking if it's object or array, and returns it.
//In case of error raises xclu-exception.

#include <QJsonArray>
#include <QJsonObject>

class JsonUtils
{
public:
    static QJsonObject json_object(const QJsonObject &json, QString name);
    static QJsonArray json_array(const QJsonObject &json, QString name);
    static QJsonObject json_array_object(const QJsonArray &jsonArray, int i);
    static QString json_string(const QJsonObject &json, QString name);
    static bool json_bool(const QJsonObject &json, QString name);

    //значения int мы пишем как QString::number(i), но считываем как json_int
    static int json_int(const QJsonObject &json, QString name);
    static double json_double(const QJsonObject &json, QString name);

};

#endif // JSONUTILS_H
