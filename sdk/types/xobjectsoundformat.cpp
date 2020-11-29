#include "xobjectsoundformat.h"
#include "incl_cpp.h"
#include "xguiobject.h"

//---------------------------------------------------------------------
XObjectSoundFormat::XObjectSoundFormat(const XObject *object)
: XObjectWrapper(object)
{

}

//---------------------------------------------------------------------
//создание объекта
/*static*/ void XObjectSoundFormat::set_to_object(XObject &object, XObjectSoundFormatData &data) {
    object.set_type(XObjectTypeSoundFormat);
    object.seti("sample_rate", data.sample_rate);
    object.seti("channels", data.channels);
}

//---------------------------------------------------------------------
//получение информации из объекта
/*static*/ XObjectSoundFormatData XObjectSoundFormat::get_data(const XObject *object) {
    object->assert_type(XObjectTypeSoundFormat);

    XObjectSoundFormatData data;
    data.sample_rate = object->geti("sample_rate");
    data.channels = object->geti("channels");
    return data;
}

//---------------------------------------------------------------------
//показ в GUI
void XObjectSoundFormat::show_object(XGuiObject *item) {
    auto &visual = item->visual();
    auto data = get_data(object());

    QString line;
    line.append(QString("Sample rate: %1\n").arg(data.sample_rate));
    line.append(QString("Channels: %1\n").arg(data.channels));
    visual.set_text(line);

    visual.clear_image();

}
