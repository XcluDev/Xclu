#include "xobjectvisimage.h"
#include "xobject.h"

//---------------------------------------------------------------------
XObjectVisImage::XObjectVisImage(XObject *object)
    : XObjectVis(object)
{

}
//---------------------------------------------------------------------
QStringList XObjectVisImage::short_description() const {
    XRaster *raster = object_->data<XRaster>();
    return QStringList() << QString("Image %1 x %2, type: ").arg(raster.w).arg(raster.h).arg(XTypeId_to_string(raster.type_id));
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
void XObjectVisImage::draw_thumbnail(QPainter &p, int w, int h) const {

    XRasterUtils::draw(&p, &raster, 0, 0, w, h);
}

//---------------------------------------------------------------------
/*
//Загрузка изображения с диска
//TODO выполняется через QImage, поэтому не очень быстрая
//быстрее через OpenCV или FreeImage или TurboJpeg
void XObjectImage::load(XObject &object, QString file_name) {
    QImage qimage;
    xc_assert(qimage.load(file_name), "Can't load image " + file_name);
    create_from_QImage(object, qimage, "RGB", XTypeId::uint8);
}

//---------------------------------------------------------------------
//Запись на диск
//TODO выполняется через QImage, поэтому не очень быстрая
//быстрее через OpenCV или FreeImage или TurboJpeg
void XObjectImage::save(const XObject &object, QString file_name, QString format, int quality) {
    QImage qimage;
    link_to_QImage(object, qimage);
    xc_assert(!qimage.isNull(), "XObjectImage::save - null resulted QImage");
    xc_assert(qimage.save(file_name, format.toStdString().c_str(), quality),
                "Can't save image " + file_name);
}
*/
//---------------------------------------------------------------------
