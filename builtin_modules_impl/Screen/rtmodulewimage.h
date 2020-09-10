#ifndef RTMODULEWIMAGE_H
#define RTMODULEWIMAGE_H


//Реализация модуля WImage - показ изображения в окне

#include <QObject>
#include <QScopedPointer>
#include <QMutex>
#include <QWindow>

#include "incl_h.h"
#include "xmodule.h"
#include "xcluprotecteddata.h"
#include "xdict.h"

class QWidget;
class QLabel;


//Данные, которые защищаются с помощью mutex
struct XModuleWImageData: public XcluProtectedData
{
    //int gui_changed = 0;

    void clear() {
        //gui_changed = 0;
    }

};

//Модуль
class XModuleWImage: public XModule
{
    Q_OBJECT
public:
    XModuleWImage();
    ~XModuleWImage();

    static QString *static_class_name_ptr;
    static XModuleWImage *new_module();

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
    QLabel *image_ = nullptr;   //изображение

    XModuleWImageData data_;  //Состояние - например, изменились ли данные, введенные пользователем.

    void create_widget();

    void update_all(bool force);
    void update_value();

    void set_image(const QImage &image);
    void clear_image();

};



#endif // RTMODULEWIMAGE_H
