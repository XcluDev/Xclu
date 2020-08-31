#ifndef INCL_INCLCPP_H
#define INCL_INCLCPP_H

#include <QDebug>
#include <QRegExp>
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QMessageBox>

#include <QSettings>
#include <QJsonArray>
#include <QJsonObject>

#include "incl_h.h"

#include <QScopedPointer>

#include "xclu_settings.h"
#include "console.h"

//функции для парсинга json - проверка, что это объект или массив, и возвращает этот элемент, или  nullptr
//в случае ошибки - генерирует xclu-исключение
QJsonObject json_object(const QJsonObject &json, QString name);
QJsonArray json_array(const QJsonObject &json, QString name);
QJsonObject json_array_object(const QJsonArray &jsonArray, int i);
QString json_string(const QJsonObject &json, QString name);
bool json_bool(const QJsonObject &json, QString name);

//значения int мы пишем как QString::number(i), но считываем как json_int
int json_int(const QJsonObject &json, QString name);
double json_double(const QJsonObject &json, QString name);



#endif // INCL_INCLCPP_H
