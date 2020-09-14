#ifndef INCL_QT_H
#define INCL_QT_H

//Файлы для подключения с Qt

#include <QVector>
#include <QMap>
#include <QSet>
#include <QString>
#include <QStringList>
#include <functional>
#include <QScopedPointer>

//Stl - currently commented
//#include <vector>
//#include <string>
//#include <algorithm>
//using namespace std;


//types, utils
#include "math_types.h"
#include "math_utils.h"
#include "raster.h"

//geometry
#include <glm/glm.hpp>

//vector norm glm::length, glm::length2
#include <glm/gtx/norm.hpp>

//rotation matrix mat4 glm::eulerAngleYXZ(float yaw, float pitch, float roll);
//   and mat3x3 glm::orientate3(vec3 const &angles); - here yaw -> z, pitch -> y, roll -> x
#include <glm/gtx/euler_angles.hpp>

//int-vectors
#include "int2.h"

//#include "incl_std.h"
#include "xclu_types.h"
#include "xclu_theme.h"
#include "xclu_utils.h"
#include "xclu_paths.h"
#include "xclass.h"

#endif // INCL_QT_H
