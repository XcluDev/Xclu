#include "xmodulescanfolder.h"
#include "incl_cpp.h"
#include "registrarxmodule.h"
#include <QProcess>
#include "project_props.h"


//registering module implementation
REGISTER_XMODULE(ScanFolder)

//---------------------------------------------------------------------
XModuleScanFolder::XModuleScanFolder(QString class_name)
    :XClass(class_name)
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
