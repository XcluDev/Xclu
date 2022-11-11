#include "xclassmotiondetectorrouter.h"
#include "incl_cpp.h"
#include "registrarxclass.h"
#include "project_props.h"
#include "xobjectvis.h"

//registering module implementation
REGISTER_XCLASS(MotionDetectorRouter)

//---------------------------------------------------------------------
XClassMotionDetectorRouter::XClassMotionDetectorRouter(QString class_name)
    :XClass(class_name)
{

}

//---------------------------------------------------------------------
XClassMotionDetectorRouter::~XClassMotionDetectorRouter()
{

}

//---------------------------------------------------------------------
void XClassMotionDetectorRouter::start() {
    //link images with internal objects
    setobject_output1(output_gui_[0]);
    setobject_output2(output_gui_[1]);
    setobject_output3(output_gui_[2]);
    setobject_output4(output_gui_[3]);

    setobject_template1(template_gui_[0]);
    setobject_template2(template_gui_[1]);
    setobject_template3(template_gui_[2]);
    setobject_template4(template_gui_[3]);

    //clear images and set to objects
    for (int i=0; i<N; i++) {
        output_[i].clear();
        template_[i].clear();
        output_gui_[i].write().data().link(output_[i]);
        template_gui_[i].write().data().link(template_[i]);
    }

    ignore_frames_ = geti_ignore_start_frames();
    started_ = 0;
    seti_started(started_);

    n_ = geti_inputs();
}

//---------------------------------------------------------------------
XProtectedObject *XClassMotionDetectorRouter::input_image(int i) {
    xc_assert(xinrangei_excl(i, 0, n_), "Internal error - bad index at XClassMotionDetectorRouter::input_image");
    if (i == 0) return getobject_input1();
    if (i == 1) return getobject_input2();
    if (i == 2) return getobject_input3();
    if (i == 3) return getobject_input4();
    xc_exception("Internal error - bad index at XClassMotionDetectorRouter::input_image");
    return nullptr;
}

//---------------------------------------------------------------------
XProtectedObject *XClassMotionDetectorRouter::output_image(int i) {
    xc_assert(xinrangei_excl(i, 0, n_), "Internal error - bad index at XClassMotionDetectorRouter::output_image");
    if (i == 0) return getobject_output1();
    if (i == 1) return getobject_output2();
    if (i == 2) return getobject_output3();
    if (i == 3) return getobject_output4();
    xc_exception("Internal error - bad index at XClassMotionDetectorRouter::output_image");
    return nullptr;
}

//---------------------------------------------------------------------
XProtectedObject *XClassMotionDetectorRouter::template_image(int i) {
    xc_assert(xinrangei_excl(i, 0, n_), "Internal error - bad index at XClassMotionDetectorRouter::template_image");
    if (i == 0) return getobject_template1();
    if (i == 1) return getobject_template2();
    if (i == 2) return getobject_template3();
    if (i == 3) return getobject_template4();
    xc_exception("Internal error - bad index at XClassMotionDetectorRouter::template_image");
    return nullptr;
}

//---------------------------------------------------------------------
//automatic route setup if required
void XClassMotionDetectorRouter::make_route() {
    route_scheme_.resize(n_);

    auto route_method = gete_route_method();
    if (route_method == route_method_Manual) {
        //parse manual route
        QString route_str = gets_route_manual();
        QStringList route = route_str.split(" ");
        xc_assert(route.size() >= n_, "Too short route string '" + route_str + "', expected such as '1 2 3 4'");
        for (int i=0; i<n_; i++) {
            route_scheme_[i] = route[i].toInt() - 1;
            xc_assert(xinrangei_excl(route_scheme_[i],0,n_), "Bad index in route '" + route_str + "', must be 1..Inputs");
        }
    }
    //automatic
    if (route_method == route_method_Using_Templates) {
        route_scheme_ = auto_route();
        //output to interface
        QString line;
        for (int i=0; i<n_; i++) {
            if (!line.isEmpty()) line += " ";
            line += QString::number(route_scheme_[i]+1);
        }
        sets_route_template(line);
        xc_console_append("auto route: " + line);
    }

    //Perform routing
    for (int i=0; i<n_; i++) {
        int index = route_scheme_[i];
        xc_assert(xinrangei_excl(index, 0, n_), "Internal error, bad index in route");

        if (i == 0) setobject_output1(input_image(index));
        if (i == 1) setobject_output2(input_image(index));
        if (i == 2) setobject_output3(input_image(index));
        if (i == 3) setobject_output4(input_image(index));
    }

}

//---------------------------------------------------------------------
void XClassMotionDetectorRouter::update() {
    //check starting
    if (ignore_frames_ > 0) {
        ignore_frames_--;
    }
    if (ignore_frames_ == 0 && !started_) {
        started_ = 1;
        seti_started(started_);
        //automatic route setup if required
        make_route();
    }

    if (started_) {
        //ready to save templates
        if (geti_save_templates()) {
            save_templates();
        }
    }
}

