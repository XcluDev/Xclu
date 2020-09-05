#ifndef RTMODULESCALAR_H
#define RTMODULESCALAR_H

//Реализация модуля Scalar - скаляр (int, float, string, checkbox, enum),
//в виде поля ввода и/или слайдера

#include <QObject>
#include <QScopedPointer>
#include <QMutex>
#include <QWindow>

#include "incl_h.h"
#include "rtmodule.h"
#include "xcluprotecteddata.h"
#include "xdict.h"

class QWidget;
class XcluSpinBox;



//Данные, которые защищаются с помощью mutex
struct RtModuleGuiNumberData: public XcluProtectedData
{
    int gui_changed = 0;

    void clear() {
        gui_changed = 0;
    }

};

//Модуль
class RtModuleScalar: public RtModule
{
    Q_OBJECT
public:
    RtModuleScalar();
    ~RtModuleScalar();

    static QString *static_class_name_ptr;
    static RtModuleScalar *new_module();

protected:
    //Выполнение
    virtual void execute_loaded_internal() {}
    virtual void execute_start_internal();
    virtual void execute_update_internal();
    virtual void execute_stop_internal();

    //Вызовы
    virtual void call_internal(QString function, XDict *input, XDict * /*output*/);
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

    RtModuleGuiNumberData data_;  //Состояние - например, изменились ли данные, введенные пользователем.

    void spin_changed();    //вызывается, если значение изменилось

};


#endif // RtModuleScalar_H
