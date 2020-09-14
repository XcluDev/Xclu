#include "qt_widgets.h"
#include "xmodulewimage.h"

#include "incl_cpp.h"
#include "moduleregistrar.h"
#include "projectruntime.h"
#include "module.h"
#include "xdict.h"
#include "xcluobjectwrapper.h"



//registering module implementation
REGISTRAR(WImage)

//---------------------------------------------------------------------
/*static*/ XModuleWImage *XModuleWImage::new_module() {
    return new XModuleWImage();
}

//---------------------------------------------------------------------
XModuleWImage::XModuleWImage()
    :XModule(*static_class_name_ptr)
{

}

//---------------------------------------------------------------------
XModuleWImage::~XModuleWImage()
{

}

//---------------------------------------------------------------------
void XModuleWImage::impl_start() {
    //сбрасываем родителя - это будет установлено в impl_call, когда родитель запросит
    parent_was_set_ = false;
    parent_id_ = "";
    clear_string_parent_id();

    DataAccess access(data_);
    data_.clear();

    seti_is_new_frame(0);

    clear_image();

}

//---------------------------------------------------------------------
void XModuleWImage::impl_update() {

    //установка всех значений, если они изменились
    update_all(false);
}


//---------------------------------------------------------------------
void XModuleWImage::impl_stop() {
    //нам не надо удалять виджет - так как он будет удален родителем
    //поэтому, просто обнуляем
    widget_ = nullptr;
    image_ = nullptr;
}

//---------------------------------------------------------------------
//`create_widget` call implementation, creates QWidget and returns pointer on it
void *XModuleWImage::impl_create_widget(QString parent_id) {
    xclu_assert(!parent_was_set_, "Widget can have only one parent, and it's already set to '" + parent_id_ + "'")

    parent_id_ = parent_id;
    sets_parent_id(parent_id_);
    parent_was_set_ = true;

    //создаем виджет
    //insert_label(input);
    image_ = new QLabel();
    widget_ = image_;
    //очистка данных - важно чтобы уничтожились перед вызовом update_all()
    {
        DataAccess access(data_);
        data_.clear();
    }
    //отслеживание изменений
    //connect(spin_, QOverload<int>::of(&QSpinBox::valueChanged),
    //      [=](int /*i*/){ spin_changed(); });

    //установка всех значений
    update_all(true);

    return widget_;
}

//---------------------------------------------------------------------
void XModuleWImage::update_all(bool force) {
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


}

//---------------------------------------------------------------------
void XModuleWImage::update_value() {
    int new_frame = RUNTIME.get_int_by_link(gets_is_new_frame_link());
    seti_is_new_frame(new_frame);

    if (new_frame) {
        XDict *object = RUNTIME.get_object_by_link(gets_image_link());
        {
            XDictRead obj(object);
            obj.copy_to(getobj_image());
        }

        if (image_) {

            //устанавливаем настройки показа
            XDictShowSettings settings;
            settings.w = geti_w();
            settings.h = geti_h();

            //создаем wrapper для объекта, который установится в зависимости от его типа,
            //и вызываем функцию для его визуализации
            QScopedPointer<XDictWrapper> wrapper;
           wrapper.reset(XDictWrapper::create_wrapper(object));

           wrapper->show_object(image_, settings);
        }
    }

}


//---------------------------------------------------------------------
void XModuleWImage::set_image(const QImage &image) {
    if (image_) {
        QPixmap pix = QPixmap::fromImage(image);
        image_->setPixmap(pix);
        //image_->setVisible(true);
    }
}

//---------------------------------------------------------------------
void XModuleWImage::clear_image() {
    if (image_) {
        image_->setText("");
        image_->setVisible(false);
        //spacer_->spacerItem()-> setVisible(false);
    }
}

//---------------------------------------------------------------------













