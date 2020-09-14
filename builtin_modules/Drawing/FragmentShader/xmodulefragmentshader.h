#ifndef RTMODULEFRAGMENTSHADER_H
#define RTMODULEFRAGMENTSHADER_H

//Реализация модуля FragmentShader - рисование прямоугольника, пропущенного через фрагментный шейдер, в FBO
//Это FBO можно конвертировать в картинку или использовать как текстуру для вывода в окно

#include <QObject>
#include <QScopedPointer>
#include <QMutex>
#include <QWindow>

#include "incl_h.h"
#include "xmodule.h"
#include "xcluprotecteddata.h"


//Модуль
class XModuleFragmentShader: public XModule
{
    Q_OBJECT
public:
    XModuleFragmentShader();
    ~XModuleFragmentShader();

    static QString *static_class_name_ptr;
    static XModuleFragmentShader *new_module();

protected:
#include "auto.h"

    //Выполнение
    virtual void impl_loaded() {}
    virtual void impl_start();
    virtual void impl_update();
    virtual void impl_stop();

    //Вызовы
    virtual void impl_call(QString function, XDict *input, XDict * /*output*/);
protected:
    //QScopedPointer<QWindow> window_;
};


#endif // RTMODULEFRAGMENTSHADER_H
