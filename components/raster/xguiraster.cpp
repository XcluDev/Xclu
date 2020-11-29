
#include "qt_widgets.h"
#include "incl_cpp.h"
#include "xitemraster.h"
#include "xguiraster.h"

/*
//---------------------------------------------------------------------
void XGuiRasterVisual::set_text(QString text) {
    description_->setText(text);

}

//---------------------------------------------------------------------
void XGuiRasterVisual::set_image(const QImage &image) {
    QPixmap pix = QPixmap::fromImage(image);
    thumbnail_->setPixmap(pix);
    thumbnail_->setVisible(true);
}

//---------------------------------------------------------------------
void XGuiRasterVisual::clear_image() {
    thumbnail_->setText("");
    thumbnail_->setVisible(false);
    //spacer_->spacerItem()-> setVisible(false);
}

//---------------------------------------------------------------------
//---------------------------------------------------------------------
//---------------------------------------------------------------------
template<typename T>
XGuiRaster_<T>::XGuiRaster_(XGuiPageBuilder &page_builder, XItemRaster_<T> *item)
    :XGui(input, item)
{
    visual_.thumbnail_ = new QLabel("");
    visual_.description_ = new QLabel("");
    visual_.spacer_ = new QSpacerItem(5,1);
    visual_.clear_image();

    object_widget_ = new QWidget;
    QHBoxLayout *layout = new QHBoxLayout;
    object_widget_->setLayout(layout);
    layout->setMargin(0);

    layout->addWidget(visual_.thumbnail_);
    layout->addItem(visual_.spacer_);
    layout->addWidget(visual_.description_);
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


    //track changes
    //connect(checkbox_, SIGNAL (stateChanged(int)), this, SLOT (on_value_changed()));
}

//---------------------------------------------------------------------
template<typename T>
XGuiRaster_<T>::~XGuiRaster_() {

}

//---------------------------------------------------------------------
//установка режима read_only - для out и блокировки констант при запуске проекта
template<typename T>
void XGuiRaster_<T>::set_read_only_(bool read_only) {
    //xclu::widget_update_css(spin_);
}

//---------------------------------------------------------------------
//доступ к меткам и другим компонентам для визуализации
template<typename T>
XGuiRaster_<T>Visual &XGuiRaster_<T>::visual() {
    return visual_;
}

//---------------------------------------------------------------------
//показать объект визуально
//если изображение - то картинкой, если нет - то текстовым описанием
//мы это делаем только по команде извне - так как не знаем,
//вдруг с объектом проводятся операции
//при необходимости - можно ввести mutex в объект
template<typename T>
void XGuiRaster_<T>::show_object(XObject *object) {
    if (object) {
        //создаем wrapper для объекта, который установится в зависимости от его типа,
        //и вызываем функцию для его визуализации
        QScopedPointer<XObjectWrapper> wrapper;
        wrapper.reset(XObjectWrapper::create_wrapper(object));
        wrapper->show_object(this);
    }
}
*/
//---------------------------------------------------------------------
