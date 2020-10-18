#ifndef DIALOGEDITLINKS_H
#define DIALOGEDITLINKS_H

#include <QDialog>
#include "xlink.h"

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

    struct Links {
        QVector<XLink> links;
        QVector<QString> vars;
        bool ok = false;
    };

    Links get_list();

private slots:
    void on_button_check_links_clicked();
    void on_button_ok_clicked();
    void on_button_cancel_clicked();
};

#endif // DIALOGEDITLINKS_H
