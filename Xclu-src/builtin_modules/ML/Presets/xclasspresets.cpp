#include "qt_widgets.h"
#include "xclasspresets.h"
#include "incl_cpp.h"
#include "registrarxclass.h"
#include "project_props.h"
#include "xmodule.h"
#include "xobjectvis.h"


//registering module implementation
REGISTER_XCLASS(Presets)

//---------------------------------------------------------------------
XClassPresets::XClassPresets(QString class_name)
    :XClassWidget(class_name)
{

}

//---------------------------------------------------------------------
XClassPresets::~XClassPresets()
{

}

//---------------------------------------------------------------------
void XClassPresets::start() {

}

//---------------------------------------------------------------------
void XClassPresets::update() {


    redraw();   //call to update screen

}

//---------------------------------------------------------------------
void XClassPresets::stop() {
    /*
    //нам не надо удалять виджет - так как он будет удален родителем
    //поэтому, просто обнуляем
    widget_ = nullptr;

    //delete shader's data
    reset_shader();
    */
}

//---------------------------------------------------------------------
void XClassPresets::draw(QPainter &painter, int outw, int outh) {

    //Antialiasing
    painter.setRenderHint(QPainter::Antialiasing);

    //Draw background
    painter.setBrush(QColor(0, 0, 0));
    painter.setPen(Qt::PenStyle::NoPen);
    painter.drawRect(0, 0, outw, outh);

    //Vector field - attractors
    // painter.save();
    // painter.translate(wsp, 0);

    // painter.restore();

}

//---------------------------------------------------------------------

