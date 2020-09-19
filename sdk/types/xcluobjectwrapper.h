#ifndef XCLUOBJECTWRAPPER_H
#define XCLUOBJECTWRAPPER_H

//"Обертка" для XStruct.
//Он и его наследники позволяют следующее:
//1. представлять объекты в GUI редактора,
//2. описывать, как хранить настройки показа
//3. получать удобный доступ к параметрам объекта
//4. конвертировать типы Qt, например, изображения, в объект и обратно

//Работа с ним идет путем создания wrapper, который будет привязан к типу объекта,
//и затем работа с ним:
//QScopedPointer<XStructWrapper> wrapper;
//wrapper.reset(XStructWrapper::create_wrapper(object));
//wrapper->show_object(this);
//(QScopedPointer удалить объект автоматически)


#include "incl_h.h"
#include "xstruct.h"

class QLabel;
class XItemObject;
class XGuiObjectVisual;
class XStruct;
class XGuiObject;


//настройки показа объекта
class XStructShowSettings {
public:
    int w = 256;
    int h = 256;
};

//wrapper для работы и показа объекта
class XStructWrapper
{
public:
    //создать wrapper для типа объекта, чтобы затем его вывести в GUI
    //или проделать другие операции
    static XStructWrapper *create_wrapper(XStruct *object);

    XStructWrapper(XStruct *object);

    XStruct *object();

    //показать объект в редакторе
    virtual void show_object(XGuiObject *item);

    //показать объект в QLabel
    virtual void show_object(QLabel *label, const XStructShowSettings &settings);

protected:
    XStruct *object_;
};

#endif // XCLUOBJECTWRAPPER_H
