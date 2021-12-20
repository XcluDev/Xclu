#ifndef CONSOLE_H
#define CONSOLE_H

//Выдача сообщений об ошибках
//TODO: Сейчас сообщения об ошибках печатаются в консоль,
//сделать их вывод в виде MessageBox,
//но это нужно делать в основном потоке, и их накапливать в списке
//(с mutex, так как сообщения могут идти из разных потоков).

#include "incl_h.h"


//Exceptions
void xc_exception(QString message);
void xc_exception(ErrorInfo err);


//Xclu-level critical exception with stopping Xclu
void xc_halt(QString message);

//Check condition, if false - eЗдесь assert обязательно делать макросом - чтобы если не выполнится, строки не создавались
#define xc_assert(cond, message) {if (!(cond)) xc_exception(message);}
#define xc_assert_ignore(cond, message, ignore) { \
    if (!(cond)) { \
        if (!(ignore)) xc_exception(message); \
        else { xc_console_append(message); return; } \
    }\
}

//Message box
void xc_message_box(QString message);

//Console output
void xc_console_warning(QString message, bool dirty = true); //TODO output in other color to mark it's warning
void xc_console_append(QString message, bool dirty = true);
void xc_console_clear();
void xc_console_repaint();  //force redraw, use for showing progress in long operations

//Signal that project was modified, calls directly to MainWindow
void xc_document_modified();

//Copy text to clipboard
void xc_clipboard_set_text(QString text);
//Get text from clipboard
QString xc_clipboard_get_text();


//Exception class
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

//Xclu-level critical exception class
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
