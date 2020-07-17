#include <QShowEvent>
#include <QScrollBar>
#include "xcluscrollarea.h"
#include "xcludoublespinbox.h"
#include "incl_qtcpp.h"


//---------------------------------------------------------------------
XcluScroollArea::XcluScroollArea(QWidget *parent)
    :QScrollArea(parent)
{

}

//---------------------------------------------------------------------
//был ли слайдер уже активирован после загрузки проекта (то есть, окно полностью сформировалось)
bool XcluScroollArea::is_shown() {
    return shown_;
}

//---------------------------------------------------------------------
void XcluScroollArea::resizeEvent(QResizeEvent *e) {
    QScrollArea::resizeEvent(e);
    if (verticalScrollBar()->isVisible() && !shown_) {
        apply_vscroll();
        //очень важно поставить shown_ после apply_vscroll()
        //- чтобы не посылался ненужный сигнал, будто значение изменилось и is_shown()
        //это используется в InterfaceGuiPage при отслеживании изменения значения
        shown_ = true;
    }
}

//---------------------------------------------------------------------
void XcluScroollArea::set_vscroll(int scroll) {
    vscroll_ = scroll;
    apply_vscroll();
}

//---------------------------------------------------------------------
int XcluScroollArea::get_vscroll() {
    if (shown_) {
        vscroll_ = verticalScrollBar()->value();
    }
    return vscroll_;
}

//---------------------------------------------------------------------
void XcluScroollArea::apply_vscroll() {
    verticalScrollBar()->setValue(vscroll_);
}

//---------------------------------------------------------------------
