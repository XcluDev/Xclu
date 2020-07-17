#ifndef XCLUOBJECTSOUNDFORMAT_H
#define XCLUOBJECTSOUNDFORMAT_H

//Звуковой формат - число каналов, частота дискретизации, размер буфера

#include "xcluobject.h"
#include "xcluobjectwrapper.h"
class InterfaceGuiObject;

//данные
class XcluObjectSoundFormatData {
public:
    int sample_rate = 0;
    int channels = 0;
    XcluObjectSoundFormatData() {}
    XcluObjectSoundFormatData(int sample_rate, int channels) {
        this->sample_rate = sample_rate;
        this->channels = channels;
    }
    void clear() {
        sample_rate = 0;
        channels = 0;
    }
};


//wrapper
class XcluObjectSoundFormat: public XcluObjectWrapper {
public:
    XcluObjectSoundFormat(XcluObject *object);

    //показ в GUI
    virtual void show_object(InterfaceGuiObject *item);

    //создание объекта
    static void set_to_object(ObjectReadWrite &object, XcluObjectSoundFormatData &data);

    //получение информации из объекта
    static XcluObjectSoundFormatData get_data(ObjectRead &object);


};

#endif // XCLUOBJECTSOUNDFORMAT_H
