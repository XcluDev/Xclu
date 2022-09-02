#include "qt_widgets.h"
#include "incl_cpp.h"
#include "xguitext.h"
#include "xitemtext.h"

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
XGuiText::XGuiText(XGuiPageBuilder &page_builder, XItemText *item)
    :XGuiComp(page_builder, item)
{
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

    //insert to page
    insert_widgets(page_builder,
                   textEdit_,
                   new_label(), 3, false,
                   nullptr, 1, false,
                   new_label_link(), 1, true,
                   textEdit_, 5, true
                   );

    //track changes
    connect(textEdit_, SIGNAL (textChanged()), this, SLOT (on_value_changed()));
}

//---------------------------------------------------------------------
XGuiText::~XGuiText() {

}

//---------------------------------------------------------------------
//Отслеживание изменений - переопределяем, чтобы скролл текста не сбрасывался при запросе toPlainText
void XGuiText::on_value_changed() {
    XGuiComp::on_value_changed();
    dirty_ = true;
}

//---------------------------------------------------------------------
//установка режима read_only - для out и блокировки констант при запуске проекта
void XGuiText::set_read_only_(bool read_only) {
    textEdit_->setReadOnly(read_only);
    xclu::widget_update_css(textEdit_);
}

//---------------------------------------------------------------------
QString XGuiText::value() {
    if (dirty_) {
        value_ = textEdit_->toPlainText();
        dirty_ = false;
    }
    return value_;
}

//---------------------------------------------------------------------
void XGuiText::set_value(QString v) {
    //проверяем, что значение не изменилось
    //(в противном случае, out-значение невозможно скопировать во время выполнения)
    if (value() != v) {
        value_ = v;
        textEdit_->setPlainText(v);
        dirty_ = false;

        //scroll to bottom automatically
        textEdit_->verticalScrollBar()->setValue(textEdit_->verticalScrollBar()->maximum());
    }
}

//---------------------------------------------------------------------
