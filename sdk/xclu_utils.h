#ifndef XCLU_UTILS_H
#define XCLU_UTILS_H

#include "incl_h.h"


//замена подчеркивания на пробел в заголовках: Abc_Def -> "Abc Def"
QString xclu_remove_underscore(QString title);

QStringList xclu_read_text_file(QString file_name);
void xclu_write_text_file(QStringList list, QString file_name);

#endif // XCLU_UTILS_H
