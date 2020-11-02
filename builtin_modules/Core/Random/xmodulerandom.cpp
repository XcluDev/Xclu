#include "xmodulerandom.h"
#include "incl_cpp.h"
#include "registrarxmodule.h"
#include "xcore.h"


//registering module implementation
REGISTER_XMODULE(Random)

//---------------------------------------------------------------------
XModuleRandom::XModuleRandom(QString class_name)
    :XModule(class_name)
{

}

//---------------------------------------------------------------------
XModuleRandom::~XModuleRandom()
{

}

//---------------------------------------------------------------------
void XModuleRandom::impl_start() {
    sets_result("");
}

//---------------------------------------------------------------------
void XModuleRandom::impl_update() {
    QString value;

    auto type = gete_output_type();
    switch (type) {
    case output_type_Float:
        value = QString::number(randomf(getf_from_float(), getf_to_excluded_float()));
        break;
    case output_type_Int:
        value = QString::number(randomi(geti_from_int(), geti_to_int()));
        break;
    case output_type_String:
        value = get_random_string();
        break;
    default:
        xclu_exception("XModuleRandom::impl_update - bad `output_type` value");
    }

   sets_result(value);

}

//---------------------------------------------------------------------
QString XModuleRandom::get_random_string() {
    //collect list of non-empty and non-commented items
    QStringList list;
    QStringList values = get_strings_values();
    for (auto &line: values) {
        if (line.isEmpty() || line.startsWith("#")) continue;
        list.append(line);
    }
    if (list.isEmpty()) return "";
    int i = randomi(0, list.size()-1);
    return list.at(i);
}

//---------------------------------------------------------------------
void XModuleRandom::impl_stop() {

}

//---------------------------------------------------------------------
//void XModuleTimerm::impl_button_pressed(QString button_id) {
//}

//---------------------------------------------------------------------
