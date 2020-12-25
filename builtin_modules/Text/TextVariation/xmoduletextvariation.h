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
    virtual void on_loaded() {}
    virtual void start();
    virtual void update();
    virtual void stop();
    //virtual void on_button_pressed(QString button_id);

    //Recursive function for building variation
    //For [A|B|C[D|E]] input it will generate randomly A,B,CD,CE.
    //level - for debugging
    QString variate(QString text, int level);
};



#endif // XMODULERANDOM_H
