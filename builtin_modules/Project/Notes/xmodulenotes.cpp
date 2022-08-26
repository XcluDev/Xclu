#include "xmodulenotes.h"
#include "incl_cpp.h"
#include "registrarxclass.h"
#include "project_props.h"

//registering module implementation
REGISTER_XCLASS(Notes)

//---------------------------------------------------------------------
XModuleNotes::XModuleNotes(QString class_name)
    :XClass(class_name)
{

}

//---------------------------------------------------------------------
XModuleNotes::~XModuleNotes()
{

}

//This is just UI module, without implementation.

//---------------------------------------------------------------------
