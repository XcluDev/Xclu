#pragma once

// Сделано на основе ofxKu/OfxKuMeshUtils
//- loading OBJ files
//- computing normals
//- make wireframed mesh from triangle mesh
//- shuffle verties and triangles

#include <QVector>
#include <QString>
#include "xmath.h"
#include "XGeomMesh.h"


void XGeomLoadObjFile( XGeomMesh &mesh, QString fileName, bool useTex,
                   bool setupNormals, bool normalize,
                   bool separateFaces, bool shuffle, int texW, int texH//,
//				   bool caching_to_ply = true
);


void XGeomSaveObjFile(XGeomMesh &mesh, QString fileName, bool setupNormals,
    bool textured, QString mtl_file ="", int texW=0, int texH=0
);		//sets normals and so change mesh!


// Remove duplicated vertices - it occurs for IcoPrimitive, for example
void XGeomMeshRemoveDuplicates(XGeomMesh& mesh_in, XGeomMesh& mesh_out, float eps = 0.001, bool verbose_duplicated = false);
void XGeomMeshRemoveDuplicates(XGeomMesh& mesh, float eps = 0.001, bool verbose_duplicated = false);

// Set normals
void XGeomSetNormals(XGeomMesh &mesh, bool invert = false, bool remove_duplicates = false, float eps = 0.001, bool verbose_duplicated = false);

// Shuffle vertices and triangles
void XGeomMeshShuffle( QVector<vec3> &v, QVector<int> &t, QVector<vec2> &tex,
                   bool useTex = true, float shuffle_count=2 );

// Move and scale mesh vertices
void XGeomMeshTransform(QVector<vec3>& v, vec3 translate, vec3 scale);

//-------------------------







