#include "exportinterface.h"
#include "incl_cpp.h"
#include "moduleinterface.h"
#include "modulesfactory.h"
#include <QDateTime>

//---------------------------------------------------------------------
ExportInterface::ExportInterface()
{
    //Reading template
    QString file_name = xclu_module_h_template_file();
    templ_ = xclu_read_text_file(file_name);
}

//---------------------------------------------------------------------
//Template:
//CLASS_NAME - replace with class name
//DATETIME - replace with date time
//CONTENT - replace with lines we want

void ExportInterface::export_to_h_file(ModuleInterface *interf, QString folder) {
    //interf->description().class_name can be not set, so deduce it from folder name
    QString class_name = "XClass" + QFileInfo(folder).baseName();

    QString file_name = folder + "/" + "auto.h"; //class_name + ".h";

    QStringList file;
    for (auto T: templ_) {
        if (T == "CONTENT") {
            //put all we want
            append_interface(interf, file);
            continue;
        }
        if (T.contains("CLASS_NAME")) {
            T.replace("CLASS_NAME", class_name);
            file.append(T);
            continue;
        }
        if (T.contains("DATETIME")) {
            QString date_time = QDateTime::currentDateTime()
                    .toString("yyyy.MM.dd hh:mm:ss");
            T.replace("DATETIME", date_time);
            file.append(T);
            continue;
        }
        file.append(T);    //test

        //QStringList list = item->generate_cpp_header();
    }

    xclu_write_text_file(file, file_name);
}

//---------------------------------------------------------------------
void ExportInterface::append_interface(ModuleInterface *interf, QStringList &file) {
    //So, let's put it here!
    for (auto &item: interf->items()) {
        if (!item->belongs_general_page()) {
            item->export_interface(file);
        }
    }
}

//---------------------------------------------------------------------
void ExportInterface::export_all_builtin_h_files() {
    int n = FACTORY.size();
    for (int i=0; i<n; i++) {
        ModuleSeed *seed = FACTORY.get_module(i);
        if (!seed) {
            continue;
        }
        try {
            //Create interface
            QScopedPointer<ModuleInterface> interf;
            interf.reset(new ModuleInterface(*seed));
            if (!interf.data()) continue;

            //Export
            export_to_h_file(interf.data(), seed->folder());
        }
        catch(XCluException& /*e*/) {
            xclu_console_append("Error at `" + seed->description.class_name + "`");
        }
    }

}

//---------------------------------------------------------------------
