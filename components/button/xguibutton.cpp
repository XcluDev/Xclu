#include "qt_widgets.h"
#include "incl_cpp.h"
#include "xitembutton.h"
#include "xguibutton.h"

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
XGuiButton::XGuiButton(XGuiPageBuilder &page_builder, XItemButton *item)
    :XGui(page_builder, item)
{
    button_ = new QPushButton(item->title());
    button_->setMaximumWidth(xclu::BUTTON_WIDTH);
    button_->setToolTip(get_tip());

    //insert to page
    insert_widgets(page_builder,
                   button_,
                   nullptr, 1, false,
                   button_, 2, false,
                   nullptr, 1, false,
                   new_label_link(), 1, true);

    connect(button_, SIGNAL (released()), this, SLOT (button_pressed()));

}

//---------------------------------------------------------------------
XGuiButton::~XGuiButton() {

}

//---------------------------------------------------------------------
//значение - нажатие считывается один раз, затем стирается
int XGuiButton::value() {
    int res = value_;
    value_ = 0;
    return res;
}

//---------------------------------------------------------------------
//User pressed the button
void XGuiButton::button_pressed() {
    //запоминаем, что кнопка была нажата, если не read only
    if (!is_read_only()) {
        value_ = 1;
    }

    //warp to try/catch, because whole Xclu can crash here
    try {
        ((XItemButton *)item__)->callback_button_pressed();
    }
    catch (XException &e) {
        xclu_message_box("Error: " + e.whatQt());
    }
}

//---------------------------------------------------------------------
