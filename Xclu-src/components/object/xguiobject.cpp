#include "qt_widgets.h"
#include "incl_cpp.h"
#include "xitemobject.h"
#include "xguiobject.h"
#include "xobjectvis.h"

//---------------------------------------------------------------------
//XGuiObjectVisual
//---------------------------------------------------------------------
XGuiObjectVisual::XGuiObjectVisual() {
    thumb_size_ = Settings::get_xobject_thumb_size();

    resize_image(thumb_size_.x, thumb_size_.y);
}

//---------------------------------------------------------------------
void XGuiObjectVisual::set_text(QString text) {
    description_->setText(text);

}

//---------------------------------------------------------------------
void XGuiObjectVisual::set_thumbnail_size(int w, int h)
{
    thumb_size_ = int2(w, h);
    resize_image(w, h);
    update_thumbnail();
}

//---------------------------------------------------------------------
void XGuiObjectVisual::resize_image(int w, int h) {
    image_ = QImage(w, h, QImage::Format_ARGB32);
    clear_image();
}

//---------------------------------------------------------------------
void XGuiObjectVisual::clear_image() {
    image_.fill(Qt::gray);
}

//---------------------------------------------------------------------
int2 XGuiObjectVisual::thumbnail_size() {
    return thumb_size_;
}

//---------------------------------------------------------------------
void XGuiObjectVisual::clear_thumbnail() {
    clear_image();
    update_thumbnail();
    //thumbnail_->setText("");
    //thumbnail_->setVisible(false);
}

//---------------------------------------------------------------------
void XGuiObjectVisual::update_thumbnail() {
    QPixmap pix = QPixmap::fromImage(image_);
    thumbnail_->setPixmap(pix);
}

//---------------------------------------------------------------------
void XGuiObjectVisual::show_thumbnail() {
    thumbnail_->setVisible(true);
}

//---------------------------------------------------------------------
void XGuiObjectVisual::hide_thumbnail() {
    thumbnail_->setVisible(false);
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
    :XGuiComp(page_builder, item)
{
    visual_.thumbnail_ = new QLabel("");
    visual_.description_ = new QLabel("");
    //visual_.spacer_ = new QSpacerItem(5,1);
    visual_.clear_thumbnail();

    //insert to page
    insert_widgets(page_builder,
                   visual_.description_,
                   new_label(), 3, false,
                   nullptr, 1, false,
                   new_label_link(), 1, true,
                   visual_.thumbnail_, 3, false,
                   visual_.description_, 2, true
                   );

    //TODO ДОБАВЛЕНИЕ КНОПКИ Details для показа детальной информации в отдельном окне

    //квалификаторы
    if (item->is_out()) {
        set_read_only(true);
    }

    //track changes
    //connect(checkbox_, SIGNAL (stateChanged(int)), this, SLOT (on_value_changed()));*/
    reset_last_object();

    visual_.hide_thumbnail();
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
void XGuiObject::reset_last_object() {
    last_object_ = nullptr;
    was_changed_checker_.reset();
    visual_.clear_thumbnail();
    visual_.set_text("No object");
}

//---------------------------------------------------------------------
//показать объект визуально
//если изображение - то картинкой, если нет - то текстовым описанием
//мы это делаем только по команде извне - так как не знаем,
//вдруг с объектом проводятся операции
void XGuiObject::show_object(XProtectedObject* object) {
    // Проверка, что объект действительно есть
    if (!object) {
        reset_last_object();
        return;
    }

    const XObject *obj = object->read().pointer();
    if (!obj) {
        reset_last_object();
        return;
    }

    // Проверка, было ли изменение объекта
    bool was_changed = false;
    if (last_object_ != obj) {
        was_changed = true;
        last_object_ = obj;
        was_changed_checker_.reset();
    }
    else {
        was_changed = object->was_changed(was_changed_checker_);
    }

    if (!was_changed) {
        return;
    }

    // Создаем wrapper для объекта, который установится в зависимости от его типа,
    //и вызываем функцию для его визуализации
    QScopedPointer<XObjectVis> vis(XObjectVis::new_vis(obj));
    visual().set_text(vis->short_description().join("\n"));

    if (vis->is_thumbnail_exists())
    {
        QPainter painter(&visual().image_);
        int2 size = visual().thumbnail_size();
        vis->draw_thumbnail(painter, size.x, size.y);
        visual().update_thumbnail();
        visual().show_thumbnail();
    }
    else {
        visual_.hide_thumbnail();
    }

}

//---------------------------------------------------------------------
