#include "XGeomMeshUtils.h"
#include <QDebug>

//--------------------------------------------------------
void XGeomLoadObjFile(XGeomMesh &mesh, QString fileName, bool useTex,
	bool setupNormals, bool normalize,
	bool separateFaces, bool shuffle, int texW, int texH//,
   // bool caching_to_ply 
)
{
    qDebug() << "loading " << fileName << "...";
    QString fileNamePly = fileName + ".ply";
    //if (!caching_to_ply || XGeomFileTime::isNewerThan(fileName, fileNamePly)) {
        //if (caching_to_ply) qDebug() << "   rebuild cached version..." << endl;
	mesh.clear();
    QVector<QString> lines = XGeomFileReadStrings(ofToDataPath(fileName));

    QVector<vec3> v;      //vertices
    QVector<int> t;  //indices for triangles
    QVector<vec2> tex;    //texture coords

    vec3 p;
	int f[4];

    qDebug() << "   parsing..." << endl;
	for (int i = 0; i < lines.size(); i++) {
        QVector<QString> list = ofSplitString(lines[i], " ", true, true);
		int n = list.size();
		if (n > 0) {
			if (list[0] == "v" && n >= 4) {
                v.push_back(vec3(
					ofToFloat(list[1]),
					ofToFloat(list[2]),
					ofToFloat(list[3])
				));
			}
			if (useTex && list[0] == "vt" && n >= 3) {
                tex.push_back(vec2(
					ofToFloat(list[1]) * texW,
					ofToFloat(list[2]) * texH
				));
			}
			if (list[0] == "f" && n >= 4) {
				int N = min(n - 1, 4);
				for (int j = 0; j < N; j++) {
                    QVector<QString> line = ofSplitString(list[j + 1], "/", true, true);
					if (line.size() > 0) {
						f[j] = ofToInt(line[0]) - 1;

					}
				}
				t.push_back(f[0]);
				t.push_back(f[1]);
				t.push_back(f[2]);
				//4-угольная грань
				if (n >= 5) {
					t.push_back(f[0]);
					t.push_back(f[2]);
					t.push_back(f[3]);
				}
			}

		}
	}

    qDebug() << "   processing..." << endl;
	//нормализация в куб [-1,1]x[-1,1]x[-1,1]
	if (normalize) {
        vec3 p0 = vec3(0);
        vec3 p1 = p0;
		if (v.size() > 0) {
			p0 = v[0];
			p1 = p0;
			for (int i = 0; i < v.size(); i++) {
                vec3 &p = v[i];
				p0.x = min(p0.x, p.x);
				p0.y = min(p0.y, p.y);
				p0.z = min(p0.z, p.z);
				p1.x = max(p1.x, p.x);
				p1.y = max(p1.y, p.y);
				p1.z = max(p1.z, p.z);
			}
		}
        vec3 c = (p0 + p1) * 0.5;
        vec3 delta = p1 - p0;
		float scl = delta.x;
		scl = max(scl, delta.y);
		scl = max(scl, delta.z);
		if (scl > 0) {
			scl = 1.0 / scl;
		}
		for (int j = 0; j < v.size(); j++) {
            vec3 &p = v[j];
			p = (p - c) * scl;
		}
	}

	//shuffle
	if (shuffle) {
        XGeomMeshShuffle(v, t, tex, useTex);
	}

	//vertices
	mesh.addVertices(v);

	//texture coords
	if (useTex) {
		if (tex.size() >= v.size()) {
			mesh.addTexCoords(tex);
		}
		else {
            qDebug() << "Error in OBJ model, not enough texture coords" << endl;
		}
	}

	//triangles
	mesh.addIndices(t);

	//normals
    if (setupNormals) { XGeomSetNormals(mesh); }

	//write
	//if (caching_to_ply)  mesh.save(fileNamePly);
	//}
	//else {
    //	qDebug() << "  loading cached " << fileNamePly << endl;
	//	mesh.load(fileNamePly);
	//}
}

