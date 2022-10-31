#ifndef DIALOGEDITUI_H
#define DIALOGEDITUI_H

#include <QDialog>

namespace Ui {
class DialogEditUI;
}

class DialogEditUI : public QDialog
{
    Q_OBJECT

public:
    static void call_dialog(QWidget *parent);

    explicit DialogEditUI(QWidget *parent = nullptr);
    ~DialogEditUI();

private:
    Ui::DialogEditUI *ui;
};

#endif // DIALOGEDITUI_H
