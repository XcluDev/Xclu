#ifndef XCLUOBJECTSOUNDFORMAT_H
#define XCLUOBJECTSOUNDFORMAT_H

//Звуковой формат - число каналов, частота дискретизации, размер буфера

#include "xobject.h"
#include "xcluobjectwrapper.h"
class XGuiObject;

//данные
class XObjectSoundFormatData {
public:
    int sample_rate = 0;
    int channels = 0;
    XObjectSoundFormatData() {}
    XObjectSoundFormatData(int sample_rate, int channels) {
        this->sample_rate = sample_rate;
        this->channels = channels;
    }
    void clear() {
        sample_rate = 0;
        channels = 0;
    }
};


//wrapper
class XObjectSoundFormat: public XObjectWrapper {
public:
    XObjectSoundFormat(const XObject *object);

    //показ в GUI
    virtual void show_object(XGuiObject *item);

    //создание объекта
    static void set_to_object(XObject &object, XObjectSoundFormatData &data);

    //получение информации из объекта
    static XObjectSoundFormatData get_data(const XObject *object);


};

#endif // XCLUOBJECTSOUNDFORMAT_H
