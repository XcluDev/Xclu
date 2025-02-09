#include "xobjectvisimage.h"
#include "xobject.h"
#include "xrasterutils.h"

//---------------------------------------------------------------------
XObjectVisImage::XObjectVisImage(const XObject *object)
    : XObjectVis(object)
{

}
//---------------------------------------------------------------------
QStringList XObjectVisImage::short_description() const {
    auto *raster = object_->data<XRaster>();
    return QStringList() << QString("Image %1 x %2, type: %3")
                            .arg(raster->w)
                            .arg(raster->h)
                            .arg(XType_to_string(raster->type));
    //info_text += QString("\n%1x%2, %3, %4").arg(d.w).arg(d.h).arg(d.channels_description).arg(d.data_type);
    //visual.set_text(info_text);
}

//---------------------------------------------------------------------
int XObjectVisImage::detailed_description_size() const {
    return 0;
}

//---------------------------------------------------------------------
QString XObjectVisImage::detailed_description(int i) const {
    return "";
}

//---------------------------------------------------------------------
bool XObjectVisImage::is_thumbnail_exists() const {
    const XRaster *raster = object_->data<XRaster>();
    return (raster && !raster->is_empty());
}

//---------------------------------------------------------------------
void XObjectVisImage::draw_thumbnail(QPainter &p, int w, int h) const {
    xc_assert(is_thumbnail_exists(), "XObjectVisImage::draw_thumbnail - no thumbnail exists");
    const XRaster *raster = object_->data<XRaster>();
    if (raster) {
        XRasterUtils::draw(p, *raster, 0, 0, w, h);
    }
}

//---------------------------------------------------------------------
/*
//Загрузка изображения с диска
//TODO выполняется через QImage, поэтому не очень быстрая
//быстрее через OpenCV или FreeImage или TurboJpeg
void XRasterUtils::load(XObject &object, QString file_name) {
    QImage qimage;
    xc_assert(qimage.load(file_name), "Can't load image " + file_name);
    create_from_QImage(object, qimage, "RGB", XType::uint8);
}

//---------------------------------------------------------------------
//Запись на диск
//TODO выполняется через QImage, поэтому не очень быстрая
//быстрее через OpenCV или FreeImage или TurboJpeg
void XRasterUtils::save(const XObject &object, QString file_name, QString format, int quality) {
    QImage qimage;
    link_to_QImage(object, qimage);
    xc_assert(!qimage.isNull(), "XRasterUtils::save - null resulted QImage");
    xc_assert(qimage.save(file_name, format.toStdString().c_str(), quality),
                "Can't save image " + file_name);
}
*/
//---------------------------------------------------------------------
