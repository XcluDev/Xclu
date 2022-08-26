#ifndef XMODULEIMAGELOADER_H
#define XMODULEIMAGELOADER_H

//ImageLoader - load imges from a file and a folder

#include <QObject>
#include "xclass.h"
#include "sdk_h.h"


class XModuleImageLoader: public XModule
{
    Q_OBJECT
public:
    XModuleImageLoader(QString class_name);
    virtual ~XModuleImageLoader();

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

    XProtectedObject image_;

};

#endif // XMODULEIMAGELOADER_H
