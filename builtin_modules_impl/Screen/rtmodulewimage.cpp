#include "qt_widgets.h"
#include "rtmodulewimage.h"

#include "incl_qtcpp.h"
#include "rtmoduleregistrar.h"
#include "projectruntime.h"
#include "module.h"
#include "xcluobject.h"
#include "xcluobjectwrapper.h"



//заполнение имени класса и регистрация класса
REGISTRAR(WImage)

//---------------------------------------------------------------------
/*static*/ RtModuleWImage *RtModuleWImage::new_module() {
    return new RtModuleWImage();
}

//---------------------------------------------------------------------
RtModuleWImage::RtModuleWImage()
    :RtModule(*static_class_name_ptr)
{

}

//---------------------------------------------------------------------
RtModuleWImage::~RtModuleWImage()
{

}

//---------------------------------------------------------------------
void RtModuleWImage::execute_start_internal() {
    //сбрасываем родителя - это будет установлено в call_internal, когда родитель запросит
    parent_was_set_ = false;
    parent_id_ = "";
    clear_string("parent_id");

    DataAccess access(data_);
    data_.clear();

    set_int("is_new_frame",0);

    clear_image();

}

//---------------------------------------------------------------------
void RtModuleWImage::execute_update_internal() {

    //установка всех значений, если они изменились
    update_all(false);
}


//---------------------------------------------------------------------
void RtModuleWImage::execute_stop_internal() {
    //нам не надо удалять виджет - так как он будет удален родителем
    //поэтому, просто обнуляем
    widget_ = nullptr;
    image_ = nullptr;
}

//---------------------------------------------------------------------
//Вызов
void RtModuleWImage::call_internal(QString function, XcluObject *input, XcluObject *output) {
    //"get_widget_pointer"
    if (function == call_function_name::get_widget_pointer()) {
        xclu_assert(!parent_was_set_, "Widget can have only one parent, and it's already set to '" + parent_id_ + "'")

        //call get_widget_pointer
        //Window calls GUI elements to insert them into itself.
        //string parent_id
        //out pointer widget_pointer

        //проверка, что оба объекта переданы
        xclu_assert(input, "Internal error, input object is nullptr");
        xclu_assert(output, "Internal error, output object is nullptr");

        //устанавливаем, кто использует
        parent_id_ = ObjectRead(input).get_string("parent_id");
        set_string("parent_id", parent_id_);
        parent_was_set_ = true;

        //проверяем, что еще не стартовали
        xclu_assert(status().was_started,
                    QString("Can't create widget, because module '%1' was not started yet."
                            " You need to place it before parent '%2'.")
                    .arg(module_->name())
                    .arg(parent_id_));

        //создаем виджет
        create_widget();

        //ставим его в объект
        ObjectReadWrite(output).set_pointer("widget_pointer", widget_);


        return;
    }

}

//---------------------------------------------------------------------
void RtModuleWImage::create_widget() {
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
}


//---------------------------------------------------------------------
void RtModuleWImage::update_all(bool force) {
    if (!widget_) {
        return;
    }
    //parent_id - set by call

    //int visible
    if (force || was_changed("visible")) {
        widget_->setVisible(get_int("visible"));
    }

    //итоговое значение
    update_value();


}

//---------------------------------------------------------------------
void RtModuleWImage::update_value() {
    int new_frame = RUNTIME.get_int_by_link(get_string("is_new_frame_link"));
    set_int("is_new_frame",new_frame);

    if (new_frame) {
        XcluObject *object = RUNTIME.get_object_by_link(get_string("image_link"));
        {
            ObjectRead obj(object);
            obj.copy_to(get_object("image"));
        }

        if (image_) {

            //устанавливаем настройки показа
            XcluObjectShowSettings settings;
            settings.w = get_int("w");
            settings.h = get_int("h");

            //создаем wrapper для объекта, который установится в зависимости от его типа,
            //и вызываем функцию для его визуализации
            QScopedPointer<XcluObjectWrapper> wrapper;
           wrapper.reset(XcluObjectWrapper::create_wrapper(object));

           wrapper->show_object(image_, settings);
        }
    }

}


//---------------------------------------------------------------------
void RtModuleWImage::set_image(const QImage &image) {
    if (image_) {
        QPixmap pix = QPixmap::fromImage(image);
        image_->setPixmap(pix);
        //image_->setVisible(true);
    }
}

//---------------------------------------------------------------------
void RtModuleWImage::clear_image() {
    if (image_) {
        image_->setText("");
        image_->setVisible(false);
        //spacer_->spacerItem()-> setVisible(false);
    }
}

//---------------------------------------------------------------------













