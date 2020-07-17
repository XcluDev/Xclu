#include <QtWidgets>
#include "interfaceguiseparator.h"
#include "interfaceitemseparator.h"


//---------------------------------------------------------------------
InterfaceGuiSeparator::InterfaceGuiSeparator(InterfaceGuiPageCreator &input, InterfaceItemSeparator *item)
    :InterfaceGui(input, item)
{
    is_line_ = item->is_line();
    is_separator_ = item->is_separator();

    if (is_separator_) {
        visible_size_ = xclu::SEPARATOR_HEIGHT;
        spacer_ = new QSpacerItem(1,visible_size_);
        //добавляем на страницу
        input.grid->addItem(spacer_,input.y,0,1,2);
        ////input.grid->setRowStretch(input.y,1);
        input.y++;
    }

    if (is_line_) {
        line_ = new QFrame();
        line_->setFrameShape(QFrame::HLine);
        line_->setFrameShadow(QFrame::Sunken);

        //добавляем на страницу
        input.grid->addWidget(line_,input.y, 0, 1, 2);
        input.y++;
    }
}

//---------------------------------------------------------------------
InterfaceGuiSeparator::~InterfaceGuiSeparator() {

}

//---------------------------------------------------------------------
void InterfaceGuiSeparator::set_visible(bool visible) {
    InterfaceGui::set_visible(visible);

    if (is_separator_) {
        if (visible) {
            spacer_->changeSize(1,visible_size_);
        }
        else {
            spacer_->changeSize(0,0);
        }
    }

    if (is_line_) {
        line_->setVisible(visible);
    }

}

//---------------------------------------------------------------------
