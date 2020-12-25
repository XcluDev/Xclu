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
    xc_exception("draw() is not implemented for class `" + class_name() + "`");
}

//-----------------------------------------------
//subclasses must call it for update widget image, an apply update size
void XModulePainter::screen_repaint() {
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
void XModulePainter::set_screen_size(int2 size) {
    screen_size_ = size;
}

//---------------------------------------------------------------------
//`create_widget` call implementation, creates QWidget and returns pointer on it
void *XModulePainter::impl_create_widget(QString parent_id) {
    xc_assert(!parent_was_set_, "Widget can have only one parent, and it's already set to '" + parent_id_ + "'")
    parent_id_ = parent_id;
    parent_was_set_ = true;

    widget_ = new XModulePainterWidget(nullptr, this);
    return widget_;
}

//---------------------------------------------------------------------
//reset widget at stop
void XModulePainter::impl_reset_widget() {
    widget_ = nullptr;
    parent_id_.clear();
    parent_was_set_ = false;
}


//---------------------------------------------------------------------
