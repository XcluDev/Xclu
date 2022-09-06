#include "XGeomExportVectorField.h"
#include <QDebug>


//--------------------------------------------------------------------------------
void XGeomExportFGA(QString file_name,
    const QVector<vec3> QVector_field,
	int nx, int ny, int nz, 
    vec3 lower_bound, vec3 upper_bound,
	int float_precision)
{
    qDebug() << "Saving FGA " << nx << " x " << ny << " x " << nz << " to " << file_name << endl;
	int n = nx * ny * nz;
    if (n != QVector_field.size()) {
        qDebug() << "Bad array size!" << endl;
		return;
	}
    QVector<QString> file(n + 3);
	int k = 0;
	file[k++] = ofToString(nx) + "," + ofToString(ny) + "," + ofToString(nz) + ",";
	file[k++] = ofToString(lower_bound.x) + "," + ofToString(lower_bound.y) + "," + ofToString(lower_bound.z) + ",";
	file[k++] = ofToString(upper_bound.x) + "," + ofToString(upper_bound.y) + "," + ofToString(upper_bound.z) + ",";
	for (int z = 0; z < nz; z++) {
		for (int y = 0; y < ny; y++) {
			for (int x = 0; x < nx; x++) {
                auto& v = QVector_field[x + nx * (y + ny * z)];
				file[k++] = ofToString(v.x, float_precision) 
					+ "," + ofToString(v.y, float_precision) 
					+ "," + ofToString(v.z, float_precision)
					+ ",";
			}
		}
	}

    XGeomFileWriteStrings(file, file_name);
    qDebug() << "   ...done" << endl;
}

//--------------------------------------------------------------------------------
void XGeomExportVectorFieldAsAtlasImage(QString tif_file_name,
    const QVector<vec3> QVector_field,
	int nx, int ny, int nz, float max_field_value)
{
	if (!(nx == ny && ny == nz && nz == 64)) {
        qDebug() << "XGeomExportVectorFieldAsImage error - only 64x64x64 QVector images are supported" << endl;
		return;
	}
	int n = nx;
	int atlas_count = 8;
	int w = atlas_count * n;
	int h = w;
	ofFloatPixels pix;
	pix.allocate(w, h, 3);
	for (int z = 0; z < nz; z++) {
		int atlas_x = (z % atlas_count)*nx;
		int atlas_y = (z / atlas_count)*ny;
		for (int y = 0; y < ny; y++) {
			for (int x = 0; x < nx; x++) {
                auto& v = QVector_field[x + nx * (y + ny * z)];
				float r = ofMap(v.x, -max_field_value, max_field_value, 0, 1, true);
				float g = ofMap(v.y, -max_field_value, max_field_value, 0, 1, true);
				float b = ofMap(v.z, -max_field_value, max_field_value, 0, 1, true);
				pix.setColor(x + atlas_x, y + atlas_y, ofFloatColor(r, g, b));
			}
		}
	}

	ofSaveImage(pix, tif_file_name);

}
