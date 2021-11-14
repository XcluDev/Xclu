#include "xmodulenotes.h"
#include "incl_cpp.h"
#include "registrarxmodule.h"
#include "xc_project.h"

//registering module implementation
REGISTER_XMODULE(Notes)

//---------------------------------------------------------------------
XModuleNotes::XModuleNotes(QString class_name)
    :XModule(class_name)
{

}

//---------------------------------------------------------------------
XModuleNotes::~XModuleNotes()
{

}

//This is just UI module, without implementation.

//---------------------------------------------------------------------
