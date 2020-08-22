#include "qt_widgets.h"
#include "xcluobjectwrapper.h"
#include "incl_qtcpp.h"
#include "interfaceitemobject.h"
#include "interfaceguiobject.h"
#include "xcluobjectimage.h"
#include "xcluobjectsoundformat.h"


//---------------------------------------------------------------------
/*static*/ XcluObjectWrapper *XcluObjectWrapper::create_wrapper(XcluObject *object) {
    //xclu_assert(object, "Internal error in 'create_wrapper': object is nullptr");
    auto type = ObjectRead(object).type();
    switch (type) {
    case XcluObjectTypeEmpty:
    case XcluObjectTypeCustom:
    case XcluObjectTypeSoundBuffer:
        return new XcluObjectWrapper(object);
        break;
    case XcluObjectTypeSoundFormat:
        return new XcluObjectSoundFormat(object);
        break;
    case XcluObjectTypeImage:
        return new XcluObjectImage(object);
        break;
    default:
        xclu_exception(QString("Unknown object type '%1'").arg(type));
    }
    return nullptr;
}

//---------------------------------------------------------------------
XcluObjectWrapper::XcluObjectWrapper(XcluObject *object) {
    object_ = object;
}

//---------------------------------------------------------------------
XcluObject *XcluObjectWrapper::object() {
    return object_;
}

//---------------------------------------------------------------------
//показать объект в редакторе
void XcluObjectWrapper::show_object(InterfaceGuiObject *item) {
    auto &visual = item->visual();

    {
        ObjectRead obj(object());

        //тип объекта и размер объекта в байтах
        visual.set_text(QString("%1\n%2 byte(s)")
                        .arg(object_type_to_string(obj.type()))
                        .arg(obj.size_bytes()));
    }
    visual.clear_image();

}

//---------------------------------------------------------------------
//показать объект в QLabel
void XcluObjectWrapper::show_object(QLabel *label, const XcluObjectShowSettings &settings) {
    label->setText("");
}

//---------------------------------------------------------------------
