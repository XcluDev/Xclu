#include "qt_widgets.h"
#include "incl_cpp.h"
#include "interfaceguienum.h"
#include "interfaceitemenum.h"
#include "xclucombobox.h"

//---------------------------------------------------------------------
InterfaceGuiEnum::InterfaceGuiEnum(InterfaceGuiPageCreator &input, InterfaceItemEnum *item)
    :InterfaceGui(input, item)
{
    insert_label(input);

    combo_ = new XcluComboBox();
    combo_->addItems(item->titles());
    names_ = item->names(); //запоминаем исходные имена, чтобы их выдавать при проверке групп видимости

    combo_->setMinimumWidth(xclu::COMBO_WIDTH_MIN);
    combo_->setMaximumWidth(xclu::COMBO_WIDTH_MAX);

    //отключаем, чтобы случайно не менялся от колесика
    //https://stackoverflow.com/questions/5821802/qspinbox-inside-a-qscrollarea-how-to-prevent-spin-box-from-stealing-focus-when
    combo_->setFocusPolicy(Qt::StrongFocus);

    //вставка на страницу
    //если есть единицы измерения - создаем блок с Label
    QString units = item->units();
    if (!units.isEmpty()) {
        //qDebug() << "units" << units;
        insert_widget_with_spacer(xclu::hwidget(0,
                                                combo_,0,
                                                new QLabel(units), 0),
                                  combo_, input);
    }
    else {
        insert_widget_with_spacer(combo_, combo_, input);
    }

    //отслеживание изменений
    connect(combo_, SIGNAL (currentIndexChanged(int)), this, SLOT (on_value_changed()));
}

//---------------------------------------------------------------------
InterfaceGuiEnum::~InterfaceGuiEnum() {

}

//---------------------------------------------------------------------
//установка режима read_only - для out и блокировки констант при запуске проекта
void InterfaceGuiEnum::set_read_only(bool read_only) {
    //цвет фона
    InterfaceGui::set_read_only(read_only);

    combo_->setEnabled(!read_only);
}

//---------------------------------------------------------------------
int InterfaceGuiEnum::index() {
    return combo_->currentIndex();
}

//---------------------------------------------------------------------
void InterfaceGuiEnum::set_index(int v) {
    if (v < 0 || v >= combo_->count()) v = 0;
    //проверяем, что значение не изменилось
    //(в противном случае, out-значение невозможно скопировать во время выполнения)
    if (combo_->count() > 0 && combo_->currentIndex() != v) {
        combo_->setCurrentIndex(v);
    }
}

//---------------------------------------------------------------------
//значение для проверки видимости детей
QString InterfaceGuiEnum::value_string_for_visibility() {
    int i = index();
    if (i >= 0 && i < names_.size()) {
        return names_[i];
    }
    return "";
};

//---------------------------------------------------------------------
