#include "xclassfacedetect.h"
#include "incl_cpp.h"
#include "registrarxclass.h"
#include "project_props.h"
#include "xobjectvis.h"
#include "xdrawhelper.h"
#include "xcvhelper.h"

#include <opencv2/imgproc/imgproc.hpp>


REGISTER_XCLASS(FaceDetect)

//---------------------------------------------------------------------
XClassFaceDetect::XClassFaceDetect(QString class_name)
    :XClass(class_name)
{

}

//---------------------------------------------------------------------
XClassFaceDetect::~XClassFaceDetect()
{

}

//---------------------------------------------------------------------
void XClassFaceDetect::on_loaded() {

}

//---------------------------------------------------------------------
//нажатие кнопки, даже когда модуль остановлен - модуль также должен переопределить эту функцию
//внимание, обычно вызывается из основного потока как callback
void XClassFaceDetect::on_button_pressed(QString /*button_id*/) {
    //if (button_id == "print_devices") {
    //}
}


//---------------------------------------------------------------------
void XClassFaceDetect::start() {
    haar_load(xc_absolute_path_from_project(gets_cascade_file()));
    clear_results();
}


//---------------------------------------------------------------------
void XClassFaceDetect::clear_results() {
    seti_face_count(0);
    blobs_.clear();
    raw_blobs_.clear();
    update_biggest();
    last_time_ = 0;
}

//---------------------------------------------------------------------
void XClassFaceDetect::update() {
    auto mode = gete_processing_mode();
    bool new_image =
            (mode == processing_mode_On_Checkbox && geti_process_new_frame())
            || (mode == processing_mode_On_Change && input_image_was_changed());

    // processing
    if (mode == processing_mode_Each_Frame
            || new_image) {
        haar_search();
        last_time_ = 0;
    }
    else {
        last_time_ += xc_dt();
    }

    // if no new image - clear results
    if ((mode == processing_mode_On_Checkbox || mode == processing_mode_On_Change)
            && geti_auto_clear_if_no_data()
            && last_time_ >= geti_auto_clear_sec()) {
        clear_results();
    }

}

//---------------------------------------------------------------------
bool XClassFaceDetect::input_image_was_changed() {
    return getobject_input_image()->was_changed(image_changed_checker_);
}

//---------------------------------------------------------------------
void XClassFaceDetect::stop() {
    haar_unload();

    clear_results();
}


//---------------------------------------------------------------------
void XClassFaceDetect::draw(QPainter &painter, int w, int h) {
    if (!geti_draw_enabled()) {
        return;
    }

    auto image_read = getobject_input_image()->read();
    const XObject *object = image_read.pointer();
    auto rect = XDrawHelper::draw_XObject_fit(object, getf_draw_x(), getf_draw_y(), getf_draw_size(), painter, w, h);


    if (!rect.isEmpty()) {
        {   // raw blobs
            QPen pen(QColor(0,255,0));
            pen.setWidth(1);
            painter.setPen(pen);
            painter.setBrush(Qt::NoBrush);
            if (geti_draw_raw_blobs()) {
                for (auto &b: raw_blobs_) {
                    auto &r = b.rect;
                    painter.drawRect(QRectF(r.x() * rect.width() + rect.x(),
                                            r.y() * rect.height() + rect.y(),
                                            r.width() * rect.width(),
                                            r.height() * rect.height()));

                }
            }
        }

        QPen pen(QColor(255,255,0));
        pen.setWidth(3);
        painter.setPen(pen);
        painter.setBrush(Qt::NoBrush);
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
void XClassFaceDetect::haar_load(QString file_name) {
    haar_unload();

    xc_assert(face_cascade_.load(file_name.toStdString()),
            "haar_load error - can't load from `" + file_name
              + "`. Please check that path contains Latin-only symbols.");
}

//---------------------------------------------------------------------
void XClassFaceDetect::haar_unload() {
    //face_cascade_.... TODO now not deleting here, for fix may use scoped pointer

}

//---------------------------------------------------------------------
void XClassFaceDetect::haar_search() {
    if (face_cascade_.empty()) {
        seti_face_count(0);
        return;
    }

    blobs_.clear();

    auto read = getobject_input_image()->read();
    const XObject *obj = read.pointer();
    cv::Mat img = XCvHelper::link_to_cv(obj);
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
    raw_blobs_.clear(); // Used for thresholding as debug blobs
    for (int i = 0; i < n; i++) {
        auto &face = faces[i];
        blobs_[i] = FaceBlob(QRect(face.x, face.y, face.width, face.height), w, h);
    }


    //Thresholding
    apply_thresholding(w, h);

    // sort the pointers based on size
    //if( blobs.size() > 1 ) {
    //    sort( blobs.begin(), blobs.end(), sort_carea_compare );
    //}

    seti_face_count(blobs_.size());
    update_biggest();
}

//---------------------------------------------------------------------
void XClassFaceDetect::update_biggest() {
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
// Apply threshold and create only one blob; all blobs_ are copyed to raw_blobs_ for debug drawing.
void XClassFaceDetect::apply_thresholding(int w0, int h0) {
    if (blobs_.isEmpty()) return;
    if (!(geti_haar_neighbors() == 0 && geti_haar_apply_threshold())) return;

    int shrink = geti_haar_shrink_res();
    int w = w0 / shrink;
    int h = h0 / shrink;
    xc_assert(w > 0 && h > 0, "Too much shrinking in face detection");

    raw_blobs_ = blobs_;
    blobs_.clear();

    accum_image_.resize(w*h);
    accum_image_.fill(0);
    for (auto &b: raw_blobs_) {
        auto &r = b.recti;
        int x0 = xclampi(r.x()/shrink, 0, w-1);
        int y0 = xclampi(r.y()/shrink, 0, h-1);
        int x1 = xclampi((r.x()+r.width())/shrink, 0, w);
        int y1 = xclampi((r.y()+r.height())/shrink, 0, h);
        for (int y=y0; y<y1; y++) {
            for (int x=x0; x<x1; x++) {
                accum_image_[x + w*y]++;
            }
        }
    }

    // Search boundary box exceeding threshold
    int thresh = geti_haar_threshold();
    int bx0 = w;
    int by0 = h;
    int bx1 = 0;
    int by1 = 0;
    for (int y=0; y<h; y++) {
        for (int x=0; x<w; x++) {
            if (accum_image_[x+w*y] >= thresh) {
                bx0 = qMin(bx0, x);
                by0 = qMin(by0, y);
                bx1 = qMax(bx1, x);
                by1 = qMax(by1, y);
            }
        }
    }
    // Something is found
    if (bx0 <= bx1 && by0 <= by1) {
        int x0 = xclampi(bx0*shrink, 0, w0-1);
        int y0 = xclampi(by0*shrink, 0, h0-1);
        int x1 = xclampi(bx1*shrink, 0, w0-1);
        int y1 = xclampi(by1*shrink, 0, h0-1);
        FaceBlob blob(QRect(x0, y0, x1-x0+1, y1-y0+1), w0, h0);
        blobs_.append(blob);
    }
}

//---------------------------------------------------------------------


