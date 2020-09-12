#include "xmodulescanfolder.h"
#include "incl_cpp.h"
#include "moduleregistrar.h"
#include <QProcess>
#include "projectruntime.h"


//registering module implementation
REGISTRAR(ScanFolder)

//---------------------------------------------------------------------
/*static*/ XModuleScanFolder *XModuleScanFolder::new_module() {
    return new XModuleScanFolder();
}

//---------------------------------------------------------------------
XModuleScanFolder::XModuleScanFolder()
    :XModule(*static_class_name_ptr)
{

}

//---------------------------------------------------------------------
XModuleScanFolder::~XModuleScanFolder()
{

}

//---------------------------------------------------------------------
void XModuleScanFolder::impl_start() {


}

//---------------------------------------------------------------------
void XModuleScanFolder::impl_update() {


}

//---------------------------------------------------------------------
void XModuleScanFolder::impl_stop() {

}

//---------------------------------------------------------------------
