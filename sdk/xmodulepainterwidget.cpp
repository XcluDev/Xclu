#include "xmodulepainterwidget.h"

#include "incl_cpp.h"
#include <QPainter>
#include <QTimer>
#include "xmodulepainter.h"

//---------------------------------------------------------------------
XModulePainterWidget::XModulePainterWidget(QWidget *parent, XModulePainter *xmodule)
    : QWidget(parent)
{
    //setFixedSize(1280, 720);

    xc_assert(xmodule, "XModulePainterWidget constructor error - xmodule is nullptr");
    xmodule_ = xmodule;

    //QLinearGradient gradient(QPointF(50, -20), QPointF(80, 20));
    //gradient.setColorAt(0.0, Qt::white);
    //gradient.setColorAt(1.0, QColor(0xa6, 0xce, 0x39));

    //background = QBrush(QColor(64, 32, 64));
    //circleBrush = QBrush(gradient);
    //circlePen = QPen(Qt::black);
    //circlePen.setWidth(1);
    //textPen = QPen(Qt::white);
    //textFont.setPixelSize(50);
}

//---------------------------------------------------------------------
void XModulePainterWidget::set_fixed_size(int2 size) {
    if (size.x != w() || size.y != h()) {
        setFixedSize(size.x, size.y);
    }
}

//---------------------------------------------------------------------
//double click to set detection center
//void DrawingWidget::mouseDoubleClickEvent(QMouseEvent *event) {
//    auto pos = event->pos(); //localPos();
//    SETTINGS.set_seed_pos(glm::vec2(pos.x(), pos.y()));
//}

//---------------------------------------------------------------------
//drawing function
//call update(); to repaint widget
void XModulePainterWidget::paintEvent(QPaintEvent * event)
{

    QPainter painter;
    painter.begin(this);
    xmodule_->draw(painter, w(), h());
    painter.end();
}

//---------------------------------------------------------------------
