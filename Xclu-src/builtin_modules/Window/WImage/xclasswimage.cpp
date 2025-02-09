#include "qt_widgets.h"
#include "xclasswimage.h"

#include "incl_cpp.h"
#include "registrarxclass.h"
#include "project_props.h"
#include "xobject.h"

//registering module implementation
REGISTER_XCLASS(WImage)

//---------------------------------------------------------------------
XClassWImage::XClassWImage(QString class_name)
    :XClass(class_name)
{
    xc_exception("XClassWImage is not implemented, please not use it");
}

//---------------------------------------------------------------------
XClassWImage::~XClassWImage()
{

}

//---------------------------------------------------------------------
void XClassWImage::start() {
    /*
    //сбрасываем родителя - это будет установлено в on_call, когда родитель запросит
    parent_was_set_ = false;
    parent_id_ = "";
    clear_string_parent_id();
    clear_image();
    */
}

//---------------------------------------------------------------------
void XClassWImage::update() {
    /*
    //установка всех значений, если они изменились
    update_all(false);
    */
}


//---------------------------------------------------------------------
void XClassWImage::stop() {
    /*
    //нам не надо удалять виджет - так как он будет удален родителем
    //поэтому, просто обнуляем
    widget_ = nullptr;
    image_label_ = nullptr;
    */
}

//---------------------------------------------------------------------
//`create_widget` call implementation, creates QWidget and returns pointer on it
void *XClassWImage::on_create_widget(QString parent_id) {
    return nullptr;
    /*
    xc_assert(!parent_was_set_, "Widget can have only one parent, and it's already set to '" + parent_id_ + "'")

    parent_id_ = parent_id;
    sets_parent_id(parent_id_);
    parent_was_set_ = true;

    //создаем виджет
    //insert_label(input);
    image_label_ = new QLabel();
    widget_ = image_label_;

    //track changes
    //connect(spin_, QOverload<int>::of(&QSpinBox::valueChanged),
    //      [=](int){ spin_changed(); });

    //установка всех значений
    update_all(true);

    return widget_;
    */
}

//---------------------------------------------------------------------
//reset widget at stop
void XClassWImage::on_reset_widget() {
    /*
    widget_ = nullptr;
    parent_id_.clear();
    parent_was_set_ = false;
    */
}

//---------------------------------------------------------------------
void XClassWImage::update_all(bool force) {
    /*
    if (!widget_) {
        return;
    }
    //parent_id - set by call

    //int visible
    if (force || was_changed_visible()) {
        widget_->setVisible(geti_visible());
    }

    //итоговое значение
    update_value();
*/

}

//---------------------------------------------------------------------
void XClassWImage::update_value() {
    /*
    if (geti_is_new_frame()) {
        if (image_label_) {
            //устанавливаем настройки показа
            XObjectShowSettings settings;
            settings.w = geti_w();
            settings.h = geti_h();

            QScopedPointer<XObjectWrapper> wrapper;
            wrapper.reset(XObjectWrapper::create_wrapper(getobject_image()->read().pointer()));

            wrapper->draw_thumbnail(image_label_, settings);
        }
    }
*/
}


//---------------------------------------------------------------------
void XClassWImage::set_image(const QImage &image) {
    /*
    if (image_label_) {
        QPixmap pix = QPixmap::fromImage(image);
        image_label_->setPixmap(pix);
        //image_label_->setVisible(true);
    }
    */
}

//---------------------------------------------------------------------
void XClassWImage::clear_image() {
    /*
    if (image_label_) {
        image_label_->setText("");
        image_label_->setVisible(false);
        //spacer_->spacerItem()-> setVisible(false);
    }
    */
}

//---------------------------------------------------------------------













