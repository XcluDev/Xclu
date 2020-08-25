#include "interfaceitemobject.h"
#include "interfaceguiobject.h"
#include "incl_qtcpp.h"

//---------------------------------------------------------------------
/*
in object Object_To_Save obj_to_save
    //Object for saving
object(image) - дает намек, что ожидается тип изображения.
object(image,array) - что ожидаются изображения и массивы.
И тогда при выборе объекта это учитывается и показываются только они.
object(strings) - массив строк (?) - его можно ставить в text
*/


InterfaceItemObject::InterfaceItemObject(ModuleInterface *parent, const InterfaceItemPreDescription &pre_description)
    : InterfaceItem(parent, pre_description)
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
    object_.reset(new XcluObject(XcluObjectTypeEmpty));

}

//---------------------------------------------------------------------
//графический интерфейс
InterfaceGui *InterfaceItemObject::create_gui(InterfaceGuiPageCreator &input) {
    gui__ = gui_ = new InterfaceGuiObject(input, this);
    return gui_;
}

//---------------------------------------------------------------------
//получение значения из gui
void InterfaceItemObject::gui_to_var_internal() {
    //set_value_int(gui_->value());
}

//---------------------------------------------------------------------
//установка значения в gui
void InterfaceItemObject::var_to_gui_internal() {
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
void InterfaceItemObject::copy_data_to_internal(InterfaceItem *item) {
    xclu_assert(item->supports_object(), "Can't copy object data, because destination item doesn't support object");
    ObjectRead(get_object()).copy_to(item->get_object());
}

//---------------------------------------------------------------------


