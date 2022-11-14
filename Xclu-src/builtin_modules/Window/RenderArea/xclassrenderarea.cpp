#include "qt_widgets.h"
#include "xclassrenderarea.h"
#include "incl_cpp.h"
#include "registrarxclass.h"
#include "xmoduleutils.h"
#include "xmodule.h"

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
    auto modules = XModuleUtils::find_modules_by_filter(XCallType::Draw);
    // Use only modules which sets value "render_area" equalt to this module's name
    modules_.clear();
    QString render_area_str = "render_area";
    for (auto m: modules) {
        xc_assert(m->has_item(render_area_str),
                  QString("Internal error: module %1 received Draw events but hasn't %2 value")
                  .arg(m->name()).arg(render_area_str));
        if (m->gets(render_area_str) == name()) {
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













