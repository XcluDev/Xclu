#include "xcluobjectsoundformat.h"
#include "incl_cpp.h"
#include "interfaceguiobject.h"

//---------------------------------------------------------------------
XcluObjectSoundFormat::XcluObjectSoundFormat(XcluObject *object)
: XcluObjectWrapper(object)
{

}

//---------------------------------------------------------------------
//создание объекта
/*static*/ void XcluObjectSoundFormat::set_to_object(ObjectReadWrite &object, XcluObjectSoundFormatData &data) {
    object.set_type(XcluObjectTypeSoundFormat);
    object.set_int("sample_rate", data.sample_rate);
    object.set_int("channels", data.channels);
}

//---------------------------------------------------------------------
//получение информации из объекта
/*static*/ XcluObjectSoundFormatData XcluObjectSoundFormat::get_data(ObjectRead &object) {
    object.assert_type(XcluObjectTypeSoundFormat);

    XcluObjectSoundFormatData data;
    data.sample_rate = object.get_int("sample_rate");
    data.channels = object.get_int("channels");
    return data;
}

//---------------------------------------------------------------------
//показ в GUI
void XcluObjectSoundFormat::show_object(InterfaceGuiObject *item) {
    auto &visual = item->visual();
    ObjectRead obj(object());
    auto data = get_data(obj);

    QString line;
    line.append(QString("Sample rate: %1\n").arg(data.sample_rate));
    line.append(QString("Channels: %1\n").arg(data.channels));
    visual.set_text(line);

    visual.clear_image();

}
