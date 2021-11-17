#include <qt_widgets.h>
#include "xmoduletestdrawing.h"
#include "incl_cpp.h"
#include "registrarxmodule.h"
#include "project_props.h"


//registering module implementation
REGISTER_XMODULE(TestDrawing)

//---------------------------------------------------------------------
XModuleTestDrawing::XModuleTestDrawing(QString class_name)
    :XModuleWidget(class_name)
{

}

//---------------------------------------------------------------------
XModuleTestDrawing::~XModuleTestDrawing()
{

}

//---------------------------------------------------------------------
void XModuleTestDrawing::start() {
    //xc_console_append(QString("%1 - start").arg(name()));

}

//---------------------------------------------------------------------
void XModuleTestDrawing::update() {
    set_fixed_size(int2(geti_screen_w(), geti_screen_h()));
    redraw();
}

//---------------------------------------------------------------------
void XModuleTestDrawing::stop() {
    //xc_console_append(QString("%1 - stop").arg(name()));
}

//---------------------------------------------------------------------
void XModuleTestDrawing::draw(QPainter &painter, int w, int h) {
    painter.fillRect(QRect(0,0,w,h), QColor(200,200,200));
    //painter.translate(100, 100);
    //painter.save();
    //painter.setBrush(circleBrush);
    //painter.setPen(circlePen);
    //painter.rotate(elapsed * 0.030);
    //painter.restore();
    //painter.setPen(textPen);
    //painter.setFont(textFont);
    //painter.drawText(QRect(-50, -50, 100, 100), Qt::AlignCenter, QStringLiteral("Qt"));

    painter.setBrush(QColor(64,64,64));
    painter.setPen(QColor(0,0,0));

    painter.drawEllipse(w/4,h/4,w/2,h/2);


}

//---------------------------------------------------------------------
