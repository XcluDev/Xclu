#include "qt_widgets.h"
#include "xobjectwrapper.h"
#include "incl_cpp.h"
#include "xitemobject.h"
#include "xguiobject.h"
#include "xobjectimage.h"
#include "xobjectsoundformat.h"


//---------------------------------------------------------------------
/*static*/ XObjectWrapper *XObjectWrapper::create_wrapper(const XObject *object) {
    //xclu_assert(object, "Internal error in 'create_wrapper': object is nullptr");
    auto type = object->type();
    switch (type) {
    case XObjectTypeEmpty:
    case XObjectTypeCustom:
    case XObjectTypeSoundBuffer:
        return new XObjectWrapper(object);
        break;
    case XObjectTypeSoundFormat:
        return new XObjectSoundFormat(object);
        break;
    case XObjectTypeImage:
        return new XObjectImage(object);
        break;
    default:
        xclu_exception(QString("Unknown object type '%1'").arg(type));
    }
    return nullptr;
}

//---------------------------------------------------------------------
XObjectWrapper::XObjectWrapper(const XObject *object) {
    object_ = object;
}

//---------------------------------------------------------------------
const XObject * XObjectWrapper::object() {
    return object_;
}

//---------------------------------------------------------------------
//показать объект в редакторе
void XObjectWrapper::show_object(XGuiObject *item) {
    auto &visual = item->visual();

    {
        //тип объекта и размер объекта в байтах
        visual.set_text(QString("%1\n%2 byte(s)")
                        .arg(object_type_to_string(object()->type()))
                        .arg(object()->size_bytes()));
    }
    visual.clear_image();

}

//---------------------------------------------------------------------
//показать объект в QLabel
void XObjectWrapper::show_object(QLabel *label, const XObjectShowSettings &/*settings*/) {
    label->setText("");
}

//---------------------------------------------------------------------
