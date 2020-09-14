#include "console.h"
#include <QDebug>
#include <QMessageBox>
#include <QString>
#include "mainwindow.h"
#include "consoleview.h"

//Вызовы исключений:
//Исключение при парсинге и прочих внутренних операциях
void xclu_exception(QString message) {
    xclu_exception(ErrorInfo(message));
}

void xclu_exception(ErrorInfo err) {
    throw XCluException(err);
}


//Ошибка, после которой программа завершает работу
void xclu_halt(QString message) {
    throw XCluCriticalException(message);
}

//Показ окна сообщений
void xclu_message_box(QString message) {
     QMessageBox::information(0, "Warning", message);
}


//Вывод в лог ConsoleView
void xclu_console_warning(QString message, bool dirty) {
    xclu_assert(CONS_VIEW, "CONS_VIEW is not created, can't add log message there");
    CONS_VIEW->log(message, dirty);
    qDebug() << "warning >>" << message;
}
void xclu_console_append(QString message, bool dirty) {
    xclu_assert(CONS_VIEW, "CONS_VIEW is not created, can't add log message there");
    CONS_VIEW->log(message, dirty);
    qDebug() << ">>" << message;
}
void xclu_console_clear() {
    CONS_VIEW->clear();
}

//Сигнал, что проект был изменен
//обращается прямо в MainWindow
void xclu_document_modified() {
    static MainWindow *win = nullptr;
    if (!win) win = MainWindow::main_window();
    win->set_document_modified();
}