//--------------------------------------------------------
void XGeomSaveObjFile(XGeomMesh &mesh, QString fileName, bool setupNormals,
    bool textured, QString mtl_file, int texW, int texH) {	//sets normals and so change mesh!

	auto &v = mesh.getVertices();
	int n = v.size();

	auto &vt = mesh.getTexCoords();
	auto &vn = mesh.getNormals();

    QVector<GLuint> &ind = mesh.getIndices();
	int m = ind.size() / 3;

	if (setupNormals) {
        XGeomSetNormals(mesh);
	}
	int N = n + m;
	if (setupNormals) N += n;
	if (textured) N += n;

    QVector<QString> list(2 + N);	//header, v, vt, vn, f
	int j = 0;

	if (textured && !mtl_file.empty()) {
		list[j++] = "mtllib " + mtl_file; // +".mtl";
		list[j++] = "usemtl texture";
	}

    std::qDebug() << "    v  " << n << "..." << endl;
	for (int i = 0; i < n; i++) {
		list[j++] = "v " + ofToString(v[i].x) + " " + ofToString(v[i].y) + " " + ofToString(v[i].z);
	}

	if (setupNormals) {
        std::qDebug() << "    vn..." << endl;
		for (int i = 0; i < n; i++) {
			list[j++] = "vn " + ofToString(vn[i].x) + " " + ofToString(vn[i].y) + " " + ofToString(vn[i].z);
		}
	}

	if (textured) {
        std::qDebug() << "    vt..." << endl;
		for (int i = 0; i < n; i++) {
			list[j++] = "vt " + ofToString(vt[i].x / texW) + " " + ofToString(vt[i].y / texH);
		}
	}


    std::qDebug() << "    f..." << endl;
	for (int i = 0; i < m; i++) {
        QString a = ofToString(ind[i * 3] + 1);
        QString b = ofToString(ind[i * 3 + 1] + 1);
        QString c = ofToString(ind[i * 3 + 2] + 1);
		a = a + "/" + a + "/" + a;
		b = b + "/" + b + "/" + b;
		c = c + "/" + c + "/" + c;
		list[j++] = "f " + a + " " + b + " " + c;
	}

    std::qDebug() << "Writing " << fileName << "..." << endl;
    XGeomFileWriteStrings(list, fileName);
    std::qDebug() << "Ok saving " << fileName << endl;

}


//--------------------------------------------------------
//shuffle vertices and triangles
void XGeomMeshShuffle(QVector<vec3> &v, QVector<int> &t, QVector<vec2> &tex,
	bool useTex, float shuffle_count) {

	int n = v.size();
    QVector<int> vto(n);
    QVector<int> vfrom(n);
	for (int i = 0; i < n; i++) {
		vto[i] = i;
		vfrom[i] = i;
	}
	//vertices
	int cnt = n * shuffle_count;
	for (int k = 0; k < cnt; k++) {
		int i = ofRandom(0, n);
		i = min(i, n - 1);
		int j = ofRandom(0, n);
		j = min(j, n - 1);
		if (i != j) {
			swap(vfrom[vto[i]], vfrom[vto[j]]);
			swap(vto[i], vto[j]);
		}
	}
	auto v1 = v;
	for (int i = 0; i < n; i++) {
		v[i] = v1[vto[i]];
	}
	if (useTex && tex.size() >= n) {
		auto tex1 = tex;
		for (int i = 0; i < n; i++) {
			tex[i] = tex1[vto[i]];
		}
	}
	//tune triangles
    QVector<int> t1 = t;
	for (int i = 0; i < t.size(); i++) {
		t[i] = vfrom[t1[i]];
	}

	//shuffle triangles
	int T = t.size() / 3;
	int count = T * 2;
	for (int k = 0; k < count; k++) {
		int i = ofRandom(0, T);
		i = min(i, T - 1);
		int j = ofRandom(0, T);
		j = min(j, T - 1);
		if (i != j) {
			int a = i * 3;
			int b = j * 3;
			swap(t[a], t[b]);
			swap(t[a + 1], t[b + 1]);
			swap(t[a + 2], t[b + 2]);
		}
	}
}

//--------------------------------------------------------
void XGeomMeshRemoveDuplicates(XGeomMesh& mesh, float eps, bool verbose_duplicated) {
    XGeomMesh temp = mesh;
    XGeomMeshRemoveDuplicates(temp, mesh, eps, verbose_duplicated);
}

