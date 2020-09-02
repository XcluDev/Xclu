#ifndef XCLASS_H
#define XCLASS_H

//Xclu base class for implementing "around" modules.
//It provides access for runtime information and module's values

#include "incl_h.h"

class Module;

class XClass
{
public:
    //Constructor requires providing underlying module pointer
    //for accessing its GUI values
    XClass(Module *module);

    //Underlying module
    Module *module();

    //geti
    //getf
    //gets
    //seti
    //setf
    //sets

protected:
    Module *module_;

};

#endif // XCLASS_H
