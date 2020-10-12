#ifndef DIALOGEDITLINK_H
#define DIALOGEDITLINK_H

#include <QDialog>

namespace Ui {
class DialogEditLink;
}

class XItem;

struct DialogEditLinkData {
    DialogEditLinkData(QString module_name, XItem *item) {
        this->module_name = module_name;
        this->item = item;
    }
    QString module_name;
    XItem *item;
};

class DialogEditLink : public QDialog
{
    Q_OBJECT

public:
    //Call this function for working with dialog
    //if returns not nullptr - then success and you can use dialog's value
    static void call_dialog(const DialogEditLinkData &data);

    explicit DialogEditLink(QWidget *parent = nullptr);
    ~DialogEditLink();

    void set_data(const DialogEditLinkData &data);
    bool link_enabled();
    QString link();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::DialogEditLink *ui;
    XItem *item_ = nullptr;

};

#endif // DIALOGEDITLINK_H
