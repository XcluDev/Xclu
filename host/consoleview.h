#ifndef CONSOLEVIEW_H
#define CONSOLEVIEW_H

//Показ консольных сообщений

//Редактор списка модулей в проекте
#include <QWidget>
#include "incl_h.h"

QT_BEGIN_NAMESPACE
class QAction;
class QDialogButtonBox;
class QGroupBox;
class QLabel;
class QLineEdit;
class QPushButton;
class QPlainTextEdit;
class QVBoxLayout;
class QHBoxLayout;
class QListWidget;
class QTabWidget;
class QListWidgetItem;
QT_END_NAMESPACE


class ConsoleView : public QWidget
{
    Q_OBJECT

public:
    ConsoleView(QWidget *parent);

    //добавить сообщение, dirty - помечать, что консоль не пустая (были ошибки)
    void log(QString message, bool dirty = true);

    //есть ли сообщения (кроме тех, для которых dirty = false)
    bool is_empty();

public slots:
    //очистить список сообщений
    void clear();


private:
    QPlainTextEdit *textArea_ = nullptr;
    QPushButton *buttonClear_ = nullptr;

    bool empty_ = true;

};

extern ConsoleView *CONS_VIEW;

#endif // CONSOLEVIEW_H
