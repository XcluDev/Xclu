#pragma once

//Runtime module class with drawing to widget capability

#include "sdk_h.h"
#include "xclass.h"

class InterfaceItem;
class XModule;
class XObject;
class QPainter;
class XModuleVisualWidget;

class XClassWidget : public XClass
{
    Q_OBJECT
public:
    XClassWidget(QString class_name);
    virtual ~XClassWidget();

    //-----------------------------------------------
    //subclasses MUST reimplement this for drawing
    //and call redraw() for repainting!
    //virtual void draw(QPainter &painter, int w, int h);

    //-----------------------------------------------
    //subclasses MUST call it for repaing widget image, and to apply size change - normally, inside update()
    void redraw();

    //-----------------------------------------------
    //Getting current size:
    int screen_w();
    int screen_h();
    int2 screen_size();
    //Change screen size
    void set_fixed_size(int2 size);

    //----------------------------------------------
    //Virtual functions for processing mouse and keyboard events
    //I use "openFrameworks style"
    //They are called automatically at process_events() - before update()
    //But queued asyncronically by widget calls of add_mouse_event(), add_keyboard_event()
    virtual void mouse_moved(int2 /*pos*/) {}
    virtual void mouse_pressed(int2 /*pos*/, XMouseButton /*button*/) {}
    virtual void mouse_dragged(int2 /*pos*/, XMouseButton /*button*/) {}
    virtual void mouse_released(int2 /*pos*/, XMouseButton /*button*/) {}
    virtual void mouse_double_clicked(int2 /*pos*/, XMouseButton /*button*/) {}

    //Note: Currently keyboard events are not sent. May be need set focus on the widget?
    virtual void key_pressed(int /*key*/) {}
    virtual void key_released(int /*key*/) {}

    //----------------------------------------------
    //Queuing mouse/keyboard events by widget
    void add_mouse_event(XWidgetEvent_Type type, int2 pos, XMouseButton button);
    void add_keyboard_event(XWidgetEvent_Type type, int key);


private:
    //Process mouse/keyboard events by calling virtual functions
    //this function is called in XClass::bang_update, before module's update()
    virtual void process_events();

    //It's protected data, because widget event can occur asyncronous
    XProtectedData_<QVector<XWidgetEvent>> widget_events_;

protected:
    //`create_widget` call implementation, creates QWidget and returns pointer on it
    virtual void *on_create_widget(QString parent_id);

    //reset widget at stop
    virtual void on_reset_widget();

    //information about parent for rendering
    bool parent_was_set_ = false;
    QString parent_id_ = "";

    //int2 screen_size_ = int2(100,100);
    XModuleVisualWidget *widget_ = nullptr;

};

