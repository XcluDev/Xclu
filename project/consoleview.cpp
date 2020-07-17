#include <QtWidgets>
#include "consoleview.h"
#include "incl_qtcpp.h"

ConsoleView *CONS_VIEW;

//---------------------------------------------------------------------
ConsoleView::ConsoleView(QWidget *parent)
    :QWidget(parent)
{

    //textEdit_ = new QTextEdit;    //- позволяет вставлять картинки и HTML
    textArea_ = new QPlainTextEdit;

    //ставим число строк, как запрошено
    //int font_spacing = textEdit_->fontMetrics().lineSpacing();
    //int hmin = font_spacing * item->lines_count_min();
    //int hmax = font_spacing * item->lines_count_max();

    //textArea_->setMinimumHeight(200);
    //textArea_->setMaximumHeight(hmax);
    textArea_->setReadOnly(true);
    //ставим серый фон
    QPalette pal = textArea_->palette();
    pal.setBrush(QPalette::Base, pal.brush(QPalette::Midlight));
    textArea_->setPalette(pal);


    buttonClear_ = new QPushButton(tr("Clear"));
    //Пока скрываем кнопку Clear
    buttonClear_->setVisible(false);

    //Сборка frame
    QWidget *frame = xclu::vwidget(-1, new QLabel(tr("Console")), 0, textArea_, 10, buttonClear_, 0);

    //устанавливаем шрифт
    //xclu::set_font_size(frame, xclu::main_font_size);
    xclu::set_font_size(textArea_, xclu::console_font_size);


    //общий layout
    this->setLayout(xclu::vlayout(0, frame, 0));

    //отслеживание изменений
    connect(buttonClear_, SIGNAL (released()), this, SLOT (clear()));

}

//---------------------------------------------------------------------
//добавить сообщение
void ConsoleView::log(QString message) {
    textArea_->appendPlainText(message);
    qDebug() << "Appending " << message;

    empty_ = false;
}

//---------------------------------------------------------------------
//очистить список сообщений
void ConsoleView::clear() {
    textArea_->clear();
    empty_ = true;
}

//---------------------------------------------------------------------
//есть ли сообщения
bool ConsoleView::is_empty() {
    return empty_;
}

//---------------------------------------------------------------------

