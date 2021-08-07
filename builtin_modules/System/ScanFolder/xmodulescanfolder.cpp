#include "xmodulescanfolder.h"
#include "incl_cpp.h"
#include "registrarxmodule.h"
#include <QProcess>
#include "xc_project.h"


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
void XModuleScanFolder::start() {


}

//---------------------------------------------------------------------
void XModuleScanFolder::update() {


}

//---------------------------------------------------------------------
void XModuleScanFolder::stop() {

}

//---------------------------------------------------------------------
