#ifndef INCL_QT_H
#define INCL_QT_H

//Файлы для подключения с Qt

#include <QVector>
#include <QMap>
#include <QSet>
#include <QString>
#include <QStringList>
#include <functional>
#include <QMutex>
#include <QReadWriteLock>
#include <QScopedPointer>

//Stl - currently commented
//#include <vector>
//#include <string>
//#include <algorithm>
//using namespace std;


//types, utils
#include "types.h"
#include "math_utils.h"
#include "xtypes.h"

//geometry
#include <glm/glm.hpp>

//vector norm glm::length, glm::length2
#include <glm/gtx/norm.hpp>

//rotation matrix mat4 glm::eulerAngleYXZ(float yaw, float pitch, float roll);
//   and mat3x3 glm::orientate3(vec3 const &angles); - here yaw -> z, pitch -> y, roll -> x
#include <glm/gtx/euler_angles.hpp>

//int-vectors
#include "int2.h"

#include "xclu_types.h"

#endif // INCL_QT_H
