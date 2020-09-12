#ifndef EXPORTINTERFACE_H
#define EXPORTINTERFACE_H

//Export interface as h file
//Constructor loads template from `module_h_template.h`

#include "incl_h.h"
class ModuleInterface;

class ExportInterface
{
public:
    ExportInterface();
    void export_to_file(ModuleInterface *interf, QString folder);
private:
    QStringList templ_;

    void append_interface(ModuleInterface *interf, QStringList &file);
};

#endif // EXPORTINTERFACE_H
