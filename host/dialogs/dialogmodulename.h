#pragma once

#include <QDialog>

namespace Ui {
class DialogModuleName;
}

class DialogModuleName : public QDialog
{
    Q_OBJECT

public:
    //Call this function for working with dialog
    //if returns not nullptr - then success and you can use dialog's value
    static DialogModuleName* call_dialog(QWidget *parent, QString name_hint);

    explicit DialogModuleName(QWidget *parent = nullptr);
    virtual ~DialogModuleName();

    void set_name_hint(QString name_hint);
    QString name_hint();
private:
    Ui::DialogModuleName *ui;
};

