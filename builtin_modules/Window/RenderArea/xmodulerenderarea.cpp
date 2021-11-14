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

}

//---------------------------------------------------------------------
void XModuleRenderArea::update() {

    repaint();   //call to update screen
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
}
//---------------------------------------------------------------------













