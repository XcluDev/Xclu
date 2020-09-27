#include "xitemobject.h"
#include "xguiobject.h"
#include "incl_cpp.h"
#include "registrarxitem.h"

REGISTER_XITEM(Object, object)
//---------------------------------------------------------------------
/*
in object Object_To_Save obj_to_save
    //Object for saving
object_image - дает намек, что ожидается тип изображения.
object(image,array) - что ожидаются изображения и массивы.
И тогда при выборе объекта это учитывается и показываются только они.
object(strings) - массив строк (?) - его можно ставить в text
*/


XItemObject::XItemObject(ModuleInterface *interf, const XItemPreDescription &pre_description)
    : XItem(interf, pre_description)
{
    QString line = pre_description.line_to_parse;
    QStringList query;
    split_spaced(line, name_, query);
    //xclu_assert(query.size()>=1, "no default value, expected '...q=0...'");

    //опции - типы объектов
    QString options = pre_description.options;
    if (!options.isEmpty()) {
        types_ = options.split(",");
    }

    //создаем объект
    object_.reset(new XStruct(XStructTypeEmpty));

}

//---------------------------------------------------------------------
//графический интерфейс
XGui *XItemObject::create_gui(XGuiPageCreator &input) {
    gui__ = gui_ = new XGuiObject(input, this);
    return gui_;
}

//---------------------------------------------------------------------
//получение значения из gui
void XItemObject::gui_to_var_internal() {
    //set_value_int(gui_->value());
}

//---------------------------------------------------------------------
//установка значения в gui
void XItemObject::var_to_gui_internal() {
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
void XItemObject::copy_data_to_internal(XItem *item) {
    xclu_assert(item->supports_object(), "Can't copy object data, because destination item doesn't support object");
    XStructRead(get_object()).copy_to(item->get_object());
}

//---------------------------------------------------------------------
//C++
//original: XStruct *get_object(QString name);
void XItemObject::export_interface(QStringList &file) {
    export_interface_template(file, false, true, "Object ", true,
                              "XStruct *", "struct", "get_struct", "");
}

//---------------------------------------------------------------------


