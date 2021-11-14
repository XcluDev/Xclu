#ifndef PROJECTEDITORPROPERTIES_H
#define PROJECTSAVEDPROPERTIES_H

#include "incl_h.h"

class QJsonObject;

//Project properties, which are saved to project file
class ProjectEditorProperties {
public:
    QString name = "Untitled";
    int selected_module = -1;

    void reset_name();
    void write_json(QJsonObject &json);
    void read_json(const QJsonObject &json);
};

#endif // PROJECTEDITORPROPERTIES_H
