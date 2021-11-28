#include <QDebug>
#include <QMessageBox>
#include <QString>
#include <QClipboard>
#include <QApplication>
#include <QThread>
#include "console.h"
#include "mainwindow.h"
#include "consoleview.h"

//---------------------------------------------------------------------
//Вызовы исключений:
//Исключение при парсинге и прочих внутренних операциях
void xc_exception(QString message) {
    xc_exception(ErrorInfo(message));
}

//---------------------------------------------------------------------
void xc_exception(ErrorInfo err) {
    qDebug() << "xc_exception:" << err.error_text();
    throw XException(err);
}

//---------------------------------------------------------------------
//Ошибка, после которой программа завершает работу
void xc_halt(QString message) {
    throw XCluCriticalException(message);
}

//---------------------------------------------------------------------
//Показ окна сообщений
void xc_message_box(QString message) {
     QMessageBox::information(0, "Warning", message);
}

//---------------------------------------------------------------------
//Вывод в лог ConsoleView
void xc_console_warning(QString message, bool dirty) {
    xc_assert(CONS_VIEW, "CONS_VIEW is not created, can't add log message there");
    CONS_VIEW->append(message, dirty);
    qDebug() << "warning >>" << message;
}

//---------------------------------------------------------------------
void xc_console_append(QString message, bool dirty) {
    xc_assert(CONS_VIEW, "CONS_VIEW is not created, can't add log message there");
    CONS_VIEW->append(message, dirty);
    qDebug() << ">>" << message;

}

//---------------------------------------------------------------------
void xc_console_repaint() {  //force redraw
    CONS_VIEW->update();
    qApp->processEvents();
}

//---------------------------------------------------------------------
void xc_console_clear() {
    CONS_VIEW->clear();

    //qApp->processEvents();  //update view
    //int sleep_ms = 1;     //need to sleep to process this ????????
    //QThread::msleep(sleep_ms);
}

//---------------------------------------------------------------------
//Сигнал, что проект был изменен
//обращается прямо в MainWindow
void xc_document_modified() {
    static MainWindow *win = nullptr;
    if (!win) win = MainWindow::window();
    win->set_document_modified();
}

//---------------------------------------------------------------------
//Copy text to clipboard
void xc_clipboard_set_text(QString text) {
    QClipboard *clipboard = QGuiApplication::clipboard();
    xc_assert(clipboard, "xclu_clipboard_set_text error: clipboard is nullptr");
    clipboard->setText(text);
}

//---------------------------------------------------------------------
//Get text from clipboard
QString xc_clipboard_get_text() {
    QClipboard *clipboard = QGuiApplication::clipboard();
    xc_assert(clipboard, "xclu_clipboard_get_text error: clipboard is nullptr");
    return clipboard->text();
}

//---------------------------------------------------------------------
