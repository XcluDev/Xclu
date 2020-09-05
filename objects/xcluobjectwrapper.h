#ifndef XCLUOBJECTWRAPPER_H
#define XCLUOBJECTWRAPPER_H

//"Обертка" для XDict.
//Он и его наследники позволяют следующее:
//1. представлять объекты в GUI редактора,
//2. описывать, как хранить настройки показа
//3. получать удобный доступ к параметрам объекта
//4. конвертировать типы Qt, например, изображения, в объект и обратно

//Работа с ним идет путем создания wrapper, который будет привязан к типу объекта,
//и затем работа с ним:
//QScopedPointer<XDictWrapper> wrapper;
//wrapper.reset(XDictWrapper::create_wrapper(object));
//wrapper->show_object(this);
//(QScopedPointer удалить объект автоматически)


#include "incl_h.h"
#include "xdict.h"

class QLabel;
class InterfaceItemObject;
class InterfaceGuiObjectVisual;
class XDict;
class InterfaceGuiObject;


//настройки показа объекта
class XDictShowSettings {
public:
    int w = 256;
    int h = 256;
};

//wrapper для работы и показа объекта
class XDictWrapper
{
public:
    //создать wrapper для типа объекта, чтобы затем его вывести в GUI
    //или проделать другие операции
    static XDictWrapper *create_wrapper(XDict *object);

    XDictWrapper(XDict *object);

    XDict *object();

    //показать объект в редакторе
    virtual void show_object(InterfaceGuiObject *item);

    //показать объект в QLabel
    virtual void show_object(QLabel *label, const XDictShowSettings &settings);

protected:
    XDict *object_;
};

#endif // XCLUOBJECTWRAPPER_H
