#ifndef CONSOLE_H
#define CONSOLE_H

//Выдача сообщений об ошибках
//TODO: Сейчас сообщения об ошибках печатаются в консоль,
//сделать их вывод в виде MessageBox,
//но это нужно делать в основном потоке, и их накапливать в списке
//(с mutex, так как сообщения могут идти из разных потоков).

#include "incl_h.h"


//Вызовы исключений:
//Исключение при парсинге и прочих внутренних операциях
void xc_exception(QString message);

void xc_exception(ErrorInfo err);


//Ошибка, после которой программа завершает работу
void xc_halt(QString message);

//Здесь assert обязательно делать макросом - чтобы если не выполнится, строки не создавались
#define xc_assert(cond, message) {if (!(cond)) xc_exception(message);}

//Показ окна сообщений
void xc_message_box(QString message);

//Вывод в лог - ConsoleView
void xc_console_warning(QString message, bool dirty = true);
void xc_console_append(QString message, bool dirty = true);
void xc_console_clear();

//Сигнал, что проект был изменен
//обращается прямо в MainWindow
void xc_document_modified();

//Copy text to clipboard
void xc_clipboard_set_text(QString text);
//Get text from clipboard
QString xc_clipboard_get_text();


//Исключение внутри программы
struct XException: public std::exception {
    XException(const QString &message) {
        err_ = ErrorInfo(message);
    }
    XException(const ErrorInfo &err) {
        err_ = err;
    }
    //дописать текст
    XException(const QString &prepend, ErrorInfo err) {
        err_ = ErrorInfo(prepend, err);
    }

   const char * what () const throw () {
      return err_.error_text().toStdString().c_str();
   }
   QString whatQt() const throw() {
       return err_.error_text();
   }
   ErrorInfo err() { return err_; }

private:
   ErrorInfo err_;
};

//Критическое исключение
struct XCluCriticalException: public std::exception {
    XCluCriticalException(const QString &message) {
        message_ = message;
    }
   const char * what () const throw () {
      return message_.toStdString().c_str();
   }
   QString whatQt() const throw() {
       return message_;
   }
private:
   QString message_;
};


#endif // CONSOLE_H
