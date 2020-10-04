#include "qt_widgets.h"
#include "incl_cpp.h"
#include "xitembutton.h"
#include "xguibutton.h"

//---------------------------------------------------------------------
XGuiButton::XGuiButton(XGuiPageCreator &input, XItemButton *item)
    :XGui(input, item)
{
    button_ = new QPushButton(item->title());
    button_->setMaximumWidth(xclu::BUTTON_WIDTH);
    button_->setToolTip(get_tip());

    //вставка на страницу
    insert_widget_with_spacer_next_line(button_, button_, input);

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
void XGuiButton::button_pressed() {
    //запоминаем, что кнопка была нажата, если не заблокирована (то есть const и запущен проект)
    if (!blocked()) {
        value_ = 1;
    }
    //в любом случае - отправляем сигнал в модуль
    ((XItemButton *)item__)->callback_button_pressed();
}

//---------------------------------------------------------------------