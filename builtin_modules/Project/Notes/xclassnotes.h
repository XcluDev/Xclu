#ifndef XCLASSNOTES_H
#define XCLASSTEST_H

//Notes module.

#include "sdk_h.h"
#include "xclass.h"

class XClassNotes: public XClass
{
public:
    XClassNotes(QString class_name);
    virtual ~XClassNotes();
protected:
    //This is just UI module, without implementation.
    virtual void on_loaded() {}
    virtual void start() {}
    virtual void update() {}
    virtual void stop() {}


};

#endif // XCLASSTEST_H
