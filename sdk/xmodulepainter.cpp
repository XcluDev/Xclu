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
    xc_exception("draw() is not yet implemented for class `" + class_name() + "`");
}

//-----------------------------------------------
//subclasses must call it for update widget image, an apply update size
void XModulePainter::refresh() {
    if (widget_) {
        //widget_->set_size(screen_size_);
        widget_->update();
    }
}

//-----------------------------------------------
//Resizing widget and getting its current size:
int XModulePainter::screen_w() {
    if (widget_) {
        return widget_->width();
    }
    return 0;
    //return screen_size_.x;
}

//-----------------------------------------------
int XModulePainter::screen_h() {
    if (widget_) {
        return widget_->height();
    }
    return 0;

    //return screen_size_.y;
}

//-----------------------------------------------
int2 XModulePainter::screen_size() {
    return int2(screen_w(), screen_h());
}

//-----------------------------------------------
//Change screen size
void XModulePainter::set_fixed_size(int2 size) {
    xc_assert(widget_, "Internal error at XModulePainter::set_fixed_size() - widget is not created yet");
    widget_->set_fixed_size(size);
    //screen_size_ = size;
}

//---------------------------------------------------------------------
//`create_widget` call implementation, creates QWidget and returns pointer on it
void *XModulePainter::on_create_widget(QString parent_id) {
    xc_assert(!parent_was_set_, "Widget can have only one parent, and it's already set to '" + parent_id_ + "'")
    parent_id_ = parent_id;
    parent_was_set_ = true;

    widget_ = new XModulePainterWidget(nullptr, this);
    return widget_;
}

//---------------------------------------------------------------------
//reset widget at stop
void XModulePainter::on_reset_widget() {
    widget_ = nullptr;
    parent_id_.clear();
    parent_was_set_ = false;
}


//---------------------------------------------------------------------
