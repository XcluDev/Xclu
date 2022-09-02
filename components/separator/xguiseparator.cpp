#include "qt_widgets.h"
#include "xguiseparator.h"
#include "xitemseparator.h"

//---------------------------------------------------------------------
/*
Widget structures for different controls:

float, int:     0 label, 1 control,  2 measure unit, 3 slider,     4 link label
checkbox:       0 label, 1 control                                 4 link label
checkbox_group: 0--------1 control,  2---------------3 horiz.line  4 link label
separator:      0 "control"
button:                  1 control                                 4 link label
string, text:   0 label                                            4 link label
                0 -------------------------------------------------4 control
object:         0 label                                            4 link label
                0--------------------2 thumbnail     3-------------4 description
*/

//---------------------------------------------------------------------
XGuiSeparator::XGuiSeparator(XGuiPageBuilder &page_builder, XItemSeparator *item)
    :XGuiComp(page_builder, item)
{
    bool is_line = item->is_line();
    bool is_separator = item->is_separator();

    spacer_ = new QFrame();

    spacer_->resize(1, xclu::SEPARATOR_HEIGHT);
    //spacer_ = new QSpacerItem(1,xclu::SEPARATOR_HEIGHT);

    if (is_line) {
        spacer_->setFrameShape(QFrame::HLine);
        spacer_->setFrameShadow(QFrame::Sunken);
    }
    if (is_separator) {
        spacer_->setFrameShape(QFrame::NoFrame);
        //spacer_->setFrameShadow(QFrame::Sunken);
    }

    //insert to page
    insert_widgets(page_builder,
                   spacer_,
                   spacer_, 5, true);
}

//---------------------------------------------------------------------
XGuiSeparator::~XGuiSeparator() {

}

//---------------------------------------------------------------------
