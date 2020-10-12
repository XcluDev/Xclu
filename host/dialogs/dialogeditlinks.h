#ifndef DIALOGEDITLINKS_H
#define DIALOGEDITLINKS_H

#include <QDialog>

namespace Ui {
class DialogEditLinks;
}

class Module;

class DialogEditLinks : public QDialog
{
    Q_OBJECT

public:
    //Call this function for working with dialog
    //if returns not nullptr - then success and you can use dialog's value
    static void call_dialog(Module *module);

    explicit DialogEditLinks(QWidget *parent = nullptr);
    ~DialogEditLinks();

    void set_module(Module *module);
private:
    Ui::DialogEditLinks *ui;
    Module *module_ = nullptr;

private slots:
    void on_buttonBox_accepted();
};

#endif // DIALOGEDITLINKS_H
