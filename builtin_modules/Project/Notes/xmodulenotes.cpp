#include "xmodulenotes.h"
#include "incl_cpp.h"
#include "registrarxmodule.h"
#include "project_props.h"

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
