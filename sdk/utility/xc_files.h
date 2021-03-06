#ifndef XCLU_UTILS_H
#define XCLU_UTILS_H

#include "incl_h.h"

QStringList xc_read_text_file(QString file_name);
void xc_write_text_file(QStringList list, QString file_name);

//Writing to binary file, with option to append
void xc_write_binary_file(const void *data, int n, QString file_name, bool append = false);

#endif // XCLU_UTILS_H
