#include "xobjectvissoundformat.h"
#include "xobject.h"

//---------------------------------------------------------------------
XObjectVisSoundFormat::XObjectVisSoundFormat(const XObject *object)
    : XObjectVis(object)
{

}

//---------------------------------------------------------------------
QStringList XObjectVisSoundFormat::short_description() const {
    if (!object_) {
        return QStringList();
    }
    auto* format = object_->data<XSoundFormat>();
    if (!format) {
        return QStringList();
    }

    return QStringList() << QString("Sample rate: %1\n").arg(format->sample_rate)
                         << QString("Channels: %1\n").arg(format->channels);
}

//---------------------------------------------------------------------
int XObjectVisSoundFormat::detailed_description_size() const {
    return 0;
}

//---------------------------------------------------------------------
QString XObjectVisSoundFormat::detailed_description(int /*i*/) const {
    return "";
}

//---------------------------------------------------------------------
bool XObjectVisSoundFormat::is_thumbnail_exists() const {
    return false;
}

//---------------------------------------------------------------------
void XObjectVisSoundFormat::draw_thumbnail(QPainter &/*p*/, int /*w*/, int /*h*/) const {
}

//---------------------------------------------------------------------
