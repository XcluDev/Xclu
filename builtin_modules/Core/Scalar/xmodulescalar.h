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
#include "xstruct.h"

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
    XModuleScalar(QString class_name);
    ~XModuleScalar();
protected:
#include "auto.h"

    //Выполнение
    virtual void impl_loaded() {}
    virtual void impl_start();
    virtual void impl_update();
    virtual void impl_stop();

    //`create_widget` call implementation, creates QWidget and returns pointer on it
    void *impl_create_widget(QString parent_id);
protected:
    //QScopedPointer<QWindow> window_;
    QString parent_id_;
    bool parent_was_set_ = false;

    QWidget *widget_ = nullptr; //весь виджет
    XcluSpinBox *spin_ = nullptr;

    void update_all(bool force);

    void update_value(bool force);
    void set_value(int v);


    XModuleGuiNumberData data_;  //Состояние - например, изменились ли данные, введенные пользователем.

    void spin_changed();    //вызывается, если значение изменилось

};


#endif // XModuleScalar_H
