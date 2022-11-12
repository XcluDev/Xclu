#include "xclassgraphs.h"
#include "incl_cpp.h"
#include "registrarxclass.h"
#include "project_props.h"

REGISTER_XCLASS(Graphs)

//---------------------------------------------------------------------
XClassGraphs::XClassGraphs(QString class_name)
    :XClass(class_name)
{

}

//---------------------------------------------------------------------
XClassGraphs::~XClassGraphs()
{
}

//---------------------------------------------------------------------
void XClassGraphs::on_loaded() {
}

//---------------------------------------------------------------------
void XClassGraphs::start() {
    graphs_lines_.clear();
}


//---------------------------------------------------------------------
/*void XClassGraphs::set_graphs(const NeuroplayDevice::ChannelsData &data)
{
    graphs_.clear();
    graphs_lines_.clear();
    if (data.empty()) {
        return;
    }
    for (QVector<double> chdata: data)
    {
        int n = chdata.size();
        QVector<float> graph(n);
        QVector<QPointF> line(n);
        for (int i=0; i<chdata.size(); i++) {
            float v = chdata[i] * 0.01f;
            graph[i] = v;
            line[i] = QPointF(i, v*100.0f);
        }
        graphs_ << graph;
        graphs_lines_ << line;
    }
    update_blink();
}*/

//---------------------------------------------------------------------
void XClassGraphs::update() {

}


//---------------------------------------------------------------------
void XClassGraphs::stop() {

}

//---------------------------------------------------------------------
void XClassGraphs::draw(QPainter &painter, int outw, int outh) {

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
    QColor back_color = Qt::white;
    painter.fillRect(x0, y0, w, h, back_color);


    painter.setPen(Qt::black);
    painter.drawLine(0,0,w,h);

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


}

//---------------------------------------------------------------------


