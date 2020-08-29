#ifndef PROJECTPROPERTIES_H
#define PROJECTPROPERTIES_H

#include "incl_h.h"

class QJsonObject;

//Свойства проекта
class ProjectProperties {
public:
    QString name = "Untitled";
    //float frame_rate = 30;    //это настраивается в модуле Project
    int selected_module = -1;

    void reset_name();
    void write_json(QJsonObject &json);
    void read_json(const QJsonObject &json);
};

#endif // PROJECTPROPERTIES_H
