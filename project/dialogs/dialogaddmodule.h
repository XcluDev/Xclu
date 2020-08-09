#ifndef DIALOGADDMODULE_H
#define DIALOGADDMODULE_H

//Диалог добавления модуля
#include <QDialog>

QT_BEGIN_NAMESPACE
class QAction;
class QDialogButtonBox;
class QGroupBox;
class QLabel;
class QLineEdit;
class QPushButton;
class QTextEdit;
class QTabWidget;
class QTableWidget;
class QListWidget;
QT_END_NAMESPACE

class DialogAddModule : public QDialog
{
    Q_OBJECT

public:
    //Вызывайте эту функцию для работы с диалогом,
    //если не nullptr - то диалог успешен и можно брать значения из него
    static DialogAddModule* call_dialog(QWidget *parent);

    DialogAddModule(QWidget *parent);

    //output:
    int selected_category = -1;
    int selected_item = -1;
    QString selected_type;

private:
    QTableWidget *create_table_for_category(int i);


    //Список с категориями
    QListWidget *category_list_;
    QWidget *table_container_;  //сюда будем помещать таблицы модулей

    int page_ = -1;

    QLineEdit *search_line_;

    QVector<QTableWidget *> tables;
    QVector<QWidget *> table_widgets;

    void update_selection(int i, int j);
private slots:
    //выбор страницы
    void select_page(int index);

    void category_selected();

    //сигнал переключения tab - чтобы запомнить в настройках
    void tab_current_changed(int index);
    void table_selection_changed();
    void table_double_clicked(int row, int column);

    //нажатие кнопки Add
    void pressed_add();

    //изменение строки текста поиска
    void text_changed(const QString &text);

};

#endif // DIALOGADDMODULE_H
