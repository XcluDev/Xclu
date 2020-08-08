#include <QtWidgets>
#include "incl_qtcpp.h"
#include "interfaceitemobject.h"
#include "interfaceguiobject.h"
#include "xcluobjectimage.h"
#include "xcluobjectwrapper.h"


//---------------------------------------------------------------------
void InterfaceGuiObjectVisual::set_text(QString text) {
    info_label_->setText(text);

}

//---------------------------------------------------------------------
void InterfaceGuiObjectVisual::set_image(const QImage &image) {
    QPixmap pix = QPixmap::fromImage(image);
    preview_label_->setPixmap(pix);
    preview_label_->setVisible(true);
}

//---------------------------------------------------------------------
void InterfaceGuiObjectVisual::clear_image() {
    preview_label_->setText("");
    preview_label_->setVisible(false);
    //spacer_->spacerItem()-> setVisible(false);
}

//---------------------------------------------------------------------
//---------------------------------------------------------------------
//---------------------------------------------------------------------
InterfaceGuiObject::InterfaceGuiObject(InterfaceGuiPageCreator &input, InterfaceItemObject *item)
    :InterfaceGui(input, item)
{
    visual_.preview_label_ = new QLabel("");
    visual_.info_label_ = new QLabel("");
    visual_.spacer_ = new QSpacerItem(5,1);
    visual_.clear_image();

    object_widget_ = new QWidget;
    QHBoxLayout *layout = new QHBoxLayout;
    object_widget_->setLayout(layout);
    layout->setMargin(0);

    layout->addWidget(visual_.preview_label_);
    layout->addItem(visual_.spacer_);
    layout->addWidget(visual_.info_label_);
    //layout->setStretch(0,0);
    //layout->setStretch(1,1);

    //метка
    insert_label(input);
    //вставка на страницу
    insert_widget_with_spacer_next_line(object_widget_, object_widget_, input);

    //ДОБАВЛЕНИЕ КНОПКИ Inspect

    //квалификаторы
    if (item->is_out()) {
        set_read_only(true);
    }


    //отслеживание изменений
    //connect(checkbox_, SIGNAL (stateChanged(int)), this, SLOT (on_value_changed()));*/
}

//---------------------------------------------------------------------
InterfaceGuiObject::~InterfaceGuiObject() {

}

//---------------------------------------------------------------------
//установка режима read_only - для out и блокировки констант при запуске проекта
void InterfaceGuiObject::set_read_only(bool read_only) {
    InterfaceGui::set_read_only(read_only);



}

//---------------------------------------------------------------------
//доступ к меткам и другим компонентам для визуализации
InterfaceGuiObjectVisual &InterfaceGuiObject::visual() {
    return visual_;
}

//---------------------------------------------------------------------
//показать объект визуально
//если изображение - то картинкой, если нет - то текстовым описанием
//мы это делаем только по команде извне - так как не знаем,
//вдруг с объектом проводятся операции
//при необходимости - можно ввести mutex в объект
void InterfaceGuiObject::show_object(XcluObject *object) {
    if (object) {
        //создаем wrapper для объекта, который установится в зависимости от его типа,
        //и вызываем функцию для его визуализации
        QScopedPointer<XcluObjectWrapper> wrapper;
        wrapper.reset(XcluObjectWrapper::create_wrapper(object));
        wrapper->show_object(this);
    }
}

//---------------------------------------------------------------------
