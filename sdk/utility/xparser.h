#ifndef XPARSER_H
#define XPARSER_H

//Parsing utilities

#include <QString>

//Parsing numbers
float xparse_float(QString line, QString error_message);
int xparse_int(QString line, QString error_message);

//Replace "_" to " ", used in interpreting XGUI: Abc_Def -> "Abc Def"
QString xc_remove_underscore(QString title);

//Seconds -> HMS, that is 00:00:00:0
QString xparse_seconds_to_hms(double seconds);

#endif // XPARSER_H
