#include "raster.h"
#include "incl_cpp.h"
#include <QImage>
#include <QImageReader>
#include <QImageWriter>

//-------------------------------------------------------
void raster_to_raster(Raster_u8c3 &raster_rgb, Raster_u8 &raster) {
    raster.allocate(raster_rgb.w, raster_rgb.h);
    for (int i=0; i<raster.w*raster.h; i++) {
        raster.data[i] = raster_rgb.data[i].gray();
    }
}

//-------------------------------------------------------
void raster_to_raster(Raster_u8 &raster, Raster_u8c3 &raster_rgb) {
    raster_rgb.allocate(raster.w, raster.h);
    for (int i=0; i<raster.w*raster.h; i++) {
        raster_rgb.data[i] = u8_rgb(raster.data[i]);
    }
}

//-------------------------------------------------------
void raster_from_QImage(QImage qimage, Raster_u8 &raster) {
    int w = qimage.size().width();
    int h = qimage.size().height();

    auto format = qimage.format();
    xclu_assert(format == QImage::Format_RGB32,
                "XcluObjectImage::create_from_QImage - QImage format is unsupported, only Format_RGB32 is supported");

    raster.allocate(w, h);

    int mirrory = 0;
    for (int y=0; y<h; y++) {
        const uchar *line = qimage.scanLine(mirrory?(h-1-y):y);
        int k = 0;
        for (int x=0; x<w; x++) {
            uchar b = line[k++];
            uchar g = line[k++];
            uchar r = line[k++];
            k++;
            raster.data[x+w*y] = u8_rgb::gray(r,g,b);
        }
    }
}


//-------------------------------------------------------
void raster_from_QImage(QImage qimage, Raster_u8c3 &raster) {
    int w = qimage.size().width();
    int h = qimage.size().height();

    auto format = qimage.format();
    xclu_assert(format == QImage::Format_RGB32,
                "XcluObjectImage::create_from_QImage - QImage format is unsupported, only Format_RGB32 is supported");

    raster.allocate(w, h);

    int mirrory = 0;
    for (int y=0; y<h; y++) {
        const uchar *line = qimage.scanLine(mirrory?(h-1-y):y);
        int k = 0;
        for (int x=0; x<w; x++) {
            uchar b = line[k++];
            uchar g = line[k++];
            uchar r = line[k++];
            k++;
            raster.data[x+w*y] = u8_rgb(r,g,b);
        }
    }

}

//-------------------------------------------------------
void raster_to_QImage(Raster_u8 &raster, QImage &qimage) {
    int w = raster.w;
    int h = raster.h;
    qimage = QImage(w, h, QImage::Format_RGB32);

    int mirrory = 0;
    for (int y=0; y<h; y++) {
        uchar *line = qimage.scanLine(mirrory?(h-1-y):y);
        int k = 0;
        for (int x=0; x<w; x++) {
            auto &v = raster.data[x+w*y];
            line[k+2] = v;
            line[k+1] = v;
            line[k] = v;
            line[k+3] = 255;
            k+=4;
        }
    }
}

//-------------------------------------------------------
void raster_to_QImage(Raster_u8c3 &raster, QImage &qimage) {
    int w = raster.w;
    int h = raster.h;
    qimage = QImage(w, h, QImage::Format_RGB32);

    int mirrory = 0;
    for (int y=0; y<h; y++) {
        uchar *line = qimage.scanLine(mirrory?(h-1-y):y);
        int k = 0;
        for (int x=0; x<w; x++) {
            auto &v = raster.data[x+w*y];
            line[k+2] = v.v[0];
            line[k+1] = v.v[1];
            line[k] = v.v[2];
            line[k+3] = 255;
            k+=4;
        }
    }
}

//-------------------------------------------------------
void raster_load(QString file_name, Raster_u8 &raster) {
    QImage qimage;
    xclu_assert(qimage.load(file_name), "raster_load: Can't load image '" + file_name + "'");
    raster_from_QImage(qimage, raster);
}

//-------------------------------------------------------
void raster_load(QString file_name, Raster_u8c3 &raster) {
    QImage qimage;
    xclu_assert(qimage.load(file_name), "raster_load: Can't load image '" + file_name + "'");
    raster_from_QImage(qimage, raster);
}

//---------------------------------------------------------------------
void raster_save(Raster_u8 &raster, QString file_name, QString format, int quality) {
    QImage qimage;
    raster_to_QImage(raster, qimage);
    xclu_assert(qimage.save(file_name, format.toStdString().c_str(), quality),
                "raster_save: Can't save image '" + file_name + "'");
}

//---------------------------------------------------------------------
void raster_save(Raster_u8c3 &raster, QString file_name, QString format, int quality) {
    QImage qimage;
    raster_to_QImage(raster, qimage);
    xclu_assert(qimage.save(file_name, format.toStdString().c_str(), quality),
                "raster_save: Can't save image '" + file_name + "'");
}

//---------------------------------------------------------------------
