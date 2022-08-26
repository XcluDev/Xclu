#include "qt_widgets.h"
#include "incl_cpp.h"
#include "xclasswidget.h"
#include "xclassvisualwidget.h"

//---------------------------------------------------------------------
XClassWidget::XClassWidget(QString class_name)
    :XClass(class_name)
{

}

//---------------------------------------------------------------------
XClassWidget::~XClassWidget()
{

}

//-----------------------------------------------
//subclasses must call it for update widget image, an apply update size
//"refresh()" - old name of "redraw()"
void XClassWidget::redraw() {
    if (widget_) {
        //widget_->set_size(screen_size_);
        widget_->update();
    }
}

//-----------------------------------------------
//Resizing widget and getting its current size:
int XClassWidget::screen_w() {
    if (widget_) {
        return widget_->width();
    }
    return 0;
    //return screen_size_.x;
}

//-----------------------------------------------
int XClassWidget::screen_h() {
    if (widget_) {
        return widget_->height();
    }
    return 0;

    //return screen_size_.y;
}

//-----------------------------------------------
int2 XClassWidget::screen_size() {
    return int2(screen_w(), screen_h());
}

//-----------------------------------------------
//Change screen size
void XClassWidget::set_fixed_size(int2 size) {
    xc_assert(widget_, "Internal error at XClassWidget::set_fixed_size() - widget is not created yet");
    widget_->set_fixed_size(size);
    //screen_size_ = size;
}

//---------------------------------------------------------------------
//`create_widget` call implementation, creates QWidget and returns pointer on it
void *XClassWidget::on_create_widget(QString parent_id) {
    xc_assert(!parent_was_set_, "Widget can have only one parent, and it's already set to '" + parent_id_ + "'")
    parent_id_ = parent_id;
    parent_was_set_ = true;

    widget_ = new XModuleVisualWidget(nullptr, this);
    return widget_;
}

//---------------------------------------------------------------------
//reset widget at stop
void XClassWidget::on_reset_widget() {
    widget_ = nullptr;
    parent_id_.clear();
    parent_was_set_ = false;
}

//---------------------------------------------------------------------
//Queuing mouse/keyboard events by widget
void XClassWidget::add_mouse_event(XWidgetEvent_Type type, int2 pos, XMouseButton button) {
    XWidgetEvent event;
    event.type = type;
    event.pos = pos;
    event.button = button;
    widget_events_.write().data().push_back(event);

    //xc_console_append(QString("mouse event %1  %2,%3  %4")
    //                  .arg(type).arg(pos.x).arg(pos.y).arg(button));
}

//---------------------------------------------------------------------
void XClassWidget::add_keyboard_event(XWidgetEvent_Type type, int key) {
    XWidgetEvent event;
    event.type = type;
    event.key = key;
    widget_events_.write().data().push_back(event);

    //xc_console_append(QString("keyboard event %1  %2,%3  %4")
    //                  .arg(type).arg(key));
}

//---------------------------------------------------------------------
void XClassWidget::process_events() {
    //blocking write to widget_events while events_write object exists
    auto events_write = widget_events_.write();
    auto &list = events_write.data();
    //process events
    for (auto &ev: list) {
        switch (ev.type) {
        case XWidgetEvent_none:
            xc_exception("Internal error: XClassWidget::process_events got XWidgetEvent_none event");
            break;
        case XWidgetEvent_mouse_moved:
            mouse_moved(ev.pos);
            break;
        case XWidgetEvent_mouse_pressed:
            mouse_pressed(ev.pos, ev.button);
            break;
        case XWidgetEvent_mouse_dragged:
            mouse_dragged(ev.pos, ev.button);
            break;
        case XWidgetEvent_mouse_released:
            mouse_released(ev.pos, ev.button);
            break;
        case XWidgetEvent_mouse_double_clicked:
            mouse_double_clicked(ev.pos, ev.button);
            break;
        case XWidgetEvent_key_pressed:
            key_pressed(ev.key);
            break;
        case XWidgetEvent_key_released:
            key_released(ev.key);
            break;
        default: xc_exception(QString("Internal error: XClassWidget::process_events got unknown event type %1")
                                      .arg(ev.type));

        }
    }
    //clear the list
    list.clear();
    //now events_write will be deleted and widget_events_ will be unblocked
}

//---------------------------------------------------------------------
