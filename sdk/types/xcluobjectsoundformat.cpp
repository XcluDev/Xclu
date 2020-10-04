#include "xcluobjectsoundformat.h"
#include "incl_cpp.h"
#include "xguiobject.h"

//---------------------------------------------------------------------
XStructSoundFormat::XStructSoundFormat(const XStruct *object)
: XStructWrapper(object)
{

}

//---------------------------------------------------------------------
//создание объекта
/*static*/ void XStructSoundFormat::set_to_object(XStruct &object, XStructSoundFormatData &data) {
    object.set_type(XStructTypeSoundFormat);
    object.seti("sample_rate", data.sample_rate);
    object.seti("channels", data.channels);
}

//---------------------------------------------------------------------
//получение информации из объекта
/*static*/ XStructSoundFormatData XStructSoundFormat::get_data(const XStruct &object) {
    object.assert_type(XStructTypeSoundFormat);

    XStructSoundFormatData data;
    data.sample_rate = object.geti("sample_rate");
    data.channels = object.geti("channels");
    return data;
}

//---------------------------------------------------------------------
//показ в GUI
void XStructSoundFormat::show_object(XGuiObject *item) {
    auto &visual = item->visual();
    const XStruct &obj = *object();
    auto data = get_data(obj);

    QString line;
    line.append(QString("Sample rate: %1\n").arg(data.sample_rate));
    line.append(QString("Channels: %1\n").arg(data.channels));
    visual.set_text(line);

    visual.clear_image();

}
