#ifndef XPARSER_H
#define XPARSER_H

//Parsing numbers
#include <QString>

float xparse_float(QString line, QString error_message);
int xparse_int(QString line, QString error_message);


//seconds -> HMS, that is 00:00:00:0
QString xparse_seconds_to_hms(double seconds);

#endif // XPARSER_H
