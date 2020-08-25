#include "qt_widgets.h"
#include "incl_cpp.h"
#include "interfaceguistring.h"
#include "interfaceitemstring.h"
#include "projectruntime.h"

//---------------------------------------------------------------------
InterfaceGuiString::InterfaceGuiString(InterfaceGuiPageCreator &input, InterfaceItemString *item)
    :InterfaceGui(input, item)
{
    insert_label(input);

    lineEdit_ = new QLineEdit(item->value_string());
    lineEdit_->setMinimumWidth(xclu::LINE_EDIT_WIDTH);

    //отслеживание изменений
    connect(lineEdit_, SIGNAL (textChanged(QString)), this, SLOT (on_value_changed()));

    bool inserted = false;
    //если нет опций - то вставляем только редактор строки
    if (item->options_choose_filesystem()) {
         //опции - кнопки выбора файла или папки

        //заголовок диалога - 2-й элемент описания (т.е. index==1)
        dialog_title_ = item->description(1);
        //фильтр файлов - 3-й элемент описания (т.е. index==2)
        file_filter_ = item->description(2);

        QHBoxLayout *layout = new QHBoxLayout;
        layout->setMargin(0);
        layout->addWidget(lineEdit_);

        //создаем кнопку
        QString button_title;
        if (item->options_choose_file()) button_title = tr("File...");
        if (item->options_choose_folder()) button_title = tr("Folder...");

        QPushButton *button = new QPushButton(button_title);
        //button->setMaximumWidth(xclu::BUTTON_WIDTH);
        //button->setToolTip(item->description());
        layout->addWidget(button);

        //реакция на нажатие
        if (item->options_choose_file()) {
            connect(button, SIGNAL (released()), this, SLOT (choose_file()));
        }
        if (item->options_choose_folder()) {
            connect(button, SIGNAL (released()), this, SLOT (choose_folder()));
        }

        //spacer, чтобы вправо spin не раздвигался
        /*QSpacerItem *spacer = new QSpacerItem(1,1);

        layout->addWidget(spin);
        layout->addItem(spacer);
        layout->setStretch(0,0);
        layout->setStretch(1,1);*/
        QWidget *holder = new QWidget;
        holder->setLayout(layout);

        //вставка на страницу, со сдвигом вниз
        insert_widget_next_line(holder, lineEdit_, input);
        inserted = true;
    }

    //просто вставка на страницу
    if (!inserted) {
        insert_widget_next_line(lineEdit_, lineEdit_, input);
        inserted = true;
    }

}

//---------------------------------------------------------------------
InterfaceGuiString::~InterfaceGuiString() {

}

//---------------------------------------------------------------------
//установка режима read_only - для out и блокировки констант при запуске проекта
void InterfaceGuiString::set_read_only(bool read_only) {
    //цвет фона
    InterfaceGui::set_read_only(read_only);

    lineEdit_->setReadOnly(read_only);
}

//---------------------------------------------------------------------
QString InterfaceGuiString::value() {
    return lineEdit_->text();
}

//---------------------------------------------------------------------
void InterfaceGuiString::set_value(QString v) {
    //проверяем, что значение не изменилось
    //(в противном случае, out-значение невозможно скопировать во время выполнения)
    if (value() != v) {
        lineEdit_->setText(v);
    }
}

//---------------------------------------------------------------------
void InterfaceGuiString::choose_file() {
    //запрашиваем и вычисляем относительный путь относительно пути к проекту
    //а если пустой - сказать про это
    //при этом, тут нельзя использовать xclu_assert - так как выпадет вся программа
    //ведь это идет обработка по нажатию кнопки, прямо в GUI
    QString proj_folder = RUNTIME.project_folder();
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
void InterfaceGuiString::choose_folder() {
    //запрашиваем и вычисляем относительный путь относительно пути к проекту, если он не пустой
    //а если пустой - сказать про это
    //при этом, тут нельзя использовать xclu_assert - так как выпадет вся программа
    //ведь это идет обработка по нажатию кнопки, прямо в GUI
    QString proj_folder = RUNTIME.project_folder();
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
