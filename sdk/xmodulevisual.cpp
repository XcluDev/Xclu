#include "qt_widgets.h"
#include "incl_cpp.h"
#include "xmodulevisual.h"
#include "xmodulevisualwidget.h"

//---------------------------------------------------------------------
XModuleVisual::XModuleVisual(QString class_name)
    :XModule(class_name)
{

}

//---------------------------------------------------------------------
XModuleVisual::~XModuleVisual()
{

}

//---------------------------------------------------------------------
//subclasses must reimplement this for drawing
void XModuleVisual::draw(QPainter & /*painter*/, int /*w*/, int /*h*/) {
    xc_exception("draw() is not yet implemented for class `" + class_name() + "`");
}

//-----------------------------------------------
//subclasses must call it for update widget image, an apply update size
void XModuleVisual::refresh() {
    if (widget_) {
        //widget_->set_size(screen_size_);
        widget_->update();
    }
}

//-----------------------------------------------
//Resizing widget and getting its current size:
int XModuleVisual::screen_w() {
    if (widget_) {
        return widget_->width();
    }
    return 0;
    //return screen_size_.x;
}

//-----------------------------------------------
int XModuleVisual::screen_h() {
    if (widget_) {
        return widget_->height();
    }
    return 0;

    //return screen_size_.y;
}

//-----------------------------------------------
int2 XModuleVisual::screen_size() {
    return int2(screen_w(), screen_h());
}

//-----------------------------------------------
//Change screen size
void XModuleVisual::set_fixed_size(int2 size) {
    xc_assert(widget_, "Internal error at XModuleVisual::set_fixed_size() - widget is not created yet");
    widget_->set_fixed_size(size);
    //screen_size_ = size;
}

//---------------------------------------------------------------------
//`create_widget` call implementation, creates QWidget and returns pointer on it
void *XModuleVisual::on_create_widget(QString parent_id) {
    xc_assert(!parent_was_set_, "Widget can have only one parent, and it's already set to '" + parent_id_ + "'")
    parent_id_ = parent_id;
    parent_was_set_ = true;

    widget_ = new XModuleVisualWidget(nullptr, this);
    return widget_;
}

//---------------------------------------------------------------------
//reset widget at stop
void XModuleVisual::on_reset_widget() {
    widget_ = nullptr;
    parent_id_.clear();
    parent_was_set_ = false;
}


//---------------------------------------------------------------------
