#pragma once

#include "incl_h.h"

//Check file/folder exists
bool xc_file_exists(QString file_name);
bool xc_folder_exists(QString folder_name);

// Get files list in the folder with given extension, for example "jpg"
QStringList xc_folder_list_files(QString folder_name, QString extension = "");
// Variant allowing several extensions: QStringList() << "bmp" << "jpg" << "png" << "tif" << "tiff"
QStringList xc_folder_list_files(QString folder_name, QStringList extensions);

//File size
uint64 xc_file_size(QString file_name);

//Read/write text file
QStringList xc_read_text_file(QString file_name);
void xc_write_text_file(QStringList list, QString file_name);
void xc_write_text_file(QVector<QString> list, QString file_name);

//Write to binary file, with option to append
void xc_write_binary_file(const void *data, int n, QString file_name, bool append = false);

//Read binary file
//Use result.data() for data access
//read_bytes == -1 means read all file, if >=0 - read part of the file
QByteArray xc_read_binary_file(QString file_name, int read_bytes = -1);
