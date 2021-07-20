#ifndef XCLU_UTILS_H
#define XCLU_UTILS_H

#include "incl_h.h"

//Check file/folder exists
bool xc_file_exists(QString file_name);
bool xc_folder_exists(QString folder_name);

//File size
uint64 xc_file_size(QString file_name);

//Read/write text file
QStringList xc_read_text_file(QString file_name);
void xc_write_text_file(QStringList list, QString file_name);

//Write to binary file, with option to append
void xc_write_binary_file(const void *data, int n, QString file_name, bool append = false);

//Read binary file
//Use result.data() for data access
//read_bytes == -1 means read all file, if >=0 - read part of the file
QByteArray xc_read_binary_file(QString file_name, int read_bytes = -1);


#endif // XCLU_UTILS_H
