#ifndef XCLUOBJECTWRAPPER_H
#define XCLUOBJECTWRAPPER_H

//"Обертка" для XcluObject.
//Он и его наследники позволяют следующее:
//1. представлять объекты в GUI редактора,
//2. описывать, как хранить настройки показа
//3. получать удобный доступ к параметрам объекта
//4. конвертировать типы Qt, например, изображения, в объект и обратно

//Работа с ним идет путем создания wrapper, который будет привязан к типу объекта,
//и затем работа с ним:
//QScopedPointer<XcluObjectWrapper> wrapper;
//wrapper.reset(XcluObjectWrapper::create_wrapper(object));
//wrapper->show_object(this);
//(QScopedPointer удалить объект автоматически)


#include "incl_h.h"
#include "xcluobject.h"

class QLabel;
class InterfaceItemObject;
class InterfaceGuiObjectVisual;
class XcluObject;
class InterfaceGuiObject;


//настройки показа объекта
class XcluObjectShowSettings {
public:
    int w = 256;
    int h = 256;
};

//wrapper для работы и показа объекта
class XcluObjectWrapper
{
public:
    //создать wrapper для типа объекта, чтобы затем его вывести в GUI
    //или проделать другие операции
    static XcluObjectWrapper *create_wrapper(XcluObject *object);

    XcluObjectWrapper(XcluObject *object);

    XcluObject *object();

    //показать объект в редакторе
    virtual void show_object(InterfaceGuiObject *item);

    //показать объект в QLabel
    virtual void show_object(QLabel *label, const XcluObjectShowSettings &settings);

protected:
    XcluObject *object_;
};

#endif // XCLUOBJECTWRAPPER_H
