#ifndef XMODULEIMAGELOADER_H
#define XMODULEIMAGELOADER_H

//ImageLoader - load imges from a file and a folder

#include <QObject>
#include "xmodule.h"
#include "sdk_h.h"


class XModuleImageLoader: public XModule
{
    Q_OBJECT
public:
    XModuleImageLoader(QString class_name);
    ~XModuleImageLoader();

protected:
#include "auto.h"
    //Выполнение
    virtual void impl_loaded() {}
    virtual void impl_start();
    virtual void impl_update();
    virtual void impl_stop();

    QString image_file_;
    void load_image_file(QString image_file);

    QString folder_;
    QStringList image_files_;
    int folder_img_ = -1;
    void update_folder();

    bool need_update_ = false;
    XProtectedObject *image_ = nullptr;

};

#endif // XMODULEIMAGELOADER_H
