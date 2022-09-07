#include "xexecbatch.h"
#include "incl_cpp.h"
#include "xfiles.h"

//---------------------------------------------------------------------
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
                 QVector<QString> var_names,
                   QVector<QString> var_values) {
    xc_assert(var_names.size() == var_values.size(), "xc_exec_batch error - var_names and var_values must have the same size");
    //Parse
    for (auto &line: script) {
        for (int i=0; i<var_names.size(); i++) {
            line = line.replace("{" + var_names[i] + "}", var_values[i]);
        }
    }
    //Save
    xc_write_text_file(script, file_to_save);

    //Execute
    //TODO not tested in Linux - need to set admin rights
}

//---------------------------------------------------------------------
/*float xparse_float(QString line, QString error_message) {
    bool ok;
    float value = line.toFloat(&ok);
    xc_assert(ok, error_message);
    return value;
}*/

//---------------------------------------------------------------------
