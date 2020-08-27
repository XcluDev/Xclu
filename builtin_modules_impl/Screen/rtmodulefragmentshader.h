#ifndef RTMODULEFRAGMENTSHADER_H
#define RTMODULEFRAGMENTSHADER_H

//Реализация модуля FragmentShader - рисование прямоугольника, пропущенного через фрагментный шейдер, в FBO
//Это FBO можно конвертировать в картинку или использовать как текстуру для вывода в окно

#include <QObject>
#include <QScopedPointer>
#include <QMutex>
#include <QWindow>

#include "incl_h.h"
#include "rtmodule.h"
#include "xcluprotecteddata.h"


//Модуль
class RtModuleFragmentShader: public RtModule
{
    Q_OBJECT
public:
    RtModuleFragmentShader();
    ~RtModuleFragmentShader();

    static QString *static_class_name_ptr; //"FragmentShader", эта переменная используется для создания новых объектов
    static RtModuleFragmentShader *new_module();

protected:
    //Выполнение
    virtual void execute_loaded_internal() {}
    virtual void execute_start_internal();
    virtual void execute_update_internal();
    virtual void execute_stop_internal();

    //Вызовы
    virtual void call_internal(QString function, XcluObject *input, XcluObject * /*output*/);
protected:
    //QScopedPointer<QWindow> window_;
};


#endif // RTMODULEFRAGMENTSHADER_H
