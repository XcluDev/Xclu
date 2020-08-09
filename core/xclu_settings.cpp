#include "xclu_settings.h"
#include "incl_qtcpp.h"

//---------------------------------------------------------------------
/*static*/ QString Settings::get_string(QString key, QString def) {
    XCLU_SETTINGS
    return settings.value(key, def).toString();
}

//---------------------------------------------------------------------
/*static*/ void Settings::set_string(QString key, QString value) {
    XCLU_SETTINGS
    settings.setValue(key, value);
}

//---------------------------------------------------------------------
/*static*/ int Settings::get_int(QString key, int def) {
    XCLU_SETTINGS
    return settings.value(key, def).toInt();

}

//---------------------------------------------------------------------
/*static*/ void Settings::set_int(QString key, int value) {
    XCLU_SETTINGS
    settings.setValue(key, value);
}


//---------------------------------------------------------------------

