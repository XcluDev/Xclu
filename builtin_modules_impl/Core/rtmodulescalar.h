#ifndef RTMODULESCALAR_H
#define RTMODULESCALAR_H

//Реализация модуля Scalar - скаляр (int, float, string, checkbox, enum),
//в виде поля ввода и/или слайдера

#include <QObject>
#include <QScopedPointer>
#include <QMutex>
#include <QWindow>

#include "incl_h.h"
#include "xmodule.h"
#include "xcluprotecteddata.h"
#include "xdict.h"

class QWidget;
class XcluSpinBox;



//Данные, которые защищаются с помощью mutex
struct XModuleGuiNumberData: public XcluProtectedData
{
    int gui_changed = 0;

    void clear() {
        gui_changed = 0;
    }

};

//Модуль
class XModuleScalar: public XModule
{
    Q_OBJECT
public:
    XModuleScalar();
    ~XModuleScalar();

    static QString *static_class_name_ptr;
    static XModuleScalar *new_module();

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
    QString parent_id_;
    bool parent_was_set_ = false;

    QWidget *widget_ = nullptr; //весь виджет
    XcluSpinBox *spin_ = nullptr;

    void create_widget();


    void update_all(bool force);

    void update_value(bool force);
    void set_value(int v);
    enum Source : int {
        Source_Fixed_Value = 0, Source_GUI = 1, Source_Other_Module_Value = 2, Source_Expression = 3
    };
    Source get_source();

    XModuleGuiNumberData data_;  //Состояние - например, изменились ли данные, введенные пользователем.

    void spin_changed();    //вызывается, если значение изменилось

};


#endif // XModuleScalar_H
