#ifndef RTMODULEWNUMBER_H
#define RTMODULEWNUMBER_H

//Реализация модуля WNumber - целочисленная переменная в окне, в виде поля ввода и/или слайдера

#include <QObject>
#include <QScopedPointer>
#include <QMutex>
#include <QWindow>

#include "incl_qt.h"
#include "rtmodule.h"
#include "xcluprotecteddata.h"
#include "xcluobject.h"

class QWidget;
class XcluSpinBox;



//Данные, которые защищаются с помощью mutex
struct RtModuleWIntData: public XcluProtectedData
{
    int gui_changed = 0;

    void clear() {
        gui_changed = 0;
    }

};

//Модуль
class RtModuleWNumber: public RtModule
{
    Q_OBJECT
public:
    RtModuleWNumber();
    ~RtModuleWNumber();

    static QString *static_class_name_ptr; //"WNumber", эта переменная используется для создания новых объектов
    static RtModuleWNumber *new_module();

protected:
    //Выполнение
    virtual void execute_start_internal();
    virtual void execute_update_internal();
    virtual void execute_stop_internal();

    //Вызовы
    virtual void call_internal(QString function, XcluObject *input, XcluObject * /*output*/);
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

    RtModuleWIntData data_;  //Состояние - например, изменились ли данные, введенные пользователем.

    void spin_changed();    //вызывается, если значение изменилось

};


#endif // RTMODULEWNUMBER_H
