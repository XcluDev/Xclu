#include "projecteditorprops.h"
#include "incl_cpp.h"

//---------------------------------------------------------------------
void ProjectEditorProperties::reset_name() {
    name = "";//Untitled";
}

//---------------------------------------------------------------------
void ProjectEditorProperties::write_json(QJsonObject &json) {
    json["name"] = name;
    //json["frame_rate"] = QString::number(frame_rate);
    json["selected_module"] = QString::number(selected_module);

}

//---------------------------------------------------------------------
void ProjectEditorProperties::read_json(const QJsonObject &json) {
    name = JsonUtils::json_string(json, "name");
    //frame_rate = json_double(json, "frame_rate");
    selected_module = JsonUtils::json_int(json, "selected_module");
}

//---------------------------------------------------------------------