//---------------------------------------------------------------------
QVector<int> XClassMotionDetectorRouter::auto_route() {
    //TODO may load at very start for smoother interface...
    load_templates();

    //write to route_scheme
    QVector<int> scheme(n_);

    //default
    for (int i=0; i<n_; i++) {
        scheme[i] = i;
    }

    //build correlation matrix
    xc_console_append("Correlations:");
    QVector<QVector<double>> corr(n_);
    for (int i=0; i<n_; i++) {
        corr[i].resize(n_);
    }

    for (int i=0; i<n_; i++) {
        for (int j=0; j<n_; j++) {
            XRaster templ_float = resize_to_template_float(template_image(i));
            XRaster input_float = resize_to_template_float(input_image(j));
            corr[i][j] = normalized_correlation_float(input_float, templ_float);
            xc_console_append(QString("%1->%2:  %3").arg(i+1).arg(j+1).arg(corr[i][j]));
        }
    }

    //create the best, greedy algorithm
    //TODO can make totl optimum, not greedy
    QVector<int> free(n_, 1);
    for (int i=0; i<n_; i++) {
        double best = -10;
        int bestj = -1;
        for (int j=0; j<n_; j++) {
            if (free[j] && corr[i][j] > best) {
                best = corr[i][j];
                bestj = j;
            }
        }
        xc_assert(bestj >= 0, "Internal error in auto_route");
        free[bestj] = 0;
        scheme[i] = bestj;
    }



    return scheme;
}


//---------------------------------------------------------------------
XRaster XClassMotionDetectorRouter::resize_to_template_float(XProtectedObject *image) {
    //read image
    XRaster raster_u8;
    {
        auto read = image->read();
        auto *raster = read.data().data<XRaster>();

        //no image yet
        xc_assert(raster && !raster->is_empty(), "XClassMotionDetectorRouter::resize_to_template_float: Input is not image");

        XRasterUtils::convert(*raster, raster_u8, XType::u8);
    }

    int w = raster_u8.w;
    int h = raster_u8.h;

    int w1 = geti_templ_w();
    int h1 = geti_templ_h();
    XRaster out_f;
    XRaster counter_i32;
    out_f.allocate(w1, h1, XType::float32);
    counter_i32.allocate(w1, h1, XType::int32);

    //sum
    for (int y=0; y<h; y++) {
        for (int x=0; x<w; x++) {
            int x1 = x * w1 / w;
            int y1 = y * h1 / h;
            out_f.pixel_unsafe<float>(x1, y1) += raster_u8.pixel_unsafe<u8>(x, y) / 256.0;
            counter_i32.pixel_unsafe<int32>(x1, y1)++;
        }
    }

    //result
    for (int i=0; i<w1*h1; i++) {
        int c = counter_i32.pixel_unsafe<int32>(i);
        if (c>0) {
            out_f.pixel_unsafe<float>(i) /= c;
        }
    }

    return out_f;
}

//---------------------------------------------------------------------
float XClassMotionDetectorRouter::normalized_correlation_float(XRaster &A, XRaster &B) {
    A.assert_type(XType::float32);
    B.assert_type(XType::float32);
    int w = A.w;
    int h = A.h;
    xc_assert(w == B.w && h == B.h, "normalized_correlation_float - different sizes");
    double mA = 0;
    double mB = 0;
    for (int i=0; i<w*h; i++) {
        mA += A.pixel_unsafe<float>(i);
        mB += B.pixel_unsafe<float>(i);
    }
    mA /= w*h;
    mB /= w*h;
    double normA = 0;
    double normB = 0;
    for (int i=0; i<w*h; i++) {
        normA += xsqrf(A.pixel_unsafe<float>(i) - mA);
        normB += xsqrf(B.pixel_unsafe<float>(i) - mB);
    }
    normA = sqrt(normA);
    normB = sqrt(normB);

    double corr = 0;
    for (int i=0; i<w*h; i++) {
        corr += (A.pixel_unsafe<float>(i) - mA) * (B.pixel_unsafe<float>(i) - mB);
    }
    double mult = normA * normB;
    if (mult > 0.0001) {
        corr /= mult;
    }

    return corr;
}

//---------------------------------------------------------------------
void XClassMotionDetectorRouter::save_templates() {
    QStringList files = get_strings_template_files();
    xc_assert(files.size() >= n_, "Not enough file names");

    for (int i=0; i<n_; i++) {
        QString file_name = xc_absolute_path(files[i]);
        XRasterUtils::save(output_image(i)->read().data().data<XRaster>(), file_name);
    }

    xc_console_append("Templates are saved");
    load_templates();

}

//---------------------------------------------------------------------
void XClassMotionDetectorRouter::load_templates() {
    QStringList files = get_strings_template_files();
    xc_assert(files.size() >= n_, "Not enough file names");
    for (int i=0; i<n_; i++) {
       QString file_name = xc_absolute_path(files[i]);
       XRasterUtils::load(*template_image(i)->write().data().data<XRaster>(), file_name);
    }
}

//---------------------------------------------------------------------
void XClassMotionDetectorRouter::stop() {
    started_ = 0;
    seti_started(started_);

}

//---------------------------------------------------------------------
void XClassMotionDetectorRouter::on_button_pressed(QString button_id) {

}

//---------------------------------------------------------------------
