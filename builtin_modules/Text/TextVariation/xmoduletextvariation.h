#ifndef XMODULERANDOM_H
#define XMODULERANDOM_H

//TextVariation implementation
//For [A|B|C[D|E]] input it will generate randomly A,B,CD,CE.

#include "sdk_h.h"
#include "xmodule.h"

class XModuleTextVariation: public XModule
{
public:
    XModuleTextVariation(QString class_name);
    ~XModuleTextVariation();
#include "auto.h"

protected:
    virtual void impl_loaded() {}
    virtual void impl_start();
    virtual void impl_update();
    virtual void impl_stop();
    //virtual void impl_button_pressed(QString button_id);

    //Recursive function for building variation
    //For [A|B|C[D|E]] input it will generate randomly A,B,CD,CE.
    //level - for debugging
    QString variate(QString text, int level);
};



#endif // XMODULERANDOM_H
