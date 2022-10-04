#include "XGeomMeshUtils.h"
#include <QDebug>
#include "xutils.h"
#include "xhandlingerrors.h"
#include "xfiles.h"

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
    auto lines = xc_read_text_file(fileName);

    QVector<vec3> v;      //vertices
    QVector<int> t;  //indices for triangles
    QVector<vec2> tex;    //texture coords

    vec3 p;
	int f[4];

    qDebug() << "   parsing..." << endl;
	for (int i = 0; i < lines.size(); i++) {
        QStringList list = lines[i].split(" ");
		int n = list.size();
		if (n > 0) {
			if (list[0] == "v" && n >= 4) {
                v.push_back(vec3(
                    x_string_to_float(list[1]),
                    x_string_to_float(list[2]),
                    x_string_to_float(list[3])
				));
			}
			if (useTex && list[0] == "vt" && n >= 3) {
                tex.push_back(vec2(
                    x_string_to_float(list[1]) * texW,
                    x_string_to_float(list[2]) * texH
				));
			}
			if (list[0] == "f" && n >= 4) {
                int N =qMin(n - 1, 4);
				for (int j = 0; j < N; j++) {
                    QStringList line = list[j + 1].split("/");
					if (line.size() > 0) {
                        f[j] = x_string_to_int(line[0]) - 1;

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
                p0.x = qMin(p0.x, p.x);
                p0.y = qMin(p0.y, p.y);
                p0.z = qMin(p0.z, p.z);
                p1.x = qMax(p1.x, p.x);
                p1.y = qMax(p1.y, p.y);
                p1.z = qMax(p1.z, p.z);
			}
		}
        vec3 c = (p0 + p1) * 0.5f;
        vec3 delta = p1 - p0;
		float scl = delta.x;
        scl = qMax(scl, delta.y);
        scl = qMax(scl, delta.z);
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
    mesh.vertices = v;

	//texture coords
	if (useTex) {
		if (tex.size() >= v.size()) {
            mesh.tex_coords = tex;
		}
		else {
            qDebug() << "Error in OBJ model, not enough texture coords" << endl;
		}
	}

	//triangles
    mesh.indices = t;

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

    auto &v = mesh.vertices;
	int n = v.size();

    auto &vt = mesh.tex_coords;
    auto &vn = mesh.normals;

    QVector<int> &ind = mesh.indices;
	int m = ind.size() / 3;

	if (setupNormals) {
        XGeomSetNormals(mesh);
	}
	int N = n + m;
	if (setupNormals) N += n;
	if (textured) N += n;

    QVector<QString> list(2 + N);	//header, v, vt, vn, f
	int j = 0;

    if (textured && !mtl_file.isEmpty()) {
		list[j++] = "mtllib " + mtl_file; // +".mtl";
		list[j++] = "usemtl texture";
	}

    qDebug() << "    v  " << n << "..." << endl;
	for (int i = 0; i < n; i++) {
		list[j++] = "v " + x_to_string(v[i].x) + " " + x_to_string(v[i].y) + " " + x_to_string(v[i].z);
	}

	if (setupNormals) {
        qDebug() << "    vn..." << endl;
		for (int i = 0; i < n; i++) {
			list[j++] = "vn " + x_to_string(vn[i].x) + " " + x_to_string(vn[i].y) + " " + x_to_string(vn[i].z);
		}
	}

	if (textured) {
        qDebug() << "    vt..." << endl;
		for (int i = 0; i < n; i++) {
			list[j++] = "vt " + x_to_string(vt[i].x / texW) + " " + x_to_string(vt[i].y / texH);
		}
	}


    qDebug() << "    f..." << endl;
	for (int i = 0; i < m; i++) {
        QString a1 = x_to_string(ind[i * 3] + 1);
        QString b1 = x_to_string(ind[i * 3 + 1] + 1);
        QString c1 = x_to_string(ind[i * 3 + 2] + 1);
        QString a = a1 + "/" + ((textured) ? a1 : "") + ((setupNormals) ? "/" + a1 : "");
        QString b = b1 + "/" + ((textured) ? b1 : "") + ((setupNormals) ? "/" + b1 : "");
        QString c = c1 + "/" + ((textured) ? c1 : "") + ((setupNormals) ? "/" + c1 : "");
		list[j++] = "f " + a + " " + b + " " + c;
	}

    qDebug() << "Writing " << fileName << "..." << endl;
    xc_write_text_file(list, fileName);
    qDebug() << "Ok saving " << fileName << endl;

}


//--------------------------------------------------------
//shuffle vertices and triangles
void XGeomMeshShuffle(QVector<vec3> &v, QVector<int> &t, QVector<vec2> &tex,
	bool useTex, float shuffle_count) {

    xc_exception("XGeomMeshShuffle not implemented");
/*	int n = v.size();
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
        i = qMin(i, n - 1);
		int j = ofRandom(0, n);
        j = qMin(j, n - 1);
		if (i != j) {
            qSwap(vfrom[vto[i]], vfrom[vto[j]]);
            qSwap(vto[i], vto[j]);
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
        i = qMin(i, T - 1);
		int j = ofRandom(0, T);
        j = qMin(j, T - 1);
		if (i != j) {
			int a = i * 3;
			int b = j * 3;
            qSwap(t[a], t[b]);
            qSwap(t[a + 1], t[b + 1]);
            qSwap(t[a + 2], t[b + 2]);
		}
    }*/
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
        qDebug() << "Removing duplicated vertices, input vertices " << mesh_in.vertices.size() << endl;
	}
	// Build vertices
	const float eps2 = eps * eps;
    auto& input = mesh_in.vertices;
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
        mesh_out.vertices = pnt;
		// Normals
        if (mesh_in.normals.size() == pnt.size()) {
			for (int j = 0; j < pnt.size(); j++) {
                mesh_out.normals.push_back(mesh_in.normals[indices[j]]);
			}
		}
		// Tex coords
        if (mesh_in.tex_coords.size() == pnt.size()) {
			for (int j = 0; j < pnt.size(); j++) {
                mesh_out.tex_coords.push_back(mesh_in.tex_coords[indices[j]]);
			}
		}
		// Triangles
        for (int i = 0; i < mesh_in.indices.size(); i++) {
            mesh_out.indices.push_back(remap[mesh_in.indices[i]]);
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
    int nV = mesh.vertices.size();

	//The number of the triangles
    int nT = mesh.indices.size() / 3;

    QVector<vec3> norm(nV); //Array for the normals

	//Scan all the triangles. For each triangle add its
    //normal to norm's QVectors of triangle's vertices
	for (int t = 0; t < nT; t++) {

		//Get indices of the triangle t
        int i1 = mesh.indices[3 * t];
        int i2 = mesh.indices[3 * t + 1];
        int i3 = mesh.indices[3 * t + 2];

		//Get vertices of the triangle
        const vec3 &v1 = mesh.vertices[i1];
        const vec3 &v2 = mesh.vertices[i2];
        const vec3 &v3 = mesh.vertices[i3];

		//Compute the triangle's normal
        vec3 dir = -glm::normalize(glm::cross(v2 - v1,v3 - v1));

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
    mesh.normals = norm;
}

//--------------------------------------------------------
void XGeomCreateWireframe(XGeomMesh &mesh, XGeomMesh &mesh_out) { //for triangle mesh

    auto &v = mesh.vertices;
	int n = v.size();

    QVector<int> &ind = mesh.indices;
	int m = ind.size() / 3;

	mesh_out = mesh;
    mesh_out.vertices.clear();

	for (int i = 0; i < m; i++) {
		int i1 = ind[i * 3];
		int i2 = ind[i * 3 + 1];
		int i3 = ind[i * 3 + 2];
        mesh_out.indices.push_back(i1);
        mesh_out.indices.push_back(i2);
        mesh_out.indices.push_back(i2);
        mesh_out.indices.push_back(i2);
        mesh_out.indices.push_back(i3);
        mesh_out.indices.push_back(i3);
        mesh_out.indices.push_back(i3);
        mesh_out.indices.push_back(i1);
        mesh_out.indices.push_back(i1);
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


