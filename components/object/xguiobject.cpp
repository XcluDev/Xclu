#include "qt_widgets.h"
#include "incl_cpp.h"
#include "xitemobject.h"
#include "xguiobject.h"
#include "xobjectimage.h"
#include "xobjectwrapper.h"

//---------------------------------------------------------------------
//XGuiObjectVisual
//---------------------------------------------------------------------
void XGuiObjectVisual::set_text(QString text) {
    description_->setText(text);

}

//---------------------------------------------------------------------
void XGuiObjectVisual::set_image(const QImage &image) {
    QPixmap pix = QPixmap::fromImage(image);
    thumbnail_->setPixmap(pix);
    thumbnail_->setVisible(true);
}

//---------------------------------------------------------------------
void XGuiObjectVisual::clear_image() {
    thumbnail_->setText("");
    thumbnail_->setVisible(false);
    //spacer_->spacerItem()-> setVisible(false);
}

//---------------------------------------------------------------------
//XGuiObject
//---------------------------------------------------------------------
/*
Widget structures for different controls:

float, int:     0 label, 1 control,  2 measure unit, 3 slider,     4 link label
checkbox:       0 label, 1 control                                 4 link label
checkbox_group: 0--------1 control,  2---------------3 horiz.line  4 link label
separator:      0 "control"
button:                  1 control                                 4 link label
string, text:   0 label                                            4 link label
                0 -------------------------------------------------4 control
object:         0 label                                            4 link label
                0--------------------2 thumbnail     3-------------4 description
*/

//---------------------------------------------------------------------
XGuiObject::XGuiObject(XGuiPageBuilder &page_builder, XItemObject *item)
    :XGui(page_builder, item)
{
    visual_.thumbnail_ = new QLabel("");
    visual_.description_ = new QLabel("");
    //visual_.spacer_ = new QSpacerItem(5,1);
    visual_.clear_image();

    //insert to page
    insert_widgets(page_builder,
                   visual_.description_,
                   new_label(), 3, false,
                   nullptr, 1, false,
                   new_label_link(), 1, true,
                   visual_.thumbnail_, 3, false,
                   visual_.description_, 2, true
                   );

    //TODO ДОБАВЛЕНИЕ КНОПКИ Inspect

    //квалификаторы
    if (item->is_out()) {
        set_read_only(true);
    }

    //track changes
    //connect(checkbox_, SIGNAL (stateChanged(int)), this, SLOT (on_value_changed()));*/
}

//---------------------------------------------------------------------
XGuiObject::~XGuiObject() {

}

//---------------------------------------------------------------------
//установка режима read_only - для out и блокировки констант при запуске проекта
void XGuiObject::set_read_only_(bool /*read_only*/) {
    //xclu::widget_update_css(spin_);
}

//---------------------------------------------------------------------
//доступ к меткам и другим компонентам для визуализации
XGuiObjectVisual &XGuiObject::visual() {
    return visual_;
}

//---------------------------------------------------------------------
//показать объект визуально
//если изображение - то картинкой, если нет - то текстовым описанием
//мы это делаем только по команде извне - так как не знаем,
//вдруг с объектом проводятся операции
void XGuiObject::show_object(XProtectedObject *object) {
    if (object) {
        //создаем wrapper для объекта, который установится в зависимости от его типа,
        //и вызываем функцию для его визуализации
        QScopedPointer<XObjectWrapper> wrapper;
        const XObject *obj = object->read().pointer();
        wrapper.reset(XObjectWrapper::create_wrapper(obj));
        wrapper->show_object(this);
    }
}

//---------------------------------------------------------------------
