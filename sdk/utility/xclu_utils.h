#ifndef XCLU_UTILS_H
#define XCLU_UTILS_H

#include "incl_h.h"


//замена подчеркивания на пробел в заголовках: Abc_Def -> "Abc Def"
QString xc_remove_underscore(QString title);

QStringList xc_read_text_file(QString file_name);
void xc_write_text_file(QStringList list, QString file_name);

#endif // XCLU_UTILS_H
