#include <qt_widgets.h>
#include "xclasstestdrawing.h"
#include "incl_cpp.h"
#include "registrarxclass.h"
#include "project_props.h"


//registering module implementation
REGISTER_XCLASS(TestDrawing)

//---------------------------------------------------------------------
XClassTestDrawing::XClassTestDrawing(QString class_name)
    :XClassWidget(class_name)
{

}

//---------------------------------------------------------------------
XClassTestDrawing::~XClassTestDrawing()
{

}

//---------------------------------------------------------------------
void XClassTestDrawing::start() {
    //xc_console_append(QString("%1 - start").arg(name()));

}

//---------------------------------------------------------------------
void XClassTestDrawing::update() {
    set_fixed_size(int2(geti_screen_w(), geti_screen_h()));
    redraw();
}

//---------------------------------------------------------------------
void XClassTestDrawing::stop() {
    //xc_console_append(QString("%1 - stop").arg(name()));
}

//---------------------------------------------------------------------
void XClassTestDrawing::draw(QPainter &painter, int w, int h) {
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
