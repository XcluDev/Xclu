#include "XModuleRenderElement.h"
#include "incl_cpp.h"
#include "registrarxclass.h"
#include "xmodule.h"

//registering module implementation
REGISTER_XMODULE(RenderElement)

//---------------------------------------------------------------------
XModuleRenderElement::XModuleRenderElement(QString class_name)
    :XClass(class_name)
{

}

//---------------------------------------------------------------------
XModuleRenderElement::~XModuleRenderElement()
{

}

//---------------------------------------------------------------------
void XModuleRenderElement::start() {


}

//---------------------------------------------------------------------
void XModuleRenderElement::update() {
}

//---------------------------------------------------------------------
void XModuleRenderElement::stop() {

}

//---------------------------------------------------------------------
void XModuleRenderElement::draw(QPainter &painter, int w, int h) {
    int repx = (geti_repeats()) ? geti_repeat_x() : 1;
    int repy = (geti_repeats()) ? geti_repeat_y() : 1;
    int stepx = geti_step_x();
    int stepy = geti_step_y();

    QPen pen(QColor(geti_border_red(),geti_border_green(),geti_border_blue()));
    pen.setWidth(geti_border_width());
    painter.setPen(pen);
    painter.setBrush(Qt::BrushStyle::NoBrush);

    //TODO now pos only in pixels
    int W = geti_w_int2000();
    int H = geti_h_int2000();

    int Y = geti_y_int2000();
    for (int ry=0; ry<repy; ry++) {
        int X = geti_x_int2000();
        for (int rx=0; rx<repx; rx++) {
            //TODO only rect/circle
            if (gete_button_shape() == button_shape_Rectangle) {
                painter.drawRect(X-W/2,Y-H/2,W,H);
            }
            else {
                painter.drawEllipse(X-W/2,Y-H/2,W,H);
            }
            X += stepx + W;
        }
        Y += stepy + H;
    }
}

//---------------------------------------------------------------------
