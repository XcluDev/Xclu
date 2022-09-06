#pragma once

// Сделано на основе ofxKu/ofxKuGeomExportFGA

// Export FGA file format for QVector fields in Unreal Engine.

#include <QVector>
#include <QString>
#include "xmath.h"


// Export QVector field QVector_field of size nx * ny * nz, into FGA file file_name,
// using boundaries [lower_bound, upper_bound]
// float_ - how much digits use for output number to FGA text file.
void XGeomExportFGA(QString file_name,
    const QVector<vec3> QVector_field,
	int nx, int ny, int nz, 
    vec3 lower_bound = vec3(-1,-1,-1), vec3 upper_bound = vec3(-1, -1, -1),
	int float_precision = 5);

// Export QVector field as image atlas: float-valued tif RGB [0..1].
// [-max_field_value,max_field_value] is mapped to [0..1]
// Please use tif file format in name, for example, "atlas.tif"
void XGeomExportVectorFieldAsAtlasImage(QString tif_file_name,
    const QVector<vec3> QVector_field,
	int nx, int ny, int nz, float max_field_value = 1);


