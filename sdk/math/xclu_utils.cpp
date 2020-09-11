#include "xclu_utils.h"
#include <QtGlobal>

//---------------------------------------------------------------------
//замена подчеркивания на пробел в заголовках: Abc_Def -> "Abc Def"
QString xclu_remove_underscore(QString title) {
    return title.replace('_', ' ');
}

//---------------------------------------------------------------------
