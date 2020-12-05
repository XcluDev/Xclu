#include "xmodulefilecreate.h"
#include "incl_cpp.h"
#include "registrarxmodule.h"
#include <QProcess>
#include "xcore.h"


//registering module implementation
REGISTER_XMODULE(FileCreate)

//---------------------------------------------------------------------
XModuleFileCreate::XModuleFileCreate(QString class_name)
    :XModule(class_name)
{


}

//---------------------------------------------------------------------
XModuleFileCreate::~XModuleFileCreate()
{

}

//---------------------------------------------------------------------
void XModuleFileCreate::impl_button_pressed(QString button_id) {
    if (button_id == button_create_file_btn()) {
        //Getting file size
        uint64 size = 0;
        switch (gete_file_size_unit()) {
        case file_size_unit_Bytes:
            size = geti_file_size_b();
            break;
        case file_size_unit_Kilobytes:
            size = uint64(getf_file_size_kb() * 1024);
            break;
        case file_size_unit_Megabytes:
            size = uint64(getf_file_size_kb() * (1024*1024));
            break;
        case file_size_unit_Gigabytes:
            size = uint64(getf_file_size_kb() * (1024*1024*1024));
            break;
        default:
            xclu_exception("XModuleFileCreate::impl_button_pressed - bad Unit of file size measure");
        }

        //Getting file name and checking it's not exists
        QString file_name0 = gets_file_name();
        QString file_name = xcore_abs_path(gets_file_name());
        QString base_name = QFileInfo(file_name).baseName();

        sets_last_operation(QString("Created %1: %2 bytes").arg(base_name).arg(size));

    }

}

//---------------------------------------------------------------------
void XModuleFileCreate::impl_start() {


}

//---------------------------------------------------------------------
void XModuleFileCreate::impl_update() {


}

//---------------------------------------------------------------------
void XModuleFileCreate::impl_stop() {


}

//---------------------------------------------------------------------
