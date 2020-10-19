#ifndef XCLUOBJECTWRAPPER_H
#define XCLUOBJECTWRAPPER_H

//"Обертка" для XObject.
//Он и его наследники позволяют следующее:
//1. представлять объекты в GUI редактора,
//2. описывать, как хранить настройки показа
//3. получать удобный доступ к параметрам объекта
//4. конвертировать типы Qt, например, изображения, в объект и обратно

//Работа с ним идет путем создания wrapper, который будет привязан к типу объекта,
//и затем работа с ним:
//QScopedPointer<XObjectWrapper> wrapper;
//wrapper.reset(XObjectWrapper::create_wrapper(object));
//wrapper->show_object(this);
//(QScopedPointer удалить объект автоматически)


#include "incl_h.h"
#include "xobject.h"

class QLabel;
class XItemObject;
class XGuiObjectVisual;
class XObject;
class XGuiObject;


//настройки показа объекта
class XObjectShowSettings {
public:
    int w = 256;
    int h = 256;
};

//wrapper для работы и показа объекта
class XObjectWrapper
{
public:
    //создать wrapper для типа объекта, чтобы затем его вывести в GUI
    //или проделать другие операции
    static XObjectWrapper *create_wrapper(const XObject *object);

    XObjectWrapper(const XObject *object);

    const XObject *object();

    //показать объект в редакторе
    virtual void show_object(XGuiObject *item);

    //показать объект в QLabel
    virtual void show_object(QLabel *label, const XObjectShowSettings &settings);

protected:
    const XObject *object_;
};

#endif // XCLUOBJECTWRAPPER_H
