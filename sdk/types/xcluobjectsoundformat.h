#ifndef XCLUOBJECTSOUNDFORMAT_H
#define XCLUOBJECTSOUNDFORMAT_H

//Звуковой формат - число каналов, частота дискретизации, размер буфера

#include "xstruct.h"
#include "xcluobjectwrapper.h"
class XGuiObject;

//данные
class XStructSoundFormatData {
public:
    int sample_rate = 0;
    int channels = 0;
    XStructSoundFormatData() {}
    XStructSoundFormatData(int sample_rate, int channels) {
        this->sample_rate = sample_rate;
        this->channels = channels;
    }
    void clear() {
        sample_rate = 0;
        channels = 0;
    }
};


//wrapper
class XStructSoundFormat: public XStructWrapper {
public:
    XStructSoundFormat(const XStruct *object);

    //показ в GUI
    virtual void show_object(XGuiObject *item);

    //создание объекта
    static void set_to_object(XStruct &object, XStructSoundFormatData &data);

    //получение информации из объекта
    static XStructSoundFormatData get_data(const XStruct &object);


};

#endif // XCLUOBJECTSOUNDFORMAT_H
