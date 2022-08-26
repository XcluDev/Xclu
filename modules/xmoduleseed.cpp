#include "xmoduleseed.h"
#include "incl_cpp.h"

//строки описания страницы General
//загружается при первом требовании и затем хранится в памяти тут
QStringList ModuleInfo_general_page_;

//---------------------------------------------------------------------
/*static*/ ModuleSeed* ModuleSeed::load_module(QString folder, QString category_name, QString module_name) {
    //создаем модуль и пытаемся в него загрузить информацию
    ModuleSeed* module = new ModuleSeed();
    try {
        module->load_module_from_folder(folder, category_name, module_name);
    }
    catch (XException &e) {
        xc_console_warning(QString("Error reading description for module from folder '%1':\n%2")
                                              .arg(folder).arg(e.whatQt()));
        //xc_message_box(QString("Error reading description for module from folder '%1':\n%2")
        //                 .arg(folder).arg(e.whatQt()));
        delete module;
        return nullptr;
    }
    return module;
}

//---------------------------------------------------------------------
ModuleSeed::ModuleSeed()
{

}

//---------------------------------------------------------------------
void ModuleSeed::load_module_from_folder(QString folder, QString category_name, QString module_name) {
    //qDebug() << "loading " + folder;
    folder_ = folder;
    description_file_ = folder_ + "/description" + xc_XGUI_ext();

    //очищаем текущее описание
    description = ModuleDescription();
    gui_lines_.clear();

    //считываем описание модуля,
    //а остальные непустые строки и не комментарии - записываем в lines_
    QFile file(description_file_);
    if(!file.open(QIODevice::ReadOnly)) {
        xc_exception(file.errorString());
    }
    //ставим класс и категорию, если они не пустые
    //нельзя их просто установить - так как при парсинге они еще выставляют подсказки для name
    if (!category_name.isEmpty()) {
        description.parse_module_header_line(description.field_category(), category_name);
    }
    if (!module_name.isEmpty()) {
        description.parse_module_header_line(description.field_class_name(), module_name);
    }

    QTextStream in(&file);
    while(!in.atEnd()) {
        QString line = in.readLine();
        line=line.trimmed();
        bool header = description.parse_module_header_line(line);
        if (!header && !line.isEmpty() && line.at(0)!='#') {
            gui_lines_.append(line);
            //qDebug() << "      " << line;
        }
    }
    file.close();

    //проверка, что описание правильное
    xc_assert(description.is_complete(), "Module description is not complete");
}

//---------------------------------------------------------------------
//Загрузить GUI-файл, отбросив комментарии и сделать trim строк
//применяется при считывании описания общей страницы General.
QStringList ModuleSeed::read_gui_file(QString file_name) {
    QFile file(file_name);
    xc_assert(file.open(QIODevice::ReadOnly), "Can't open " + file_name);
    QTextStream in(&file);
    QStringList list;
    while(!in.atEnd()) {
        QString line = in.readLine();
        line=line.trimmed();
        if (!line.isEmpty() && line.at(0)!='#') {
            list.append(line);
        }
    }
    file.close();
    return list;
}

//---------------------------------------------------------------------
//строки с описанием GUI, не включающие описание модуля, пустые и комментарии
//так же, с добавлением General Page
QStringList ModuleSeed::gui_lines() const {
    //Загрузить описание страницы General, если еще не загружено
    if (ModuleInfo_general_page_.isEmpty()) {
        ModuleInfo_general_page_ = read_gui_file(xc_general_page_file());
        xc_assert(!ModuleInfo_general_page_.isEmpty(), "General file description '" + xc_general_page_file() + "' is empty");
    }

    QStringList list = gui_lines_;

    //добавление страницы General
    list.append(ModuleInfo_general_page_);
    return list;
}

//---------------------------------------------------------------------
//Help
//мы считываем его при необходимости, при первом обращении к help(), и затем храним
QString ModuleSeed::help() {
    if (!help_was_read_) {
        help_was_read_ = true;
        QString help_file = folder_ + "/help.md";
        QFile file(help_file);

        QString text;
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            text = in.readAll();
        }
        help_ = text;
    }
    return help_;
}

//---------------------------------------------------------------------
