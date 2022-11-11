#include "XGeomExportVectorField.h"
#include <QDebug>
#include "xutils.h"
#include "xraster.h"
#include "xrasterutils.h"
#include "xfiles.h"

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
    file[k++] = x_to_string(nx) + "," + x_to_string(ny) + "," + x_to_string(nz) + ",";
    file[k++] = x_to_string(lower_bound.x) + "," + x_to_string(lower_bound.y) + "," + x_to_string(lower_bound.z) + ",";
    file[k++] = x_to_string(upper_bound.x) + "," + x_to_string(upper_bound.y) + "," + x_to_string(upper_bound.z) + ",";
	for (int z = 0; z < nz; z++) {
		for (int y = 0; y < ny; y++) {
			for (int x = 0; x < nx; x++) {
                auto& v = QVector_field[x + nx * (y + ny * z)];
                file[k++] = x_to_string_precision(v.x, float_precision)
                    + "," + x_to_string_precision(v.y, float_precision)
                    + "," + x_to_string_precision(v.z, float_precision)
					+ ",";
			}
		}
	}

    xc_write_text_file_abspath(file, file_name);
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
    XRaster pix;
    pix.allocate(w, h, XType::vec3);
	for (int z = 0; z < nz; z++) {
		int atlas_x = (z % atlas_count)*nx;
		int atlas_y = (z / atlas_count)*ny;
		for (int y = 0; y < ny; y++) {
			for (int x = 0; x < nx; x++) {
                auto& v = QVector_field[x + nx * (y + ny * z)];
                float r = xmapf_clamped(v.x, -max_field_value, max_field_value, 0, 1);
                float g = xmapf_clamped(v.y, -max_field_value, max_field_value, 0, 1);
                float b = xmapf_clamped(v.z, -max_field_value, max_field_value, 0, 1);

                pix.set_pixel_unsafe<vec3>(x + atlas_x, y + atlas_y, vec3(r, g, b));
			}
		}
    }

    XRasterUtils::save(pix, tif_file_name);

}
