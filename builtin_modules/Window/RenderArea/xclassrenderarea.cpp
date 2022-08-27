#include "qt_widgets.h"
#include "xclassrenderarea.h"

#include "incl_cpp.h"
#include "registrarxclass.h"
#include "xclass.h"

//registering module implementation
REGISTER_XCLASS(RenderArea)

//---------------------------------------------------------------------
XClassRenderArea::XClassRenderArea(QString class_name)
    :XClassWidget(class_name)
{

}

//---------------------------------------------------------------------
XClassRenderArea::~XClassRenderArea()
{

}

//---------------------------------------------------------------------
void XClassRenderArea::start() {
    collect_modules();
}

//---------------------------------------------------------------------
//Collect modules to render from
void XClassRenderArea::collect_modules() {
    auto modules = XCallUtils::find_modules_by_filter(XCallTypeDraw);
    // Use only modules which sets "render_area" to this module
    modules_.clear();
    for (auto m: modules) {
        if (m->gets("render_area") == name()) {
            modules_.append(m);
        }
    }

    // Output list to the screen
    QStringList list;
    for (auto m: modules_) {
        list.append(m->name());
    }
    clear_string_connected_modules();
    append_string_connected_modules(list);
}

//---------------------------------------------------------------------
void XClassRenderArea::update() {

    redraw();   //call to update screen
}


//---------------------------------------------------------------------
void XClassRenderArea::stop() {

}

//---------------------------------------------------------------------
void XClassRenderArea::draw(QPainter &painter, int outw, int outh) {

    //Antialiasing
    painter.setRenderHint(QPainter::Antialiasing);

    //Draw background
    painter.setBrush(QColor(geti_back_red(), geti_back_green(), geti_back_blue()));
    painter.setPen(Qt::PenStyle::NoPen);
    painter.drawRect(0, 0, outw, outh);

    //Draw elements
    for (auto m: modules_) {
        m->draw(painter, outw, outh);
    }
}
//---------------------------------------------------------------------













