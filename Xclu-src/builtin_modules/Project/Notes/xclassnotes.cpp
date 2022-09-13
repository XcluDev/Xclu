#include "xclassnotes.h"
#include "incl_cpp.h"
#include "registrarxclass.h"
#include "project_props.h"

//registering module implementation
REGISTER_XCLASS(Notes)

//---------------------------------------------------------------------
XClassNotes::XClassNotes(QString class_name)
    :XClass(class_name)
{

}

//---------------------------------------------------------------------
XClassNotes::~XClassNotes()
{

}

//This is just UI module, without implementation.

//---------------------------------------------------------------------
