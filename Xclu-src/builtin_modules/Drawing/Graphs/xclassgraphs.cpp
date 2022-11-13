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
    data_.clear();

    seti_last_data_columns_count(0);
    setf_last_data_max_value(0);

    separator_ = gets_separator();
    xc_assert(!separator_.isEmpty(), "Separator is empty, please set there some symbol");

    // Set indices
    QSet<int> indices_set;
    indices_.clear();
    if (!geti_draw_all_columns()) {
        auto list = get_strings_columns_to_draw();
        for (auto line: list) {
            if (line.isEmpty()) {
                continue;
            }
            auto line_list = line.split(" ");

            // Getting first number in line '1 First channel' as index
            int index_plus1 = line_list[0].toInt();
            xc_assert(index_plus1>0, "Indices at Columns To Draw must be > 0");
            int index = index_plus1 - 1;
            xc_assert(!indices_set.contains(index), "Duplicated indices in Columns To Draw");
            indices_set.insert(index);
            indices_.push_back(index);
        }
        xc_assert(!indices_.isEmpty(), "Please specify non-empty Columns To Draw");
    }

    // File
    setf_read_file_position(0);
    file_pos_ = 0;
    lines_to_send_ = 0;

    clear_string_file_data();
    seti_is_file_new_data(0);

    if (gete_data_source() == data_source_File) {
        xc_assert(!gets_read_file_name().isEmpty(), "Please choose the file to read.");
        file_ = xc_read_text_file_relpath(gets_read_file_name());
        xc_assert(!file_.isEmpty(), "File is empty: " + gets_read_file_name());
    }
}

//---------------------------------------------------------------------
void XClassGraphs::update() {
    //Input value
    if (gete_data_source() == data_source_Input_Value) {
        if (geti_is_new_data()) {
            parse_lines(get_strings_data());
        }
    }

    //File
    if (gete_data_source() == data_source_File) {
        clear_string_file_data();

        lines_to_send_ += xc_dt() * geti_read_file_rate();

        bool need_send = (lines_to_send_ > 1);
        seti_is_file_new_data(need_send);
        if (need_send) {
            QStringList data;
            int n = file_.size();
            while (lines_to_send_ > 1) {
                lines_to_send_ -= 1;
                file_pos_++;
                if (file_pos_ >= n) file_pos_ = 0;
                data.append(file_[file_pos_]);
            }
            float perc = (n>=2) ? float(file_pos_)/(n-1)*100.f : 0.f;
            setf_read_file_position(perc);
            parse_lines(data);

            append_string_file_data(data);
        }
    }
}


//---------------------------------------------------------------------
void XClassGraphs::parse_lines(QStringList lines) {  // Push line for processing

    int input_dims = 0;
    float max_value = 0;
    bool use_indices = !indices_.isEmpty();
    int history = geti_history_size();

    for (auto line: lines) {
        if (line.isEmpty()) {
            continue;
        }
        auto list = line.split(separator_);
        input_dims = list.size();
        int dims = input_dims;
        if (use_indices) {
            dims = qMin(dims, indices_.size());
        }

        // Увеличиваем число графиков, если требуется
        int n = (!data_.isEmpty())?data_[0].size():0;
        if (data_.size() < dims) {
            int old_dims = data_.size();
            data_.resize(dims);
            for (int i=old_dims; i<dims; i++) {
                data_[i].resize(n);
            }
        }

        // Удаляем старые значения из истории
        if (n >= history) {
            for (auto& graph: data_) {
                graph.erase(graph.begin());
            }
        }

        // Вставляем новые значения
        if (!use_indices) {
            for (int i=0; i<dims; i++) {
                float value = list[i].toFloat();
                data_[i].push_back(value);
                max_value = qMax(max_value, fabs(value));
            }
        }
        else {
            for (int k = 0; k<indices_.size(); k++) {
                int i = indices_[k];
                float value = (i < input_dims) ? list[i].toFloat() : 0;
                data_[k].push_back(value);
                max_value = qMax(max_value, fabs(value));
            }
        }
    }

    seti_last_data_columns_count(input_dims);
    setf_last_data_max_value(max_value);
}

//---------------------------------------------------------------------
void XClassGraphs::stop() {

}

//---------------------------------------------------------------------
void XClassGraphs::draw(QPainter &painter, int outw, int outh) {
    if (data_.isEmpty()) {
        return;
    }

    float x0 = getf_draw_graphs_x() * outw;
    float y0 = getf_draw_graphs_y() * outh;
    float w = getf_draw_graphs_w() * outw;
    float h = getf_draw_graphs_h() * outh;

    float margin_x = getf_margin_x() * w;
    float margin_y = getf_margin_y() * h;
    x0 += margin_x;
    y0 += margin_y;
    w -= 2*margin_x;
    h -= 2*margin_y;


    //Antialiasing
    painter.setRenderHint(QPainter::Antialiasing);

    // Draw background
    // QColor back_color = Qt::white;
    // painter.fillRect(x0, y0, w, h, back_color);

    QPen pen(QBrush(QColor(geti_pen_red(), geti_pen_green(), geti_pen_blue())), geti_line_width());

    painter.setPen(pen);
    // painter.drawLine(0,0,w,h);

    int NY = data_.size();
    int NX = geti_history_size();
    float minv = getf_min_value();
    float maxv = getf_max_value();
    if (maxv == minv) {
        maxv = minv + 0.001;
    }

    float h1 = h / NY;
    float h1_half = h1 / 2;
    float scale_x = w / NX;

    QVector<QPointF> pnt;
    for (int k=0; k<NY; k++)
    {
        auto& graph = data_[k];
        int n = graph.size();
        pnt.resize(n);
        float y1 = (k + 0.5f) * h1;
        for (int i=0; i<n; i++) {
            pnt[i] = QPointF(i * scale_x, xmapf(graph[i], minv, maxv, h1_half/2, -h1_half/2));
        }

        painter.save();
        painter.translate(x0, y0 + y1);
        painter.drawPolyline(pnt);
        painter.restore();
    }



}

//---------------------------------------------------------------------


