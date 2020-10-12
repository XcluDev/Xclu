#include "xcluclickablelabel.h"

//---------------------------------------------------------------------
XcluClickableLabel::XcluClickableLabel(const QString& text, QWidget* parent)
    : QLabel(text, parent) {

}

//---------------------------------------------------------------------
XcluClickableLabel::~XcluClickableLabel() {

}

//---------------------------------------------------------------------
void XcluClickableLabel::mousePressEvent(QMouseEvent* /*event*/) {
    emit clicked();
}

//---------------------------------------------------------------------
