#pragma once

// Реализация модуля WImage - показ изображения в окне
// TODO WImage сейчас закомментирован

#include <QObject>
#include <QWindow>

#include "sdk_h.h"
#include "xclass.h"
#include "xprotecteddata.h"
#include "xobject.h"

class QWidget;
class QLabel;


//Модуль
class XClassWImage: public XClass
{
    Q_OBJECT
public:
    XClassWImage(QString class_name);
    virtual ~XClassWImage();
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
    /*
    QString parent_id_;
    bool parent_was_set_ = false;

    QWidget *widget_ = nullptr; //весь виджет
    QLabel *image_label_ = nullptr;   //изображение
    */
    void update_all(bool force);
    void update_value();

    void set_image(const QImage &image);
    void clear_image();

};
