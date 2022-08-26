#include "qt_widgets.h"
#include "incl_cpp.h"
#include "dialogaddmodule.h"
#include "xmodulesfactory.h"

DialogAddModule *D_ADD_MODULE = 0;


//---------------------------------------------------------------------
//Call this function for working with dialog
//if returns not nullptr - then success and you can use dialog's value
/*static*/ DialogAddModule* DialogAddModule::call_dialog(QWidget *parent) {
    //Внимание, тут parent только один раз задается
    if (!D_ADD_MODULE) {
        D_ADD_MODULE = new DialogAddModule(parent);
    }
    auto *dialog = D_ADD_MODULE;
    int result = dialog->exec();
    if (result == QDialog::Accepted) {
        return dialog;
    }

    return nullptr;
}

//---------------------------------------------------------------------
DialogAddModule::DialogAddModule(QWidget *parent)
    : QDialog(parent)
{
    //Cчитывание запомненного tab из настроек приложения
    //это нужно тут сделать, так как потом вызовется tab_current_changed

    //По умолчанию - это категория "All"
    QString All = ModulesFactory::All_Category_Name();
    QString tab_name = Settings::gets(Settings::dialogaddmodule_tab(), "All");
    int show_implemented = Settings::geti(Settings::dialogaddmodule_show_implemented(), 1);
    //qDebug() << "tab index stored" << tab_index;

    //список категорий
    category_list_ = new QListWidget;
    XcluTheme::set_theme(category_list_);
    category_list_->setMinimumWidth(xclu::add_module_categories_list_minimum_width);
    category_list_->setMaximumWidth(xclu::add_module_categories_list_maximum_width);
    xclu::set_font_size(category_list_, xclu::main_font_size);
    connect(category_list_, SIGNAL (itemSelectionChanged()), this, SLOT (category_selected()));

    //добавляем метку
    QWidget *categories = xclu::vwidget(0,
                                        new QLabel(tr("Categories")), 0,
                                        category_list_, 0);



    //контейнер с таблицами для каждой категории
    //таблицам делается setVisible, чтобы показывать только одну нужную в данный момент
    table_container_ = xclu::vwidget(0);

    // Create categories list
    int N = FACTORY.categories();
    for (int i=0; i<N; i++) {
        int size = category_size(i, show_implemented);
        if (size > 0) {
            QString name = FACTORY.category_name(i);
            QListWidgetItem *item = new QListWidgetItem(QString("%1 (%2)").arg(name).arg(size));
            QFont originalFont = item->font();
            //шрифт bold
            originalFont.setBold(true);
            item->setFont(originalFont);
            category_list_->addItem(item);
            category_names_.append(name);
            category_indices_.append(i);
        }
    }

    // Create table for each category
    int n = category_names_.size();
    tables.resize(n);
    table_widgets.resize(n);
    for (int k=0; k<n; k++) {
        int i = category_indices_[k];
        QTableWidget *table = create_table_for_category(i, show_implemented);
        //добавляем метку
        QWidget *table_widget = xclu::vwidget(0, new QLabel(category_names_[k]), 0, table, 0);

        table_widget->setVisible(false);
        tables[k] = table;
        table_widgets[k] = table_widget;
        table_container_->layout()->addWidget(table_widget);

        xclu::set_font_size(table_widget, xclu::main_font_size);
    }


    //Строка поиска и кнопки Add, Cancel
    QPushButton *add_button;
    QPushButton *cancel_button;

    QWidget *buttonBox = xclu::hwidget(0,
                                       new QLabel("Search:"), 0,
                                       search_line_ = new QLineEdit(), 0,
                                       show_implemented_checkbox_ = new QCheckBox("Show implemented"),0,
                                       new QLabel(""),10,
                                       add_button = new QPushButton(tr("Add...")), 0,
                                       cancel_button = new QPushButton(tr("Cancel")),0
                                       );
    xclu::set_font_size(buttonBox, xclu::main_font_size);

    //search_line_->setMinimumWidth(xclu::add_module_categories_list_minimum_width);
    //search_line_->setMaximumWidth(xclu::add_module_categories_list_maximum_width);
    connect(search_line_, &QLineEdit::textChanged, this, &DialogAddModule::text_changed);

    connect(add_button, &QPushButton::released, this, &DialogAddModule::pressed_add);
    connect(cancel_button, &QPushButton::released, this, &QDialog::reject);

    // Show implemented
    show_implemented_checkbox_->setCheckState(show_implemented?Qt::Checked:Qt::Unchecked);
    connect(show_implemented_checkbox_, &QCheckBox::stateChanged, this, &DialogAddModule::show_implementing_changed);

    //Сборка layout диалога
    setLayout(xclu::vlayout(-1,
                            xclu::hwidget(0,
                                          categories, 0,
                                          table_container_, 10),
                            0, buttonBox, 0)
              );

    //Заголовок
    setWindowTitle(tr("Choose a Module to Add"));

    //установка считанного tab
    page_ = -1;
    int page = -1;
    if (!tab_name.isEmpty()) {
        for (int i=0; i<category_list_->count(); i++) {
            if (category_list_->item(i)->text() == tab_name) {
                page = i;
                //tabs->setCurrentIndex(i);
                break;
            }
        }
    }
    if (page != -1) {
        category_list_->setCurrentRow(page);
    }
}

