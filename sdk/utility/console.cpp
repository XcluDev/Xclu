#include <QDebug>
#include <QMessageBox>
#include <QString>
#include <QClipboard>
#include <QApplication>
#include "console.h"
#include "mainwindow.h"
#include "consoleview.h"

//---------------------------------------------------------------------
//Вызовы исключений:
//Исключение при парсинге и прочих внутренних операциях
void xclu_exception(QString message) {
    xclu_exception(ErrorInfo(message));
}

//---------------------------------------------------------------------
void xclu_exception(ErrorInfo err) {
    throw XException(err);
}

//---------------------------------------------------------------------
//Ошибка, после которой программа завершает работу
void xclu_halt(QString message) {
    throw XCluCriticalException(message);
}

//---------------------------------------------------------------------
//Показ окна сообщений
void xclu_message_box(QString message) {
     QMessageBox::information(0, "Warning", message);
}

//---------------------------------------------------------------------
//Вывод в лог ConsoleView
void xclu_console_warning(QString message, bool dirty) {
    xclu_assert(CONS_VIEW, "CONS_VIEW is not created, can't add log message there");
    CONS_VIEW->append(message, dirty);
    qDebug() << "warning >>" << message;
}

//---------------------------------------------------------------------
void xclu_console_append(QString message, bool dirty) {
    xclu_assert(CONS_VIEW, "CONS_VIEW is not created, can't add log message there");
    CONS_VIEW->append(message, dirty);
    qDebug() << ">>" << message;
}

//---------------------------------------------------------------------
void xclu_console_clear() {
    CONS_VIEW->clear();
}

//---------------------------------------------------------------------
//Сигнал, что проект был изменен
//обращается прямо в MainWindow
void xclu_document_modified() {
    static MainWindow *win = nullptr;
    if (!win) win = MainWindow::window();
    win->set_document_modified();
}

//---------------------------------------------------------------------
//Copy text to clipboard
void xclu_clipboard_set_text(QString text) {
    QClipboard *clipboard = QGuiApplication::clipboard();
    xclu_assert(clipboard, "xclu_clipboard_set_text error: clipboard is nullptr");
    clipboard->setText(text);
}

//---------------------------------------------------------------------
//Get text from clipboard
QString xclu_clipboard_get_text() {
    QClipboard *clipboard = QGuiApplication::clipboard();
    xclu_assert(clipboard, "xclu_clipboard_get_text error: clipboard is nullptr");
    return clipboard->text();
}

//---------------------------------------------------------------------
