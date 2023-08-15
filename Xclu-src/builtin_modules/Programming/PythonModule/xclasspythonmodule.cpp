#include "xclasspythonmodule.h"
#include "incl_cpp.h"
#include "registrarxclass.h"
#include "project_props.h"
#include "pythoncore.h"

REGISTER_XCLASS(PythonModule)

// https://realpython.com/python-bindings-overview/
// https://docs.python.org/3/extending/index.html
// https://docs.python.org/3/extending/embedding.html

//---------------------------------------------------------------------
XClassPythonModule::XClassPythonModule(QString class_name)
    :XClass(class_name)
{

}

//---------------------------------------------------------------------
XClassPythonModule::~XClassPythonModule()
{

}

//---------------------------------------------------------------------
void XClassPythonModule::on_loaded() {
    //sets_send_status("Not started");
}

//---------------------------------------------------------------------
void XClassPythonModule::on_button_pressed(QString button_id) {
    //if (button_id == "print_devices") {
    //}
}


//---------------------------------------------------------------------
void XClassPythonModule::start() {

    //xc_assert(geti_graphs_enabled() || !geti_blink_detection(), "Please enable Connect > Graphs to detect blinks.");
}


//---------------------------------------------------------------------
void XClassPythonModule::update() {
    // Buttons
    //if (geti_btn_connect()) {
    //}
}

//---------------------------------------------------------------------
void XClassPythonModule::stop() {

}

//---------------------------------------------------------------------
void XClassPythonModule::draw(QPainter &painter, int outw, int outh) {
/*
    if (geti_draw_graphs_enabled()) {
        float x0 = getf_draw_graphs_x() * outw;
        float y0 = getf_draw_graphs_y() * outh;
        float w = getf_draw_graphs_w() * outw;
        float h = getf_draw_graphs_h() * outh;

        //Antialiasing
        painter.setRenderHint(QPainter::Antialiasing);

        //Draw background
        //painter.setBrush(QColor(0, 0, 0));
        //painter.setPen(Qt::PenStyle::NoPen);
        //painter.drawRect(0, 0, outw, outh);

        // Blue background on eye blink, else white
        QColor back_color = (geti_blink_detected()) ? QColor(200,200,255) : Qt::white;
        painter.fillRect(x0, y0, w, h, back_color);

        if (!graphs_lines_.isEmpty())
        {
            painter.setPen(Qt::black);
            int channels = graphs_lines_.size();
            float h1 = h / channels;
            for (int i=0; i<channels; i++)
            {
                int count = graphs_lines_[i].size();
                float y1 = (i + 0.5f) * h1;

                const float scale_y = 200;

                painter.save();
                painter.translate(x0, y0 + y1);
                painter.scale(w / count, h1 / scale_y);
                painter.drawPolyline(graphs_lines_[i]);
                painter.restore();
            }
        }
    }*/

}

//---------------------------------------------------------------------


