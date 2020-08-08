#include <QtWidgets>
#include "incl_qtcpp.h"
#include "interfaceguitext.h"
#include "interfaceitemtext.h"

//---------------------------------------------------------------------
InterfaceGuiText::InterfaceGuiText(InterfaceGuiPageCreator &input, InterfaceItemText *item)
    :InterfaceGui(input, item)
{
    insert_label(input);

    //textEdit_ = new QTextEdit;    //- позволяет вставлять картинки и HTML
    textEdit_ = new QPlainTextEdit;

    //ставим моноширинный шрифт
    auto font = textEdit_->font();
    //font.setFixedPitch(true);
    font.setFamily("Courier New");
    textEdit_->setFont(font);
    //ставим покрупнее размер
    xclu::set_font_size(textEdit_, xclu::strings_font_size);


    //ставим число строк, как запрошено
    int font_spacing = textEdit_->fontMetrics().lineSpacing();

    //если -1 - то этого ограничения нет
    if (item->lines_count_min() != -1) {
        int hmin = font_spacing * item->lines_count_min();
        textEdit_->setMinimumHeight(hmin);
    }
    if (item->lines_count_max() != -1) {
        int hmax = font_spacing * item->lines_count_max();
        textEdit_->setMaximumHeight(hmax);
    }

    //вставка на страницу, при этом с новой строки и на всю ширину
    insert_widget(textEdit_, textEdit_, input, 0, 1, 2, 1);

    //отслеживание изменений
    connect(textEdit_, SIGNAL (textChanged()), this, SLOT (on_value_changed()));
}

//---------------------------------------------------------------------
InterfaceGuiText::~InterfaceGuiText() {

}

//---------------------------------------------------------------------
//Отслеживание изменений - переопределяем, чтобы скролл текста не сбрасывался при запросе toPlainText
void InterfaceGuiText::on_value_changed() {
    InterfaceGui::on_value_changed();
    dirty_ = true;
}

//---------------------------------------------------------------------
//установка режима read_only - для out и блокировки констант при запуске проекта
void InterfaceGuiText::set_read_only(bool read_only) {
    //цвет фона
    InterfaceGui::set_read_only(read_only);

    textEdit_->setReadOnly(read_only);
}

//---------------------------------------------------------------------
QString InterfaceGuiText::value() {
    if (dirty_) {
        value_ = textEdit_->toPlainText();
        dirty_ = false;
    }
    return value_;
}

//---------------------------------------------------------------------
void InterfaceGuiText::set_value(QString v) {
    //проверяем, что значение не изменилось
    //(в противном случае, out-значение невозможно скопировать во время выполнения)
    if (value() != v) {
        value_ = v;
        textEdit_->setPlainText(v);
        dirty_ = false;
    }
}

//---------------------------------------------------------------------
