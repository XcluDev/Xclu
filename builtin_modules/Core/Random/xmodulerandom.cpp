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
void XModuleRandom::start() {
    time_ = -1; //implies renew value on first update with Period mode

    sets_result("");
}

//---------------------------------------------------------------------
void XModuleRandom::update() {
    switch (gete_update_mode()) {
    case update_mode_Each_Update: make_new_value();
        break;
    case update_mode_Period: {
        float time = xc_elapsed_time_sec();
        if (time_ < 0 || time >= time_ + getf_period_sec()) {
            time_ = time;
            make_new_value();
        }
    }
        break;
    default: xc_exception("XModuleRandom::update - bad `update_mode` value");
    }
}

//---------------------------------------------------------------------
void XModuleRandom::make_new_value() {
    QString value;

    auto type = gete_output_type();
    switch (type) {
    case output_type_Float:
        value = QString::number(xrandomf(getf_from_float(), getf_to_excluded_float()));
        break;
    case output_type_Int:
        value = QString::number(xrandomi(geti_from_int(), geti_to_int()));
        break;
    case output_type_String:
        value = get_random_string();
        break;
    default:
        xc_exception("XModuleRandom::update - bad `output_type` value");
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
    int i = xrandomi(0, list.size()-1);
    return list.at(i);
}

//---------------------------------------------------------------------
void XModuleRandom::stop() {

}

//---------------------------------------------------------------------
//void XModuleTimerm::on_button_pressed(QString button_id) {
//}

//---------------------------------------------------------------------
