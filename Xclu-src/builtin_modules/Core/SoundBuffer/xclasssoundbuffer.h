#ifndef XCLASSSCALAR_H
#define XCLASSSCALAR_H

//Реализация модуля Scalar - скаляр (int, float, string, checkbox, enum),
//в виде поля ввода и/или слайдера

#include <QObject>
#include <QWindow>

#include "sdk_h.h"
#include "xclass.h"
#include "xcluprotecteddata.h"
#include "xdict.h"

class QWidget;
class XcluSpinBox;



//Данные, которые защищаются с помощью mutex
struct XClassGuiNumberData: public XcluProtectedData
{
    int gui_changed = 0;

    void clear() {
        gui_changed = 0;
    }

};

//Модуль
class XClassScalar: public XClass
{
    Q_OBJECT
public:
    XClassScalar(QString class_name);
    virtual ~XClassScalar();
protected:
#include "auto.h"

    //Выполнение
    virtual void on_loaded() {}
    virtual void start();
    virtual void update();
    virtual void stop();

    //`create_widget` call implementation, creates QWidget and returns pointer on it
    void *on_create_widget(QString parent_id);
protected:
    //QScopedPointer<QWindow> window_;
    QString parent_id_;
    bool parent_was_set_ = false;

    QWidget *widget_ = nullptr; //весь виджет
    XcluSpinBox *spin_ = nullptr;

    void update_all(bool force);

    void update_value(bool force);
    void set_value(int v);


    XClassGuiNumberData data_;  //Состояние - например, изменились ли данные, введенные пользователем.

    void spin_changed();    //вызывается, если значение изменилось

};


#endif // XClassScalar_H
