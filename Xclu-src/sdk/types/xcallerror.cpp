#include "xcallerror.h"
#include "xhandlingerrors.h"

//---------------------------------------------------------------------
XCallError::XCallError(QString text) {
    setup(text);
}

//---------------------------------------------------------------------
//добавить к тексту ошибки предысторию с "\n" - полезно при передаче ошибок между уровнями, дописывая подробности
XCallError::XCallError(QString prepend_text, const XCallError &err) {
    prepend(prepend_text, err);
}

//---------------------------------------------------------------------
void XCallError::clear() {
    is_error_ = false;
    error_text_.clear();
}

//---------------------------------------------------------------------
void XCallError::setup(QString text) {
    is_error_ = true;
    error_text_ = text;
}

//---------------------------------------------------------------------
void XCallError::prepend(QString prepend_text, const XCallError &err) {
    is_error_ = true;
    error_text_ = prepend_text + "\n" + err.error_text();
}

//---------------------------------------------------------------------
void XCallError::throw_error() const {    //если есть ошибка - сгенерировать исключение
    if (is_error()) {
        xc_exception(error_text());
    }
}
