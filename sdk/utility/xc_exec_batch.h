#pragma once

//Execute bat/bash scripts.

#include "incl_h.h"

//Execute bat/bash scripts represented as string lists.
//`xc_exec_batch()` function allows to execute bat/bash scripts represented as string lists.
//It's used in ML_Execute module.
//1. Script is parsed: variable {var_name} replaced by var_value
//for example:
//    in `python dataset_tool.py create_from_images {datasets_folder} {images_folder} `
//    `{datasets_folder} and `{image_folder}` will be replaced by values of variables `datasets` and `image_folder` passed to the function.
//2. Script is saved as file with specified name.
//3. Script is executed.

void xc_exec_batch(QStringList script, QString file_to_save,
                 QVector<QString> var_names = QVector<QString>(),
                 QVector<QString> var_values = QVector<QString>());

