#include "exportinterface.h"
#include "incl_cpp.h"
#include "moduleinterface.h"

//---------------------------------------------------------------------
ExportInterface::ExportInterface()
{

}

//---------------------------------------------------------------------
void ExportInterface::export_to_file(ModuleInterface *interf, QString folder) {
    //interf->description().class_name can be not set, so deduce from folder name
    QString class_name = "XClass" + QFileInfo(folder).baseName();

    QString file_name = folder + "/" + class_name + ".h";
    xclu_console_append("Exporting to `" + file_name + "`");


    QStringList hfile;
    for (auto &T: templ_) {
        hfile.append(T);    //test
        //CLASS_NAME
        //DATETIME
        //ITEMS

        //QStringList list = item->generate_cpp_header();
    }
}

//---------------------------------------------------------------------
