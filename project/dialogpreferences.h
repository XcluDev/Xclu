#ifndef DIALOGPREFERENCES_H
#define DIALOGPREFERENCES_H

//Диалог настройки Xclu

#include <QDialog>

namespace Ui {
class DialogPreferences;
}

class DialogPreferences : public QDialog
{
    Q_OBJECT

public:
    explicit DialogPreferences(QWidget *parent = nullptr);
    ~DialogPreferences();

private:
    Ui::DialogPreferences *ui;
};

#endif // DIALOGPREFERENCES_H
