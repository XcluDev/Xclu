#ifndef DIALOGEDITLINK_H
#define DIALOGEDITLINK_H

#include <QDialog>

namespace Ui {
class DialogEditLink;
}

struct DialogEditLinkData {
    DialogEditLinkData(QString module_name, QString item_name, QString link, bool link_enabled) {
        this->module_name = module_name;
        this->item_name = item_name;
        this->link = link;
        this->link_enabled = link_enabled;
    }
    QString module_name;
    QString item_name;
    QString link;
    bool link_enabled = false;
};

class DialogEditLink : public QDialog
{
    Q_OBJECT

public:
    //Call this function for working with dialog
    //if returns not nullptr - then success and you can use dialog's value
    static DialogEditLink* call_dialog(const DialogEditLinkData &data);

    explicit DialogEditLink(QWidget *parent = nullptr);
    ~DialogEditLink();

    void set_data(const DialogEditLinkData &data);
    bool link_enabled();
    QString link();

private:
    Ui::DialogEditLink *ui;

};

#endif // DIALOGEDITLINK_H
