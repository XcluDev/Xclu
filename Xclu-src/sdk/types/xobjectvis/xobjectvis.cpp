#include "qt_widgets.h"

#include "xobjectvis.h"
#include "incl_cpp.h"
#include "xguiobject.h"
#include "xrasterutils.h"

#include "xobjectvisimage.h"
#include "xobjectvissoundbuffer.h"
#include "xobjectvissoundformat.h"

//---------------------------------------------------------------------
/// Create object visualizer depending on its type. Delete after use.
/*static*/ XObjectVis* XObjectVis::new_vis(const XObject *object) {
    // TODO implement type registrar to add new vis automatically
    xc_assert(object, "XObjectVis::new_vis - bad object");
    switch (object->type()) {
    case XType::XRaster: return new XObjectVisImage(object);
    case XType::XSoundFormat: return new XObjectVisSoundFormat(object);
    case XType::XSoundBuffer: return new XObjectVisSoundBuffer(object);
    default:
        return new XObjectVis(object);
    }
}

//---------------------------------------------------------------------
XObjectVis::XObjectVis(const XObject *object) {
    object_ = object;
}

//---------------------------------------------------------------------
QStringList XObjectVis::short_description() const {
    if (!object_) {
        return QStringList();
    }
    return QStringList()
            << QString("%1 %2")
               .arg(XType_to_string(object_->type()))
               .arg(object_->subtype());

}

//---------------------------------------------------------------------
int XObjectVis::detailed_description_size() const {
    return 0;
}

//---------------------------------------------------------------------
QString XObjectVis::detailed_description(int /*i*/) const {
    return "";
}

//---------------------------------------------------------------------
bool XObjectVis::is_thumbnail_exists() const {
    return false;
}

//---------------------------------------------------------------------
void XObjectVis::draw_thumbnail(QPainter &/*p*/, int /*w*/, int /*h*/) const {
}

//---------------------------------------------------------------------
