#pragma once
// Класс XGeomMesh сделан на основе класса ofMesh из openFrameworks

#include "xmath.h"
#include <QVector>

class XGeomMesh {
public:
    QVector<vec3> vertices;
    QVector<vec3> normals;
    QVector<vec2> tex_coords;
    QVector<int> indices;

    XGeomMesh();
    void clear();
};