//--------------------------------------------------------
// Remove duplicated vertices - it occurs for IcoPrimitive, for example
void XGeomMeshRemoveDuplicates(XGeomMesh& mesh_in, XGeomMesh& mesh_out, float eps, bool verbose_duplicated) {
	if (verbose_duplicated) {
        qDebug() << "Removing duplicated vertices, input vertices " << mesh_in.getNumVertices() << endl;
	}
	// Build vertices
	const float eps2 = eps * eps;
	auto& input = mesh_in.getVertices();
    QVector<int> remap(input.size());
    QVector<int> indices;
    QVector<vec3> pnt;

	for (int i = 0; i < input.size(); i++) {
		bool unique = true;
		for (int j = 0; j < pnt.size(); j++) {
			if (glm::distance2(input[i], pnt[j]) < eps2) {
				unique = false;
				remap[i] = j;

				if (verbose_duplicated) {
                    qDebug() << "Duplicated vertex " << i << " -> " << j << endl;
				}
				break;
			}
		}
		if (unique) {
			pnt.push_back(input[i]);
			remap[i] = pnt.size() - 1;
			indices.push_back(i);
		}
	}

	// Build output
	if (pnt.size() == input.size()) {
		mesh_out = mesh_in;
		if (verbose_duplicated) {
            qDebug() << "No duplicates" << endl;
		}
	}
	else {
		mesh_out.clear();
		// Vertices
		mesh_out.addVertices(pnt);
		// Normals
		if (mesh_in.getNumNormals() == pnt.size()) {
			for (int j = 0; j < pnt.size(); j++) {
				mesh_out.addNormal(mesh_in.getNormal(indices[j]));
			}
		}
		// Tex coords
		if (mesh_in.getNumTexCoords() == pnt.size()) {
			for (int j = 0; j < pnt.size(); j++) {
				mesh_out.addTexCoord(mesh_in.getTexCoord(indices[j]));
			}
		}
		// Triangles
		for (int i = 0; i < mesh_in.getNumIndices(); i++) {
			mesh_out.addIndex(remap[mesh_in.getIndex(i)]);
		}
	}
}
//--------------------------------------------------------
// Set normals
void XGeomSetNormals(XGeomMesh &mesh, bool invert, bool remove_duplicates, float eps, bool verbose_duplicated) {
	if (remove_duplicates) {
        XGeomMesh mesh2 = mesh;
        XGeomMeshRemoveDuplicates(mesh, mesh2, eps, verbose_duplicated);
		mesh = mesh2;
	}

	//The number of the vertices
	int nV = mesh.getNumVertices();

	//The number of the triangles
	int nT = mesh.getNumIndices() / 3;

    QVector<vec3> norm(nV); //Array for the normals

	//Scan all the triangles. For each triangle add its
    //normal to norm's QVectors of triangle's vertices
	for (int t = 0; t < nT; t++) {

		//Get indices of the triangle t
		int i1 = mesh.getIndex(3 * t);
		int i2 = mesh.getIndex(3 * t + 1);
		int i3 = mesh.getIndex(3 * t + 2);

		//Get vertices of the triangle
        const vec3 &v1 = mesh.getVertex(i1);
        const vec3 &v2 = mesh.getVertex(i2);
        const vec3 &v3 = mesh.getVertex(i3);

		//Compute the triangle's normal
        vec3 dir = -((v2 - v1).crossed(v3 - v1)).normalized();

		//Accumulate it to norm array for i1, i2, i3
		norm[i1] += dir;
		norm[i2] += dir;
		norm[i3] += dir;
	}

	//Normalize the normal's length and invert if required
	for (int i = 0; i < nV; i++) {
		norm[i] = glm::normalize(norm[i]);
		if (invert) {
			norm[i] = -norm[i];
		}
	}

	//Set the normals to mesh
	mesh.clearNormals();
	mesh.addNormals(norm);
}

//--------------------------------------------------------
void XGeomCreateWireframe(XGeomMesh &mesh, XGeomMesh &mesh_out) { //for triangle mesh

	auto &v = mesh.getVertices();
	int n = v.size();

    QVector<GLuint> &ind = mesh.getIndices();
	int m = ind.size() / 3;

	mesh_out = mesh;
	mesh_out.clearIndices();

	for (int i = 0; i < m; i++) {
		int i1 = ind[i * 3];
		int i2 = ind[i * 3 + 1];
		int i3 = ind[i * 3 + 2];
		mesh_out.addIndex(i1);
		mesh_out.addIndex(i2);
		mesh_out.addIndex(i2);

		mesh_out.addIndex(i2);
		mesh_out.addIndex(i3);
		mesh_out.addIndex(i3);

		mesh_out.addIndex(i3);
		mesh_out.addIndex(i1);
		mesh_out.addIndex(i1);
	}

}

//--------------------------------------------------------
// Move and scale mesh vertices
void XGeomMeshTransform(QVector<vec3>& v, vec3 translate, vec3 scale) {
	for (auto& vert : v) {
		vert = vert * scale + translate;
	}
}

//--------------------------------------------------------


