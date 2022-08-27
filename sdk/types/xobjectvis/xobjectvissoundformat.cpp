#include "xobjectvissoundformat.h"
#include "xobject.h"

//---------------------------------------------------------------------
XObjectVisSoundFormat::XObjectVisSoundFormat(XObject *object)
    : XObjectVis(object)
{

}

//---------------------------------------------------------------------
QStringList XObjectVisSoundFormat::short_description() const {
    if (!object_) {
        return QStringList();
    }

    QString line;
    line.append(QString("Sample rate: %1\n").arg(data.sample_rate));
    line.append(QString("Channels: %1\n").arg(data.channels));
    visual.set_text(line);

    visual.clear_image();

    return QStringList()
            << QString("%1 %2")
               .arg(XObjectType_to_string(object_->type()))
               .arg(object_->subtype());

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
