#include "qt_widgets.h"
#include "incl_cpp.h"
#include "xguistring.h"
#include "xitemstring.h"
#include "xcore.h"

//---------------------------------------------------------------------
/*
Widget structures for different controls:

float, int:     0 label, 1 control,  2 measure unit, 3 slider,     4 link label
checkbox:       0 label, 1 control                                 4 link label
checkbox_group: 0--------1 control,  2---------------3 horiz.line  4 link label
separator:      0 "control"
button:                  1 control                                 4 link label
string, text:   0 label                                            4 link label
                0 -------------------------------------------------4 control
object:         0 label                                            4 link label
                0--------------------2 thumbnail     3-------------4 description
*/

//---------------------------------------------------------------------
XGuiString::XGuiString(XGuiPageBuilder &page_builder, XItemString *item)
    :XGui(page_builder, item)
{


    lineEdit_ = new QLineEdit(item->value_string());
    lineEdit_->setMinimumWidth(xclu::LINE_EDIT_WIDTH);

    //button for choosing file or folder
    QPushButton *button_choosing = nullptr;

    if (item->options_choose_filesystem()) {
        //dialog title - second description item, with index==1
        dialog_title_ = item->description(1);
        //file filter - third description item, with index==2
        file_filter_ = item->description(2);

        QString button_title;
        if (item->options_choose_file()) button_title = tr("File...");
        if (item->options_choose_folder()) button_title = tr("Folder...");

        button_choosing = new QPushButton(button_title);
        button_choosing->setMaximumWidth(xclu::BUTTON_CHOOSE_WIDTH);

        //button->setMaximumWidth(xclu::BUTTON_WIDTH);
        //button->setToolTip(item->description());

        //reaction on pressing button
        if (item->options_choose_file()) {
            connect(button_choosing, SIGNAL (released()), this, SLOT (choose_file()));
        }
        if (item->options_choose_folder()) {
            connect(button_choosing, SIGNAL (released()), this, SLOT (choose_folder()));
        }
    }

    //insert to page
    if (button_choosing) {
        insert_widgets(page_builder,
                       lineEdit_,
                       new_label(), 3, false,
                       nullptr, 1, false,
                       new_label_link(), 1, true,
                       lineEdit_, 4, false,
                       button_choosing, 1, true
                       );
    }
    else {
        insert_widgets(page_builder,
                       lineEdit_,
                       new_label(), 3, false,
                       nullptr, 1, false,
                       new_label_link(), 1, true,
                       lineEdit_, 5, true
                       );
    }


    //track changes
    connect(lineEdit_, SIGNAL (textChanged(QString)), this, SLOT (on_value_changed()));

}

//---------------------------------------------------------------------
XGuiString::~XGuiString() {

}

//---------------------------------------------------------------------
//установка режима read_only - для out и блокировки констант при запуске проекта
void XGuiString::set_read_only_(bool read_only) {
    lineEdit_->setReadOnly(read_only);
    xclu::widget_update_css(lineEdit_);
}

//---------------------------------------------------------------------
QString XGuiString::value() {
    return lineEdit_->text();
}

//---------------------------------------------------------------------
void XGuiString::set_value(QString v) {
    //проверяем, что значение не изменилось
    //(в противном случае, out-значение невозможно скопировать во время выполнения)
    if (value() != v) {
        lineEdit_->setText(v);
    }
}

//---------------------------------------------------------------------
void XGuiString::choose_file() {
    //запрашиваем и вычисляем относительный путь относительно пути к проекту
    //а если пустой - сказать про это
    //при этом, тут нельзя использовать xclu_assert - так как выпадет вся программа
    //ведь это идет обработка по нажатию кнопки, прямо в GUI
    QString proj_folder = XCORE.project_folder();
    if (proj_folder.isEmpty()) {
        xclu_message_box("To compute relative path for a file we will need the project path.\nPlease save a project before choosing a file");
        return;
    }

    QString fileName = QFileDialog::getOpenFileName(this, dialog_title_, value(), file_filter_);
    if (!fileName.isEmpty()) {

        QDir dir(proj_folder);
        fileName = dir.relativeFilePath(fileName);
        set_value(fileName);
    }
}

//---------------------------------------------------------------------
void XGuiString::choose_folder() {
    //запрашиваем и вычисляем относительный путь относительно пути к проекту, если он не пустой
    //а если пустой - сказать про это
    //при этом, тут нельзя использовать xclu_assert - так как выпадет вся программа
    //ведь это идет обработка по нажатию кнопки, прямо в GUI
    QString proj_folder = XCORE.project_folder();
    if (proj_folder.isEmpty()) {
        xclu_message_box("To compute relative path for a folder we will need the project path.\nPlease save a project before choosing a folder");
        return;
    }

    QString folder = QFileDialog::getExistingDirectory(this, dialog_title_,
                                                    value(),
                                                    QFileDialog::ShowDirsOnly
                                                    | QFileDialog::DontResolveSymlinks);

    if (!folder.isEmpty()) {

        QDir dir(proj_folder);
        folder = dir.relativeFilePath(folder);

        set_value(folder);
    }
}

//---------------------------------------------------------------------
