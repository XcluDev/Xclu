#include "qt_widgets.h"
#include "xmodulerenderarea.h"

#include "incl_cpp.h"
#include "registrarxmodule.h"
#include "module.h"

//registering module implementation
REGISTER_XMODULE(RenderArea)

//---------------------------------------------------------------------
XModuleRenderArea::XModuleRenderArea(QString class_name)
    :XModuleWidget(class_name)
{

}

//---------------------------------------------------------------------
XModuleRenderArea::~XModuleRenderArea()
{

}

//---------------------------------------------------------------------
void XModuleRenderArea::start() {
    collect_modules();
}

//---------------------------------------------------------------------
//Collect modules to render from
void XModuleRenderArea::collect_modules() {
    modules_ = XIntermodule::find_modules_by_filter(XCallTypeDraw);
    QStringList list;
    for (auto m: modules_) {
        list.append(m->name());
    }
    append_string_connected_modules(list);
}

//---------------------------------------------------------------------
void XModuleRenderArea::update() {

    redraw();   //call to update screen
}


//---------------------------------------------------------------------
void XModuleRenderArea::stop() {

}

//---------------------------------------------------------------------
void XModuleRenderArea::draw(QPainter &painter, int outw, int outh) {

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













