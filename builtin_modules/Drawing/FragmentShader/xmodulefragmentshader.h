#ifndef XMODULEFRAGMENTSHADER_H
#define XMODULEFRAGMENTSHADER_H

//Реализация модуля FragmentShader - рисование прямоугольника, пропущенного через фрагментный шейдер, в FBO
//Это FBO можно конвертировать в картинку или использовать как текстуру для вывода в окно

#include <QObject>
#include <QWindow>

#include "sdk_h.h"
#include "xclass.h"
#include "xprotecteddata.h"


//Модуль
class XModuleFragmentShader: public XModule
{
    Q_OBJECT
public:
    XModuleFragmentShader(QString class_name);
    virtual ~XModuleFragmentShader();
protected:
#include "auto.h"

    //Выполнение
    virtual void on_loaded() {}
    virtual void start();
    virtual void update();
    virtual void stop();

    //Вызовы
    //virtual void on_custom_call(QString function, XObject *input, XObject * /*output*/);
protected:
    //QScopedPointer<QWindow> window_;
};


#endif // XMODULEFRAGMENTSHADER_H
