#ifndef XCEXECBATCH_H
#define XCEXECBATCH_H

//Execute bat/bash scripts represented as string lists.
//1. Script is parsed: variables {var_name} replaced by var_value
//2. Script is saved as file
//3. Script is executed

#include "incl_h.h"

void xc_exec_batch(QStringList script, QString file_to_save,
                 QVector<QString> var_names = QVector<QString>(),
                 QVector<QString> var_values = QVector<QString>());


#endif // XCEXECBATCH_H
