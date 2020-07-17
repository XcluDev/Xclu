#ifndef XCLU_UTILS_H
#define XCLU_UTILS_H

#include <QString>

//вспомогательные функции
float xclu_clamp(float x, float a, float b);
float xclu_map(float x, float a, float b, float A, float B);
float xclu_map_clamped(float x, float a, float b, float A, float B);

//замена подчеркивания на пробел в заголовках: Abc_Def -> "Abc Def"
QString xclu_remove_underscore(QString title);

#endif // XCLU_UTILS_H