//---------------------------------------------------------------------
int DialogAddModule::category_size(int i, bool show_implemented) {
    int N = FACTORY.category_size(i);
    int n = 0;
    for (int j=0; j<N; j++) {
        QString module_name = FACTORY.category_module_type(i,j);
        auto *seed = FACTORY.get_module(module_name);
        if (seed) {
            bool is_implemented = seed->description.is_implemented();
            if (!show_implemented || (show_implemented && is_implemented)) {
                n++;
            }
        }
    }
    return n;
}

//---------------------------------------------------------------------
QTableWidget *DialogAddModule::create_table_for_category(int i, bool show_implemented) {
    int n = category_size(i, show_implemented);
    QTableWidget *table = new QTableWidget(n, 2);

    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    //table->setAlternatingRowColors(true);
    table->verticalHeader()->hide();
    table->horizontalHeader()->hide();
    table->horizontalScrollBar()->hide();
    table->setMinimumSize(600,400);     //TODO параметр - размеры таблицы
    table->setColumnWidth(0, 250);
    //table->setColumnWidth(1, 450);

    connect(table, &QTableWidget::itemSelectionChanged, this, &DialogAddModule::table_selection_changed);
    connect(table, &QTableWidget::cellDoubleClicked, this, &DialogAddModule::table_double_clicked);


    //растягивание второго столбца
    table->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);

    int N = FACTORY.category_size(i);
    int j = 0;
    for (int k=0; k<N; k++) {
        QString module_name = FACTORY.category_module_type(i,k);
        auto *seed = FACTORY.get_module(module_name);
        if (seed) {
            bool is_implemented = seed->description.is_implemented();
            if (!show_implemented || (show_implemented && is_implemented)) {
                //Имя
                QTableWidgetItem *name = new QTableWidgetItem(module_name);
                //выключаем редактирование
                name->setFlags(name->flags() ^ Qt::ItemIsEditable);
                //если реализован, то ставим шрифт bold
                if (is_implemented) {
                    QFont originalFont = name->font();
                    originalFont.setBold(true);
                    name->setFont(originalFont);
                }
                table->setItem(j, 0, name);
                //Описание
                QTableWidgetItem *descr = new QTableWidgetItem(seed->description.description);
                descr->setFlags(descr->flags() ^ Qt::ItemIsEditable); // ^ Qt::ItemIsSelectable);
                table->setItem(j, 1, descr);

                // Increase counter
                j++;

            }
        }
    }
    return table;
}

//---------------------------------------------------------------------
//выбор страницы
void DialogAddModule::select_page(int index) {
    if (index != page_) {
        if (page_ != -1) {
            //выключаем старую
            table_widgets[page_]->setVisible(false);
        }
        page_ = index;
        if (page_ != -1) {
            //включаем новую
            table_widgets[page_]->setVisible(true);
            //выделить те, которые отвечают за текст
            text_changed(search_line_->text());
        }
        tab_current_changed(index);
    }
}

//---------------------------------------------------------------------
void DialogAddModule::category_selected() {
    select_page(category_list_->currentIndex().row());
}

//---------------------------------------------------------------------
//сигнал переключения tab - чтобы запомнить в настройках
void DialogAddModule::tab_current_changed(int index) {
    //Запись tab в настройки приложения
    //qDebug() << "tab_current_changed" << index;
    if (index >= 0) {
        QString tab_name = category_list_->item(index)->text();
        Settings::sets(Settings::dialogaddmodule_tab(), tab_name);
    }
}

//---------------------------------------------------------------------
void DialogAddModule::update_selection(int i, int j) {
    selected_category = i;
    selected_item = j;
    selected_type = FACTORY.category_module_type(i, j);
}

//---------------------------------------------------------------------
void DialogAddModule::table_selection_changed() {
    update_selection(page_, tables[page_]->currentRow());
}

//---------------------------------------------------------------------
void DialogAddModule::table_double_clicked(int row, int) {
    if (row == -1) return;
    update_selection(page_, row);
    emit QDialog::done(Accepted);
}

//---------------------------------------------------------------------
void DialogAddModule::pressed_add() {
    if (selected_type.isEmpty()) {
        return;
    }
    emit QDialog::done(Accepted);
}

//---------------------------------------------------------------------
//изменение строки текста поиска
void DialogAddModule::text_changed(const QString &text) {
    //qDebug() << "search " << text;
    if (page_ >= 0) {
        QString text_lower = text.toLower();
        QTableWidget *table = tables[page_];
        xc_assert(table, "DialogAddModule::text_changed - null table");
        for (int i=0; i<table->rowCount(); i++) {
            QTableWidgetItem *item = table->item(i, 0);
            xc_assert(item, "DialogAddModule::text_changed - null item");
            QString name = item->text();
            bool visible = name.toLower().contains(text_lower);
            table->setRowHidden(i, !visible);
        }
    }
}

//---------------------------------------------------------------------
// Changed Show implementing checkbox
void DialogAddModule::show_implementing_changed(int state) {
    //qDebug() << "show_implementing_changed " << state;
    int show_implemented = (state == Qt::Checked)?1:0;
    Settings::seti(Settings::dialogaddmodule_show_implemented(), show_implemented);

    xc_message_box("Restart Xclu to apply this change.");
}

//---------------------------------------------------------------------
