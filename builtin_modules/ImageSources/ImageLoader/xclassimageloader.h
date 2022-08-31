#pragma once

//ImageLoader - load imges from a file and a folder

#include <QObject>
#include "xclass.h"
#include "sdk_h.h"


class XClassImageLoader: public XClass
{
    Q_OBJECT
public:
    XClassImageLoader(QString class_name);
    virtual ~XClassImageLoader();

protected:
#include "auto.h"
    //Выполнение
    virtual void on_loaded() {}
    virtual void start();
    virtual void update();
    virtual void stop();

    QString image_file_;
    void load_image_file(QString image_file);

    QStringList image_files_;
    void load_folder(QString folder_name);

    XRaster image_holder_;

};

