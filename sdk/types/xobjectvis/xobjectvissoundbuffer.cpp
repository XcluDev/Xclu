#include "xobjectvissoundbuffer.h"
#include "xobject.h"

//---------------------------------------------------------------------
XObjectVisSoundBuffer::XObjectVisSoundBuffer(const XObject *object)
    : XObjectVis(object)
{

}

//---------------------------------------------------------------------
QStringList XObjectVisSoundBuffer::short_description() const {
    if (!object_) {
        return QStringList();
    }
    return QStringList()
            << QString("%1 %2")
               .arg(XType_to_string(object_->type()))
               .arg(object_->subtype());

}

//---------------------------------------------------------------------
int XObjectVisSoundBuffer::detailed_description_size() const {
    return 0;
}

//---------------------------------------------------------------------
QString XObjectVisSoundBuffer::detailed_description(int /*i*/) const {
    return "";
}

//---------------------------------------------------------------------
bool XObjectVisSoundBuffer::is_thumbnail_exists() const {
    return false;
}

//---------------------------------------------------------------------
void XObjectVisSoundBuffer::draw_thumbnail(QPainter &/*p*/, int /*w*/, int /*h*/) const {
}

//---------------------------------------------------------------------
