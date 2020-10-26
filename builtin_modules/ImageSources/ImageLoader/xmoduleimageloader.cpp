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
    image_file_ = "";
    image_ = 0;
    need_update_ = false;
}

//---------------------------------------------------------------------
void XModuleImageLoader::impl_update() {
 /*   bool new_frame = 0;

    auto input_source = gete_image_source();
    switch (input_source) {
    case image_source_File: {
        QString image_file = gets_file_name();
        if (image_file != image_file_) {
            load_image_file(image_file);
            //input_image_ = getobject_input_image();
        }
        new_frame = 1;
    }
        break;
    case image_source_Folder: {
        update_folder();
        //input_image_ = getobject_input_image();
        new_frame = 1;
    }
        break;

        break;
     default:
        xclu_exception("Unknown image_source " + getraw_image_source());
    }
*/
}

//---------------------------------------------------------------------
void XModuleImageLoader::load_image_file(QString image_file) {
 /*   image_file_ = image_file;

    QString file_name = rt_path(image_file_);
    XObjectImage::load(getobject_input_image()->write().data(), file_name);
*/
}

//---------------------------------------------------------------------
void XModuleImageLoader::update_folder() {
 /*   //считываем папку
    bool updated = false;
    QString folder = gets_image_folder();
    if (folder != folder_) {
        updated = true;
        folder_ = folder;
        image_files_.clear();
        //scan folder for images
        QDirIterator images_iter(rt_path(folder_),
                                 QStringList() << "*.bmp" << "*.jpg" << "*.png" << "*.tif" << "*.tiff"
                                 ); //, QDirIterator::Subdirectories);
        image_files_.clear();
        while (images_iter.hasNext()) {
            QString image_path = images_iter.next();
            image_files_.push_back(image_path);
            //qDebug() << image_path;
        }
    }

    xclu_assert(!image_files_.isEmpty(), "No images in folder '" + folder_ +"' or folder doesn't exists");

    //считываем картинку
    if (was_changed_folder_index())
    int folder_img = geti_folder_img();
    if (folder_img != folder_img_ || updated) {
        folder_img_ = folder_img;
        int i = folder_img_ % image_files_.size();
        if (i >= 0 && i < image_files_.size()) {
            load_image_file(image_files_[i]);
        }
    }
    */
}

//---------------------------------------------------------------------
void XModuleImageLoader::impl_stop() {

}

//---------------------------------------------------------------------
