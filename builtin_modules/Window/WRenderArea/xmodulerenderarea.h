#ifndef XMODULEXUIIMAGE_H
#define XMODULEXUIIMAGE_H

//XUI image

#include <QObject>
#include <QWindow>

#include "sdk_h.h"
#include "xmodule.h"
#include "xprotecteddata.h"
#include "xobject.h"

class QWidget;
class QLabel;

class XModuleWImage: public XModule
{
    Q_OBJECT
public:
    XModuleWImage(QString class_name);
    ~XModuleWImage();
protected:
#include "auto.h"

    virtual void on_loaded() {}
    virtual void start();
    virtual void update();
    virtual void stop();

    //`create_widget` call implementation, creates QWidget and returns pointer on it
    void *on_create_widget(QString parent_id);

    virtual void on_reset_widget();


protected:
    //QScopedPointer<QWindow> window_;
    QString parent_id_;
    bool parent_was_set_ = false;

    QWidget *widget_ = nullptr; //весь виджет
    QLabel *image_label_ = nullptr;   //изображение

    XModuleWImageData data_;  //Состояние - например, изменились ли данные, введенные пользователем

    void update_all(bool force);
    void update_value();

    void set_image(const QImage &image);
    void clear_image();

};



#endif // XMODULEXUIIMAGE_H
