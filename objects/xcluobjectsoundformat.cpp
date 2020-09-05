#include "xcluobjectsoundformat.h"
#include "incl_cpp.h"
#include "interfaceguiobject.h"

//---------------------------------------------------------------------
XDictSoundFormat::XDictSoundFormat(XDict *object)
: XDictWrapper(object)
{

}

//---------------------------------------------------------------------
//создание объекта
/*static*/ void XDictSoundFormat::set_to_object(XDictWrite &object, XDictSoundFormatData &data) {
    object.set_type(XDictTypeSoundFormat);
    object.seti("sample_rate", data.sample_rate);
    object.seti("channels", data.channels);
}

//---------------------------------------------------------------------
//получение информации из объекта
/*static*/ XDictSoundFormatData XDictSoundFormat::get_data(XDictRead &object) {
    object.assert_type(XDictTypeSoundFormat);

    XDictSoundFormatData data;
    data.sample_rate = object.geti("sample_rate");
    data.channels = object.geti("channels");
    return data;
}

//---------------------------------------------------------------------
//показ в GUI
void XDictSoundFormat::show_object(InterfaceGuiObject *item) {
    auto &visual = item->visual();
    XDictRead obj(object());
    auto data = get_data(obj);

    QString line;
    line.append(QString("Sample rate: %1\n").arg(data.sample_rate));
    line.append(QString("Channels: %1\n").arg(data.channels));
    visual.set_text(line);

    visual.clear_image();

}
