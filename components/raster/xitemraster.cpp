#include "xitemraster.h"

#include "xguiobject.h"
#include "incl_cpp.h"
#include "registrarxitem.h"

/*
REGISTER_XITEM(XItemRaster_<XRaster_u8>,     raster_u8)
REGISTER_XITEM(XItemRaster_<XRaster_u8c3>,   raster_u8c3)
REGISTER_XITEM(XItemRaster_<XRaster_s8>,     raster_s8)
REGISTER_XITEM(XItemRaster_<XRaster_int16>,  raster_int16)
REGISTER_XITEM(XItemRaster_<XRaster_u16>,    raster_u16)
REGISTER_XITEM(XItemRaster_<XRaster_u32>,    raster_u32)
REGISTER_XITEM(XItemRaster_<XRaster_int32>,  raster_int32)
REGISTER_XITEM(XItemRaster_<XRaster_float>,  raster_float)
REGISTER_XITEM(XItemRaster_<XRaster_double>, raster_double)
REGISTER_XITEM(XItemRaster_<XRaster_vec2>,   raster_vec2)
REGISTER_XITEM(XItemRaster_<XRaster_vec3>,   raster_vec3)
REGISTER_XITEM(XItemRaster_<XRaster_int2>,   raster_int2)


//---------------------------------------------------------------------
//in raster_rgb Image image

template<typename TRaster>
XItemRaster_<TRaster>::XItemRaster_(ModuleInterface *interf, const XItemPreDescription &pre_description)
    : XItem(interf, pre_description)
{
    QString line = pre_description.line_to_parse;
    QStringList query;
    split_spaced(line, name_, query);
    //xc_assert(query.size()>=1, "no default value, expected '...q=0...'");

    //опции - типы объектов
    QString options = pre_description.options;

    type

    if (!options.isEmpty()) {
        types_ = options.split(",");
    }

    //создаем объект
    object_.reset(new XObject(XObjectType::Empty));

}

//---------------------------------------------------------------------
//raster access
template<typename TRaster>
bool XItemRaster_<TRaster>::is_empty() {
    return raster_.is_empty();
}

//---------------------------------------------------------------------
//returns nullptr if empty
template<typename TRaster>
XRaster_<TRaster> *XItemRaster_<TRaster>::get_raster() {
    if (is_empty()) return nullptr;
    return raster_.data();
}

//---------------------------------------------------------------------
//raises exception if empty
template<typename TRaster>
XRaster_<TRaster> &XItemRaster_<TRaster>::get_raster_ref() {
    xc_assert(!is_empty(), "XItemRaster_<TRaster>::get_raster_ref error - raster is empty");
    return *raster_.data();
}

//---------------------------------------------------------------------
//графический интерфейс
template<typename TRaster>
XGui *XItemRaster_<TRaster>::create_gui(XGuiPageBuilder &page_builder) {
    gui__ = new XGuiObject(input, this);
    return gui__;
}

//---------------------------------------------------------------------
//получение значения из gui
template<typename TRaster>
void XItemRaster_<TRaster>::gui_to_var_internal() {
    //set_value_int(gui_->value());
}

//---------------------------------------------------------------------
//установка значения в gui
template<typename TRaster>
void XItemRaster_<TRaster>::var_to_gui_internal() {
    //показать объект визуально
    //если изображение - то картинкой, если нет - то текстовым описанием
    //мы это делаем только по команде извне - так как не знаем,
    //вдруг с объектом проводятся операции
    //при необходимости - можно ввести mutex в объект

    gui_->show_object(get_object());
}

//---------------------------------------------------------------------
//копирование данных - для duplicate; предполагается, что имя и тип - одинаковые
//специальные типы, которые не поддерживают перенос через строку (array и image) - должны переписать copy_data_to_internal
template<typename TRaster>
void XItemRaster_<TRaster>::copy_data_to_internal(XItem *item) {
    xc_assert(item->supports_object(), "Can't copy object data, because destination item doesn't support object");
    XObjectRead(get_object()).copy_to(item->get_object());
}

//---------------------------------------------------------------------
//C++
//original: XObject *get_object(QString name);
template<typename TRaster>
void XItemRaster_<TRaster>::export_interface(QStringList &file) {
    export_interface_template(file, false, true, "Object ", true,
                              "XObject *", "struct", "get_struct", "");
}
*/
//---------------------------------------------------------------------


