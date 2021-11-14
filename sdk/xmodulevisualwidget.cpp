#include "xmodulevisualwidget.h"

#include "incl_cpp.h"
#include <QPainter>
#include <QTimer>
#include "xmodulewidget.h"

//---------------------------------------------------------------------
XModuleVisualWidget::XModuleVisualWidget(QWidget *parent, XModuleWidget *xmodule)
    : QWidget(parent)
{
    //setFixedSize(1280, 720);

    xc_assert(xmodule, "XModuleVisualWidget constructor error - xmodule is nullptr");
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
void XModuleVisualWidget::set_fixed_size(int2 size) {
    if (size.x != w() || size.y != h()) {
        setFixedSize(size.x, size.y);
    }
}

//---------------------------------------------------------------------
XMouseButton qtmousebutton_to_xmousebutton(Qt::MouseButton btn) {
    if (btn == Qt::LeftButton) return XMouseButton_left;
    if (btn == Qt::MiddleButton) return XMouseButton_middle;
    if (btn == Qt::RightButton) return XMouseButton_right;

    //Note: there are much more buttons available at Qt::MouseButton
    return XMouseButton_none;
}

//---------------------------------------------------------------------
//Mouse events
void XModuleVisualWidget::add_mouse_event(int type, QMouseEvent *event) {
    xmodule_->add_mouse_event(XWidgetEvent_Type(type), int2(event->x(), event->y()),
                              qtmousebutton_to_xmousebutton(event->button()));
}

//---------------------------------------------------------------------
void XModuleVisualWidget::mousePressEvent(QMouseEvent *event) {
    add_mouse_event(XWidgetEvent_mouse_pressed, event);
}

//---------------------------------------------------------------------
//Note: for tracking mouse moves without pressing, required to call setMouseTracking(bool enable);
void XModuleVisualWidget::mouseMoveEvent(QMouseEvent *event) {
    add_mouse_event(XWidgetEvent_mouse_moved, event);
}

//---------------------------------------------------------------------
void XModuleVisualWidget::mouseReleaseEvent(QMouseEvent *event) {
    add_mouse_event(XWidgetEvent_mouse_released, event);
}

//---------------------------------------------------------------------
void XModuleVisualWidget::mouseDoubleClickEvent(QMouseEvent *event) {
    add_mouse_event(XWidgetEvent_mouse_double_clicked, event);
}

//---------------------------------------------------------------------
//Keyboard events
void XModuleVisualWidget::keyPressEvent(QKeyEvent *event) {
    xmodule_->add_keyboard_event(XWidgetEvent_key_pressed, event->key());
}

//---------------------------------------------------------------------
void XModuleVisualWidget::keyReleaseEvent(QKeyEvent *event) {
    xmodule_->add_keyboard_event(XWidgetEvent_key_released, event->key());
}


//---------------------------------------------------------------------
//drawing function
//call update(); to repaint widget
void XModuleVisualWidget::paintEvent(QPaintEvent * /*event*/)
{

    QPainter painter;
    painter.begin(this);
    xmodule_->draw(painter, w(), h());
    painter.end();
}

//---------------------------------------------------------------------
