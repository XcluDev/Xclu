#pragma once

#include <QString>

// Тип ошибки для вызовов между модулями

struct XCallError {
    XCallError() {}
    XCallError(QString text);
    // Добавить к тексту ошибки предысторию с "\n" - полезно при передаче ошибок между уровнями, дописывая подробности
    XCallError(QString prepend_text, const XCallError &err);
    void clear();
    void setup(QString text);
    void prepend(QString prepend_text, const XCallError &err);
    // Извлечение информации о том, есть ли ошибка
    bool is_error() const { return is_error_; }
    QString error_text() const { return error_text_; }
    void throw_error() const;  //если есть ошибка - сгенерировать исключение
protected:
    bool is_error_ = false;
    QString error_text_;
};

