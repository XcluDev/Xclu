#ifndef CONSOLE_H
#define CONSOLE_H

//Выдача сообщений об ошибках
//TODO: Сейчас сообщения об ошибках печатаются в консоль,
//сделать их вывод в виде MessageBox,
//но это нужно делать в основном потоке, и их накапливать в списке
//(с mutex, так как сообщения могут идти из разных потоков).

#include "incl_qt.h"


//Вызовы исключений:
//Исключение при парсинге и прочих внутренних операциях
void xclu_exception(QString message);

void xclu_exception(ErrorInfo err);


//Ошибка, после которой программа завершает работу
void xclu_halt(QString message);

//Здесь assert обязательно делать макросом - чтобы если не выполнится, строки не создавались
#define xclu_assert(cond, message) {if (!(cond)) xclu_exception(message);}

//Показ окна сообщений
void xclu_message_box(QString message);

//Вывод в лог - ConsoleView
void xclu_console_warning(QString message);
void xclu_console_append(QString message);

//Сигнал, что проект был изменен
//обращается прямо в MainWindow
void xclu_document_modified();


//Исключение внутри программы
struct XCluException: public std::exception {
    XCluException(const QString &message) {
        err_ = ErrorInfo(message);
    }
    XCluException(const ErrorInfo &err) {
        err_ = err;
    }
    //дописать текст
    XCluException(const QString &prepend, ErrorInfo err) {
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
