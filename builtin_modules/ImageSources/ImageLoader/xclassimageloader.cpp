#include "qt_widgets.h"
#include "xclassimageloader.h"
#include "incl_cpp.h"
#include "registrarxclass.h"
#include "project_props.h"
#include "xclass.h"
#include "xobjectvis.h"

//registering module implementation
REGISTER_XCLASS(ImageLoader)

//---------------------------------------------------------------------
XClassImageLoader::XClassImageLoader(QString class_name)
    :XClass(class_name)
{

}

//---------------------------------------------------------------------
XClassImageLoader::~XClassImageLoader()
{

}

//---------------------------------------------------------------------
void XClassImageLoader::start() {
    getobject_image()->write().data().link<XRaster>(image_holder_);   //link xgui image with image_
    seti_is_new_frame(false);

    //load image immediately ! :)
    update();
}

//---------------------------------------------------------------------
void XClassImageLoader::update() {
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
        xc_exception("Unknown image_source " + getraw_image_source());
    }

    if (image_file != image_file_) {
        load_image_file(image_file);
        new_frame = true;
    }

    seti_is_new_frame(new_frame);

}

//---------------------------------------------------------------------
void XClassImageLoader::load_image_file(QString image_file) {
    image_file_ = image_file;
    QString file_name = xc_absolute_path_from_project(image_file_);

    XRasterUtils::load(*getobject_image()->write().data().data<XRaster>(), file_name);
}

//---------------------------------------------------------------------
void XClassImageLoader::load_folder(QString folder_name) {
    image_files_ = xc_folder_list_files(folder_name, QStringList() << "bmp" << "jpg" << "png" << "tif" << "tiff");
    xc_assert(!image_files_.isEmpty(), "No images in folder '" + folder_name +"' or folder doesn't exists");
}

//---------------------------------------------------------------------
void XClassImageLoader::stop() {

}

//---------------------------------------------------------------------
