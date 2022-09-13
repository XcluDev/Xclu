#pragma once

//Диалог переименования модуля

#include <QDialog>

QT_BEGIN_NAMESPACE
class QLabel;
class QLineEdit;
class QPushButton;
QT_END_NAMESPACE

class DialogRenameModule : public QDialog
{
    Q_OBJECT

public:
    //Вызывайте эту функцию для работы с диалогом:
    static bool call_dialog(QString &name, QWidget *parent);

    DialogRenameModule(QWidget *parent = nullptr);

    void set_name(QString name);
    QString get_name();
private:
    QLineEdit *lineEdit;
    QLabel *statusLabel;
    QString name_;

private slots:
    void pressed_ok();

};

