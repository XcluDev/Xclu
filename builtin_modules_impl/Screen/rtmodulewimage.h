#ifndef RTMODULEWIMAGE_H
#define RTMODULEWIMAGE_H


//Реализация модуля WImage - показ изображения в окне

#include <QObject>
#include <QScopedPointer>
#include <QMutex>
#include <QWindow>

#include "incl_qt.h"
#include "rtmodule.h"
#include "xcluprotecteddata.h"
#include "xcluobject.h"

class QWidget;
class QLabel;


//Данные, которые защищаются с помощью mutex
struct RtModuleWImageData: public XcluProtectedData
{
    //int gui_changed = 0;

    void clear() {
        //gui_changed = 0;
    }

};

//Модуль
class RtModuleWImage: public RtModule
{
    Q_OBJECT
public:
    RtModuleWImage();
    ~RtModuleWImage();

    static QString *static_class_name_ptr; //"IntGui", эта переменная используется для создания новых объектов
    static RtModuleWImage *new_module();

protected:
    //Выполнение
    virtual void execute_start_internal();
    virtual void execute_update_internal();
    virtual void execute_stop_internal();

    //Вызовы
    virtual void call_internal(QString function, XcluObject *input, XcluObject * /*output*/);
protected:
    //QScopedPointer<QWindow> window_;
    QString parent_name_;
    bool parent_was_set_ = false;

    QWidget *widget_ = nullptr; //весь виджет
    QLabel *image_ = nullptr;   //изображение

    RtModuleWImageData data_;  //Состояние - например, изменились ли данные, введенные пользователем.

    void create_widget();

    void update_all(bool force);
    void update_value();

    void set_image(const QImage &image);
    void clear_image();

};



#endif // RTMODULEWIMAGE_H
