#include "xmodulefacedetect.h"
#include "incl_cpp.h"
#include "registrarxmodule.h"
#include "project_props.h"
#include "xobjectimage.h"
#include "xdrawhelper.h"
#include "xcvhelper.h"

#include <opencv2/imgproc/imgproc.hpp>


REGISTER_XMODULE(FaceDetect)

//---------------------------------------------------------------------
XModuleFaceDetect::XModuleFaceDetect(QString class_name)
    :XModule(class_name)
{

}

//---------------------------------------------------------------------
XModuleFaceDetect::~XModuleFaceDetect()
{

}

//---------------------------------------------------------------------
void XModuleFaceDetect::on_loaded() {

}

//---------------------------------------------------------------------
//нажатие кнопки, даже когда модуль остановлен - модуль также должен переопределить эту функцию
//внимание, обычно вызывается из основного потока как callback
void XModuleFaceDetect::on_button_pressed(QString /*button_id*/) {
    //if (button_id == "print_devices") {
    //}
}


//---------------------------------------------------------------------
void XModuleFaceDetect::start() {
    haar_load(xc_absolute_path_from_project(gets_cascade_file()));
}

//---------------------------------------------------------------------
void XModuleFaceDetect::update() {
    auto mode = gete_processing_mode();
    if (mode == processing_mode_Each_Frame
            || (mode == processing_mode_On_Checkbox && geti_process_new_frame())) {
        haar_search();
    }
}

//---------------------------------------------------------------------
void XModuleFaceDetect::stop() {
    haar_unload();

    seti_face_count(0);
    blobs_.clear();
    update_biggest();
}


//---------------------------------------------------------------------
void XModuleFaceDetect::draw(QPainter &painter, int w, int h) {
    if (!geti_draw_enabled()) {
        return;
    }

    auto image_read = getobject_input_image()->read();
    const XObject *object = image_read.pointer();
    auto rect = XDrawHelper::draw_XObject_fit(object, getf_draw_x(), getf_draw_y(), getf_draw_size(), painter, w, h);

    QPen pen(QColor(255,255,0));
    pen.setWidth(3);
    painter.setPen(pen);
    painter.setBrush(Qt::NoBrush);

    if (!rect.isEmpty()) {
        for (auto &b: blobs_) {
            auto &r = b.rect;
            painter.drawRect(QRectF(r.x() * rect.width() + rect.x(),
                                    r.y() * rect.height() + rect.y(),
                                    r.width() * rect.width(),
                                    r.height() * rect.height()));

        }
    }
}

//---------------------------------------------------------------------
void XModuleFaceDetect::haar_load(QString file_name) {
    haar_unload();

    xc_assert(face_cascade_.load(file_name.toStdString()),
            "haar_load error - can't load from `" + file_name
              + "`. Please check that path contains Latin-only symbols.");
}

//---------------------------------------------------------------------
void XModuleFaceDetect::haar_unload() {
    //face_cascade_.... TODO now not deleting here, for fix may use scoped pointer

}

//---------------------------------------------------------------------
void XModuleFaceDetect::haar_search() {
    if (face_cascade_.empty()) {
        seti_face_count(0);
        return;
    }

    blobs_.clear();

    auto read = getobject_input_image()->read();
    cv::Mat img = XCvHelper::link_to_cv(read.data());
    if (img.empty()) {
        seti_face_count(0);
        return;
    }

    int w = img.size().width;
    int h = img.size().height;
    //img.setROI(x, y, w, h);

    cv::Mat gray;
    cv::cvtColor(img, gray, CV_BGR2GRAY);

    cv::equalizeHist(gray, gray);    //Equalize histogram //TODO make as an option

    // Parameters

    // The default value is 1.2. For accuracy, bring it closer but not equal to 1.0. To make it faster, use a larger value.
    float haar_scale = getf_haar_scale(); //1.1f; //1.2;

    // How many neighbors can be grouped into a face? Default value is 2. If set to 0, no grouping will be done.
    int haar_neighbors = geti_haar_neighbors(); //3; //2;

    // Flags
    /*
    Flags:
    CV_HAAR_DO_CANNY_PRUNING        Regions without edges are ignored.
    CV_HAAR_SCALE_IMAGE            Scale the image rather than the detector (sometimes yields speed increases).
    CV_HAAR_FIND_BIGGEST_OBJECT    Only return the largest result.
    CV_HAAR_DO_ROUGH_SEARCH       When BIGGEST_OBJECT is enabled, stop at the first scale for which multiple results are found.
    */
    int flags = CV_HAAR_DO_CANNY_PRUNING * geti_haar_canny_pruning()
            + CV_HAAR_SCALE_IMAGE * geti_haar_scale_image()
            + CV_HAAR_FIND_BIGGEST_OBJECT * geti_haar_only_biggest_face()
            + CV_HAAR_DO_ROUGH_SEARCH * geti_haar_only_biggest_face() * geti_haar_rough_search();

    int min_width =  getf_face_min_size() * w;
    int min_height =  getf_face_min_size() * h;

    //max size - now not using

    std::vector<cv::Rect> faces;
    face_cascade_.detectMultiScale(gray, faces, haar_scale, haar_neighbors, flags, cv::Size(min_width, min_height));
    int n = faces.size();
    blobs_.resize(n);
    for (int i = 0; i < n; i++) {
        auto &face = faces[i];
        blobs_[i] = FaceBlob(QRectF(float(face.x)/w, float(face.y)/h,
                                    float(face.width)/w, float(face.height)/h));
    }

    // sort the pointers based on size
    //if( blobs.size() > 1 ) {
    //    sort( blobs.begin(), blobs.end(), sort_carea_compare );
    //}

    seti_face_count(n);
    update_biggest();
}

//---------------------------------------------------------------------
void XModuleFaceDetect::update_biggest() {
    int n = blobs_.size();
    if (n == 0) {
        setf_biggest_cx(0.5);
        setf_biggest_cy(0.5);
        return;
    }
    float barea = -1;
    int besti = 0;
    for (int i=0; i<n; i++) {
        float area = blobs_[i].area();
        if (area > barea) {
            barea = area;
            besti = i;
        }
    }
    auto pos = blobs_[besti].center();
    setf_biggest_cx(pos.x);
    setf_biggest_cy(pos.y);

}


//---------------------------------------------------------------------


