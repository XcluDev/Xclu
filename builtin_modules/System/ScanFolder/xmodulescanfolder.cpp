#include "xmodulescanfolder.h"
#include "incl_cpp.h"
#include "registrarxmodule.h"
#include <QProcess>
#include "xcore.h"


//registering module implementation
REGISTER_XMODULE(ScanFolder)

//---------------------------------------------------------------------
XModuleScanFolder::XModuleScanFolder(QString class_name)
    :XModule(class_name)
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
