#include "qt_widgets.h"
#include "xclu_settings.h"
#include "incl_cpp.h"


//---------------------------------------------------------------------
/*static*/ QString Settings::gets(QString key, QString def) {
    XCLU_SETTINGS
    return settings.value(key, def).toString();
}

//---------------------------------------------------------------------
/*static*/ void Settings::sets(QString key, QString value) {
    XCLU_SETTINGS
    settings.setValue(key, value);
}

//---------------------------------------------------------------------
/*static*/ int Settings::geti(QString key, int def) {
    XCLU_SETTINGS
    return settings.value(key, def).toInt();

}

//---------------------------------------------------------------------
/*static*/ void Settings::seti(QString key, int value) {
    XCLU_SETTINGS
    settings.setValue(key, value);
}


//---------------------------------------------------------------------
/*static*/ void Settings::save_window(QString window_name, QMainWindow *win) {
    XCLU_SETTINGS
    settings.beginGroup(window_name);
    settings.setValue("geometry", win->saveGeometry()); //можно делать для любого QWidget
    settings.setValue("state", win->saveState());
    settings.endGroup();
}

//---------------------------------------------------------------------
void Settings::load_window(QString window_name, QMainWindow *win) {
    XCLU_SETTINGS
    settings.beginGroup(window_name);
    win->restoreGeometry(settings.value("geometry").toByteArray());
    win->restoreState(settings.value("state").toByteArray());

    /*win->resize(settings.value("size", QSize(900, 800)).toSize());
     QPoint p = settings.value("pos", QPoint(-100000, -100000)).toPoint();
     if (p.x() > -100000) {
         win->move(p);
     }*/
    settings.endGroup();
}

//---------------------------------------------------------------------
bool Settings::get_xguicomp_show_components_names() {
     return geti(key_show_components_names());
}

//---------------------------------------------------------------------
int2 Settings::get_xobject_thumb_size() {
    return int2(100, 100);
    //return int2(geti(xobject_thumb_w()),geti(xobject_thumb_h()));
}

//---------------------------------------------------------------------
