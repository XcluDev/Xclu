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

    static QString *static_class_name_ptr;
    static RtModuleFragmentShader *new_module();

protected:
    //Выполнение
    virtual void loaded_impl() {}
    virtual void start_impl();
    virtual void update_impl();
    virtual void stop_impl();

    //Вызовы
    virtual void call_impl(QString function, XDict *input, XDict * /*output*/);
protected:
    //QScopedPointer<QWindow> window_;
};


#endif // RTMODULEFRAGMENTSHADER_H
