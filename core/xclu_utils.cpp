#include "xclu_utils.h"
#include <QtGlobal>

//---------------------------------------------------------------------
float xclu_clamp(float x, float a, float b) {
    if (a>b) qSwap(a,b);
    return qMin(qMax(x,a),b);
}

//---------------------------------------------------------------------
float xclu_map(float x, float a, float b, float A, float B) {
    return (x-a)/(b-a)*(B-A) + A;
}

//---------------------------------------------------------------------
float xclu_map_clamped(float x, float a, float b, float A, float B) {
    return xclu_clamp(xclu_map(x,a,b,A,B),A,B);
}

//---------------------------------------------------------------------
//замена подчеркивания на пробел в заголовках: Abc_Def -> "Abc Def"
QString xclu_remove_underscore(QString title) {
    return title.replace('_', ' ');
}

//---------------------------------------------------------------------
