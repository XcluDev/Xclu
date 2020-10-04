#ifndef RTMODULEWIMAGE_H
#define RTMODULEWIMAGE_H


//Реализация модуля WImage - показ изображения в окне

#include <QObject>
#include <QWindow>

#include "sdk_h.h"
#include "xmodule.h"
#include "xcluprotecteddata.h"
#include "xstruct.h"

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
    XModuleWImage(QString class_name);
    ~XModuleWImage();
protected:
#include "auto.h"

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
    QLabel *image_ = nullptr;   //изображение

    XModuleWImageData data_;  //Состояние - например, изменились ли данные, введенные пользователем

    void update_all(bool force);
    void update_value();

    void set_image(const QImage &image);
    void clear_image();

};



#endif // RTMODULEWIMAGE_H
