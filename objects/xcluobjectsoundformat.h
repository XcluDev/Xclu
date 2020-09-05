#ifndef XCLUOBJECTSOUNDFORMAT_H
#define XCLUOBJECTSOUNDFORMAT_H

//Звуковой формат - число каналов, частота дискретизации, размер буфера

#include "xdict.h"
#include "xcluobjectwrapper.h"
class InterfaceGuiObject;

//данные
class XDictSoundFormatData {
public:
    int sample_rate = 0;
    int channels = 0;
    XDictSoundFormatData() {}
    XDictSoundFormatData(int sample_rate, int channels) {
        this->sample_rate = sample_rate;
        this->channels = channels;
    }
    void clear() {
        sample_rate = 0;
        channels = 0;
    }
};


//wrapper
class XDictSoundFormat: public XDictWrapper {
public:
    XDictSoundFormat(XDict *object);

    //показ в GUI
    virtual void show_object(InterfaceGuiObject *item);

    //создание объекта
    static void set_to_object(XDictWrite &object, XDictSoundFormatData &data);

    //получение информации из объекта
    static XDictSoundFormatData get_data(XDictRead &object);


};

#endif // XCLUOBJECTSOUNDFORMAT_H
