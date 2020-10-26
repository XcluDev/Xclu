#include "qt_widgets.h"
#include "xmoduleimageloader.h"
#include "incl_cpp.h"
#include "registrarxmodule.h"
#include "projectruntime.h"
#include "module.h"
#include "xcluobjectimage.h"

//registering module implementation
REGISTER_XMODULE(ImageLoader)

//---------------------------------------------------------------------
XModuleImageLoader::XModuleImageLoader(QString class_name)
    :XModule(class_name)
{

}

//---------------------------------------------------------------------
XModuleImageLoader::~XModuleImageLoader()
{

}

//---------------------------------------------------------------------
void XModuleImageLoader::impl_start() {
    setobject_image(&image_);
    seti_is_new_frame(false);
}

//---------------------------------------------------------------------
void XModuleImageLoader::impl_update() {
    bool new_frame = false;

    auto input_source = gete_image_source();
    QString image_file;
    switch (input_source) {
    case image_source_File: {
        image_file = gets_file_name();
    }
        break;
    case image_source_Folder: {
        if (was_changed_folder_name()) {
            load_folder(gets_folder_name());
        }
        int index = geti_folder_index();
        if (!image_files_.isEmpty()) {
            int i = index % image_files_.size();
            if (i >= 0 && i < image_files_.size()) {
                image_file = image_files_[i];
            }
        }
    }
        break;
     default:
        xclu_exception("Unknown image_source " + getraw_image_source());
    }

    if (image_file != image_file_) {
        load_image_file(image_file);
        new_frame = true;
    }

    seti_is_new_frame(new_frame);

}

//---------------------------------------------------------------------
void XModuleImageLoader::load_image_file(QString image_file) {
    image_file_ = image_file;
    QString file_name = rt_path(image_file_);
    XObjectImage::load(image_.write().data(), file_name);
}

//---------------------------------------------------------------------
void XModuleImageLoader::load_folder(QString folder_name) {
    image_files_.clear();
    //scan folder for images
    QDirIterator images_iter(rt_path(folder_name),
                             QStringList() << "*.bmp" << "*.jpg" << "*.png" << "*.tif" << "*.tiff"
                             ); //, QDirIterator::Subdirectories);
    image_files_.clear();
    while (images_iter.hasNext()) {
        QString image_path = images_iter.next();
        image_files_.push_back(image_path);
        //qDebug() << image_path;
    }

    xclu_assert(!image_files_.isEmpty(), "No images in folder '" + folder_name +"' or folder doesn't exists");
}

//---------------------------------------------------------------------
void XModuleImageLoader::impl_stop() {

}

//---------------------------------------------------------------------
