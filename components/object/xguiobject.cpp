#include "qt_widgets.h"
#include "incl_cpp.h"
#include "xitemobject.h"
#include "xguiobject.h"
#include "xobjectimage.h"

//---------------------------------------------------------------------
//XGuiObjectVisual
//---------------------------------------------------------------------
void XGuiObjectVisual::set_text(QString text) {
    description_->setText(text);

}

//---------------------------------------------------------------------
/*void XGuiObjectVisual::set_image(const QImage &image) {
    QPixmap pix = QPixmap::fromImage(image);
    thumbnail_->setPixmap(pix);
    thumbnail_->setVisible(true);
}*/

//---------------------------------------------------------------------
void XGuiObjectVisual::set_thumbnail_size(int w, int h)
{
    xc_exception("GuiObjectVisual::set_thumbnail_size not implemented");
}

//---------------------------------------------------------------------
QPainter* XGuiObjectVisual::thumbnail_painter() {
    xc_exception("GuiObjectVisual::painter not implemented");
    return nullptr;
}

//---------------------------------------------------------------------
int2 XGuiObjectVisual::thumbnail_size() {
    xc_exception("GuiObjectVisual::painter_size not implemented");
    return int2(0,0);
}

/*
    auto &visual = item->visual();

    //описание изображения
    const XObject &obj_1 = *object();
    auto d = XObjectImage::get_data(obj_1);
    QString info_text = QString("%1\n%2 byte(s)").arg(object_type_to_string(obj_1.type())).arg(obj_1.size_bytes());


    info_text += QString("\n%1x%2, %3, %4").arg(d.w).arg(d.h).arg(d.channels_description).arg(d.data_type);
    visual.set_text(info_text);

    //TODO получение параметров просмотра из item
    XObjectShowSettings settings;
    settings.w = xclu::image_preview_small_w;
    settings.h = xclu::image_preview_small_h;

    //создаем preview для изображения
    int w = d.w;
    int h = d.h;
    if (w > 0 && h > 0) {
        float scl = qMin(float(settings.w) / w, float(settings.h) / h);
        w = w * scl;
        h = h * scl;

        QImage img;
        {
            const XObject &obj = *object();
            XObjectImage::convert_to_QImage_fast_preview(obj, img, w, h);
        }

        visual.set_image(img);
    }
    else {
        //если нет картинки, то очищаем
        visual.clear_image();
    }

    */
//---------------------------------------------------------------------
void XGuiObjectVisual::clear_thumbnail() {
    xc_exception("GuiObjectVisual::clear_thumbnail not implemented");
    //thumbnail_->setText("");
    //thumbnail_->setVisible(false);
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
void XGuiObject::show_object(XProtectedObject* object) {
    if (object) {
        //создаем wrapper для объекта, который установится в зависимости от его типа,
        //и вызываем функцию для его визуализации
        const XObject *obj = object->read().pointer();
        if (obj->thumbnail_exists())
        {
            auto *painter = visual().thumbnail_painter();
            if (painter) {
                int2 size = visual().thumbnail_size();
                obj->draw_thumbnail(*painter, size.x, size.y);
            }
        }
        visual().set_text(obj->short_description().join("\n"));
    }
}

//---------------------------------------------------------------------
