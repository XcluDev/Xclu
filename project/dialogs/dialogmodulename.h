#ifndef DIALOGMODULENAME_H
#define DIALOGMODULENAME_H

#include <QDialog>

namespace Ui {
class DialogModuleName;
}

class DialogModuleName : public QDialog
{
    Q_OBJECT

public:
    //Вызывайте эту функцию для работы с диалогом,
    //если не nullptr - то диалог успешен и можно брать значения из него
    static DialogModuleName* call_dialog(QWidget *parent, QString name_hint);

    explicit DialogModuleName(QWidget *parent = nullptr);
    ~DialogModuleName();

    void set_name_hint(QString name_hint);
    QString name_hint();
private:
    Ui::DialogModuleName *ui;
};

#endif // DIALOGMODULENAME_H
