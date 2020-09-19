#include "qt_widgets.h"
#include "xcluobjectwrapper.h"
#include "incl_cpp.h"
#include "xitemobject.h"
#include "xguiobject.h"
#include "xcluobjectimage.h"
#include "xcluobjectsoundformat.h"


//---------------------------------------------------------------------
/*static*/ XStructWrapper *XStructWrapper::create_wrapper(XStruct *object) {
    //xclu_assert(object, "Internal error in 'create_wrapper': object is nullptr");
    auto type = XStructRead(object).type();
    switch (type) {
    case XStructTypeEmpty:
    case XStructTypeCustom:
    case XStructTypeSoundBuffer:
        return new XStructWrapper(object);
        break;
    case XStructTypeSoundFormat:
        return new XStructSoundFormat(object);
        break;
    case XStructTypeImage:
        return new XStructImage(object);
        break;
    default:
        xclu_exception(QString("Unknown object type '%1'").arg(type));
    }
    return nullptr;
}

//---------------------------------------------------------------------
XStructWrapper::XStructWrapper(XStruct *object) {
    object_ = object;
}

//---------------------------------------------------------------------
XStruct *XStructWrapper::object() {
    return object_;
}

//---------------------------------------------------------------------
//показать объект в редакторе
void XStructWrapper::show_object(XGuiObject *item) {
    auto &visual = item->visual();

    {
        XStructRead obj(object());

        //тип объекта и размер объекта в байтах
        visual.set_text(QString("%1\n%2 byte(s)")
                        .arg(object_type_to_string(obj.type()))
                        .arg(obj.size_bytes()));
    }
    visual.clear_image();

}

//---------------------------------------------------------------------
//показать объект в QLabel
void XStructWrapper::show_object(QLabel *label, const XStructShowSettings &/*settings*/) {
    label->setText("");
}

//---------------------------------------------------------------------
