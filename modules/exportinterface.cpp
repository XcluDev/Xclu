#include "exportinterface.h"
#include "incl_cpp.h"

//---------------------------------------------------------------------
ExportInterface::ExportInterface()
{

}

//---------------------------------------------------------------------
void ExportInterface::export_to_file(ModuleInterface *interf, QString folder) {
    xclu_console_append("Exporting to `" + folder + "`");

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
