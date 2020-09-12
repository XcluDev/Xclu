#include "xitemenum.h"
#include "incl_cpp.h"
#include "xguienum.h"

//---------------------------------------------------------------------
//in enum List list=OFF [OFF,ON]
//      //Length of the object.    описание
//      //mm                       опционально - единица измерения, показывается справа

XItemEnum::XItemEnum(ModuleInterface *parent, const XItemPreDescription &pre_description)
    : XItem(parent, pre_description)
{
    QString line = pre_description.line_to_parse;
    QStringList query;
    split_equal(line, name_, query);
    xclu_assert(query.size()>=1, "no default value, expected '...q=A...'");

    //значение по умолчанию, ниже его конвертируем в index
    QString default_value = query.at(0);

    //список значений
    xclu_assert(query.size()>=2, "no list of values, expected '...[a,b,c]'");
    QString list = query.at(1);
    xclu_assert(list.startsWith("[") && list.endsWith("]"), "list of values must start with '[' and end with ']', '...[a,b,c]'");
    //удаляем [ и ]
    list = list.mid(1);
    list.chop(1);

    rawtexts_ = list.split(",");
    xclu_assert(!rawtexts_.empty(), "empty list of values, expected '...[a,b,c]'");

    //заполнение map и проверка уникальности
    map_index_.clear();
    for (int i=0; i<rawtexts_.size(); i++) {
        QString item = rawtexts_.at(i);
        xclu_assert(!map_index_.contains(item), "duplicated entry " + item);
        map_index_[item] = i;
    }

    //установка индексов по умолчанию
    default_index_ = rawtext_to_index_safe(default_value);
    index_ = default_index_;

    //Единицы измерения - вторая строка описания после hint
    units_ = description(1);
}

//---------------------------------------------------------------------
int XItemEnum::rawtext_to_index(QString rawtext) {
    if (map_index_.contains(rawtext)) {
        return map_index_[rawtext];
    }
    return -1;
}

//---------------------------------------------------------------------
int XItemEnum::rawtext_to_index_safe(QString rawtext) {
    int index = rawtext_to_index(rawtext);
    if (index == -1) return 0;
    return index;
}

//---------------------------------------------------------------------
void XItemEnum::set_value_string(const QString &rawstring){
    index_ = rawtext_to_index_safe(rawstring);
}

//---------------------------------------------------------------------
QString XItemEnum::value_string() {
    return rawtexts_.at(index_);
}

//---------------------------------------------------------------------
QString XItemEnum::value_title() {
    return xclu_remove_underscore(value_string());
}

//---------------------------------------------------------------------
//Внимание, реализована неэффективно!
void XItemEnum::set_value_title(QString title) {
    QStringList T = titles();       //все заголовки
    for (int i=0; i<T.size(); i++) {
        if (T[i] == title) {
            set_value_int(i);
            return;
        }
    }
    //TODO: в случае ошибки просто ничего не делает, возможно стоит сделать выдачу предупреждения
}

//---------------------------------------------------------------------
QStringList XItemEnum::titles() {       //все заголовки
    QStringList list;
    int n = rawtexts_.size();
    list.reserve(n);
    for (int i=0; i<n; i++) {
        list.push_back(xclu_remove_underscore(rawtexts_.at(i)));
    }
    return list;
}

//---------------------------------------------------------------------
QStringList XItemEnum::names() {       //все заголовки с подчеркиванием - для программирования
    return rawtexts_;
}

//---------------------------------------------------------------------
//графический интерфейс
XGui *XItemEnum::create_gui(XGuiPageCreator &input) {
    gui__ = gui_ = new XGuiEnum(input, this);
    return gui_;
}

//---------------------------------------------------------------------
//получение значения из gui
void XItemEnum::gui_to_var_internal() {
    set_value_int(gui_->index());
}

//---------------------------------------------------------------------
//установка значения в gui
void XItemEnum::var_to_gui_internal() {
    gui_->set_index(value_int());
}

//---------------------------------------------------------------------
//C++
/*
//Type of content we are searching for
enum enum_filter {
    filter_All = 0,
    filter_Files = 1,
    filter_Folders = 2,
    filter_N__ = 3
};
enum_filter en_filter() {...}
*/

void XItemEnum::export_interface(QStringList &file) {
    export_interface_template(file, false, true, "Enum ", false, "", "", "", "", false);
    QString nam = name();
    QString cpp_type = "enum_" + nam;
    int n = rawtexts_.size();
    file.append(QString("enum %1 {").arg(cpp_type));
    for (int i=0; i<n; i++) {
        file.append(QString("    %1_%2 = %3,").arg(nam).arg(rawtexts_.at(i)).arg(i));
    }
    file.append(QString("    %1_%2 = %3").arg(nam).arg("N__").arg(n));
    file.append("};");

    file.append(QString("%2 en_%1() { return %2(geti(\"%1\")); }").arg(nam).arg(cpp_type));
    if (qualifier() == VarQualifierOut) {
        file.append(QString("void en_%1(%2 value) { seti(\"%1\", value); }").arg(name()).arg(cpp_type));
    }
    file.append("");

}

//---------------------------------------------------------------------
