#ifndef EXPORTINTERFACE_H
#define EXPORTINTERFACE_H

//Export interface as h file
//Constructor loads template from `module_h_template.h`

#include "sdk_h.h"
class XModuleInterface;

class ExportInterface
{
public:
    ExportInterface();
    void export_to_h_file(XModuleInterface *interf, QString folder);
    void export_all_builtin_h_files();
private:
    QStringList templ_;

    void append_interface(XModuleInterface *interf, QStringList &file);
};

#endif // EXPORTINTERFACE_H
