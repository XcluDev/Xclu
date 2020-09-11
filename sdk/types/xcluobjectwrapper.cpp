#include "qt_widgets.h"
#include "xcluobjectwrapper.h"
#include "incl_cpp.h"
#include "xitemobject.h"
#include "xguiobject.h"
#include "xcluobjectimage.h"
#include "xcluobjectsoundformat.h"


//---------------------------------------------------------------------
/*static*/ XDictWrapper *XDictWrapper::create_wrapper(XDict *object) {
    //xclu_assert(object, "Internal error in 'create_wrapper': object is nullptr");
    auto type = XDictRead(object).type();
    switch (type) {
    case XDictTypeEmpty:
    case XDictTypeCustom:
    case XDictTypeSoundBuffer:
        return new XDictWrapper(object);
        break;
    case XDictTypeSoundFormat:
        return new XDictSoundFormat(object);
        break;
    case XDictTypeImage:
        return new XDictImage(object);
        break;
    default:
        xclu_exception(QString("Unknown object type '%1'").arg(type));
    }
    return nullptr;
}

//---------------------------------------------------------------------
XDictWrapper::XDictWrapper(XDict *object) {
    object_ = object;
}

//---------------------------------------------------------------------
XDict *XDictWrapper::object() {
    return object_;
}

//---------------------------------------------------------------------
//показать объект в редакторе
void XDictWrapper::show_object(XGuiObject *item) {
    auto &visual = item->visual();

    {
        XDictRead obj(object());

        //тип объекта и размер объекта в байтах
        visual.set_text(QString("%1\n%2 byte(s)")
                        .arg(object_type_to_string(obj.type()))
                        .arg(obj.size_bytes()));
    }
    visual.clear_image();

}

//---------------------------------------------------------------------
//показать объект в QLabel
void XDictWrapper::show_object(QLabel *label, const XDictShowSettings &/*settings*/) {
    label->setText("");
}

//---------------------------------------------------------------------
