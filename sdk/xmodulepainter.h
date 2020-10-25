#ifndef XMODULEPAINTER_H
#define XMODULEPAINTER_H

//Runtime module class with drawing to widget capability

#include "sdk_h.h"
#include "xmodule.h"

class InterfaceItem;
class Module;
class XObject;
class QPainter;
class XModulePainterWidget;

class XModulePainter : public XModule
{
    Q_OBJECT
public:
    XModulePainter(QString class_name);
    virtual ~XModulePainter();

    //-----------------------------------------------
    //subclasses must reimplement this for drawing
    virtual void draw(QPainter &painter, int w, int h);

    //-----------------------------------------------
    //subclasses must call it for repaing widget image, and to apply size chane
    void screen_repaint();

    //-----------------------------------------------
    //Getting current size:
    int screen_w();
    int screen_h();
    int2 screen_size();
    //Change screen size - applied after calling repaint
    void set_screen_size(int2 size);
protected:
    //`create_widget` call implementation, creates QWidget and returns pointer on it
    virtual void *impl_create_widget(QString parent_id);

    //reset widget at stop
    virtual void impl_reset_widget();

    //information about parent for rendering
    bool parent_was_set_ = false;
    QString parent_id_ = "";

    int2 screen_size_ = int2(100,100);
    XModulePainterWidget *widget_ = nullptr;

};

#endif // XMODULEPAINTER_H
