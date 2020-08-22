#include "qt_widgets.h"
#include "incl_qtcpp.h"
#include "interfaceitemcheckbox.h"
#include "interfaceguicheckbox.h"

//---------------------------------------------------------------------
InterfaceGuiCheckbox::InterfaceGuiCheckbox(InterfaceGuiPageCreator &input, InterfaceItemCheckbox *item)
    :InterfaceGui(input, item)
{
    checkbox_ = new QCheckBox("");

    if (!item->is_group_checkbox()) { //обычный чекбокс
        insert_label(input);
        //вставка на страницу
        insert_widget_with_spacer(checkbox_, checkbox_, input);
    }
    else {
        //"групповой" чекбокс - то есть просто слева показать, без label
        checkbox_->setText(item->title());
        checkbox_->setToolTip(get_tip());

        QFrame *line_ = new QFrame();
        line_->setFrameShape(QFrame::HLine);
        line_->setFrameShadow(QFrame::Sunken);

        //добавляем на страницу
        input.grid->addWidget(line_,input.y, 1);

        //вставка на страницу слева, на место label
        int pos_x = 0;
        insert_widget(checkbox_, checkbox_, input, pos_x);
    }

    //квалификаторы
    if (item->is_out()) {
        set_read_only(true);
    }

    //отслеживание изменений
    connect(checkbox_, SIGNAL (stateChanged(int)), this, SLOT (on_value_changed()));
}

//---------------------------------------------------------------------
InterfaceGuiCheckbox::~InterfaceGuiCheckbox() {

}

//---------------------------------------------------------------------
//установка режима read_only - для out и блокировки констант при запуске проекта
void InterfaceGuiCheckbox::set_read_only(bool read_only) {
    //тут не вызываем InterfaceGui::set_read_only(read_only);
    //так как цвета фона ставить не нужно
    checkbox_->setEnabled(!read_only);
}

//---------------------------------------------------------------------
int InterfaceGuiCheckbox::value() {
    return (checkbox_->checkState() == Qt::Checked) ? 1 : 0;
}

//---------------------------------------------------------------------
void InterfaceGuiCheckbox::set_value(int v) {
    Qt::CheckState state = (v == 1) ? Qt::Checked : Qt::Unchecked;
    //проверяем, что значение не изменилось
    //(в противном случае, проект будет помечен как измененный, хотя это не так)
    if (value() != v) {
        checkbox_->setCheckState(state);
    }
}

//---------------------------------------------------------------------
