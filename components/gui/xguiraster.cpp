
#include "qt_widgets.h"
#include "incl_cpp.h"
#include "xitemraster.h"
#include "xguiraster.h"

//---------------------------------------------------------------------
void XGuiRasterVisual::set_text(QString text) {
    info_label_->setText(text);

}

//---------------------------------------------------------------------
void XGuiRasterVisual::set_image(const QImage &image) {
    QPixmap pix = QPixmap::fromImage(image);
    preview_label_->setPixmap(pix);
    preview_label_->setVisible(true);
}

//---------------------------------------------------------------------
void XGuiRasterVisual::clear_image() {
    preview_label_->setText("");
    preview_label_->setVisible(false);
    //spacer_->spacerItem()-> setVisible(false);
}

//---------------------------------------------------------------------
//---------------------------------------------------------------------
//---------------------------------------------------------------------
template<typename T>
XGuiRaster_<T>::XGuiRaster_(XGuiPageCreator &input, XItemRaster_<T> *item)
    :XGui(input, item)
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
template<typename T>
XGuiRaster_<T>::~XGuiRaster_() {

}

//---------------------------------------------------------------------
//установка режима read_only - для out и блокировки констант при запуске проекта
template<typename T>
void XGuiRaster_<T>::set_read_only(bool read_only) {
    XGui::set_read_only(read_only);



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
void XGuiRaster_<T>::show_object(XStruct *object) {
    if (object) {
        //создаем wrapper для объекта, который установится в зависимости от его типа,
        //и вызываем функцию для его визуализации
        QScopedPointer<XStructWrapper> wrapper;
        wrapper.reset(XStructWrapper::create_wrapper(object));
        wrapper->show_object(this);
    }
}

//---------------------------------------------------------------------
