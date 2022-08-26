#ifndef XMODULENOTES_H
#define XMODULETEST_H

//Notes module.

#include "sdk_h.h"
#include "xclass.h"

class XModuleNotes: public XClass
{
public:
    XModuleNotes(QString class_name);
    virtual ~XModuleNotes();
protected:
    //This is just UI module, without implementation.
    virtual void on_loaded() {}
    virtual void start() {}
    virtual void update() {}
    virtual void stop() {}


};

#endif // XMODULETEST_H
