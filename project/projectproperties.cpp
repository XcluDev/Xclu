#include "projectproperties.h"
#include "incl_cpp.h"

//---------------------------------------------------------------------
void ProjectProperties::reset_name() {
    name = "";//Untitled";
}

//---------------------------------------------------------------------
void ProjectProperties::write_json(QJsonObject &json) {
    json["name"] = name;
    //json["frame_rate"] = QString::number(frame_rate);
    json["selected_module"] = QString::number(selected_module);

}

//---------------------------------------------------------------------
void ProjectProperties::read_json(const QJsonObject &json) {
    name = json_string(json, "name");
    //frame_rate = json_double(json, "frame_rate");
    selected_module = json_int(json, "selected_module");
}

//---------------------------------------------------------------------
