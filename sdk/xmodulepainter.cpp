#include "qt_widgets.h"
#include "incl_cpp.h"
#include "xmodulepainter.h"
#include "xmodulepainterwidget.h"

//---------------------------------------------------------------------
XModulePainter::XModulePainter(QString class_name)
    :XModule(class_name)
{

}

//---------------------------------------------------------------------
XModulePainter::~XModulePainter()
{

}

//---------------------------------------------------------------------
//subclasses must reimplement this for drawing
void XModulePainter::draw(QPainter & /*painter*/, int /*w*/, int /*h*/) {
    xclu_exception("draw() is not implemented for class `" + class_name() + "`");
}

//-----------------------------------------------
//subclasses must call it for update widget image, an apply update size
void XModulePainter::repaint() {
    if (widget_) {
        widget_->set_size(screen_size_);
        widget_->update();
    }
}

//-----------------------------------------------
//Resizing widget and getting its current size:
int XModulePainter::screen_w() {
    return screen_size_.x;
}

//-----------------------------------------------
int XModulePainter::screen_h() {
    return screen_size_.y;
}

//-----------------------------------------------
int2 XModulePainter::screen_size() {
    return screen_size_;
}

//-----------------------------------------------
//Change screen size - applied after calling repaint
//applied
void XModulePainter::screen_resize(int2 size) {
    screen_size_ = size;
}

//---------------------------------------------------------------------
//`create_widget` call implementation, creates QWidget and returns pointer on it
void *XModulePainter::impl_create_widget(QString parent_id) {
    xclu_assert(!parent_was_set_, "Widget can have only one parent, and it's already set to '" + parent_id_ + "'")
    parent_id_ = parent_id;
    parent_was_set_ = true;

    widget_ = new XModulePainterWidget(nullptr, this);
    return widget_;
}

//---------------------------------------------------------------------
