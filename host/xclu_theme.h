#ifndef XCLU_GUI_CONST_H
#define XCLU_GUI_CONST_H

#include "incl_h.h"

//Пути к встроенным ресурсам
//Параметры для GUI и имена файлов, а также вспомогательные функции для GUI

class QWidget;
class QColor;
class QHBoxLayout;
class QVBoxLayout;
class QDialogWindow;
class QMainWindow;
class QListWidget;
class QApplication;


//Класс для задания темы окнам и элементам
class XcluTheme {
public:
    static void set_theme(QApplication *app);

    static void set_theme(QMainWindow *window);
    static void set_theme(QListWidget *list);

};

//Константы и вспомогательные функции
namespace xclu {

//тема
QString builtin_themes_folder();    //папка с темами
QString builtin_theme_folder();     //выбранная тема
QString builtin_theme_name();       //имя выбранной темы


//папка с иконками
QString builtin_icons_folder();

//Update widget style (used for read-only on/off)
void widget_update_css(QWidget *widget);

const int gui_page_link_column = 3;   //column for link

const int gui_page_grid_margin = -1;     //margin, если -1 - не ставить
const int gui_page_grid_spacing = 10;    //расстояние между элементами в сетке GUI, -1 - не ставить

const int LABEL_WIDTH_MIN = 80;  //ширина label

const int LINE_EDIT_WIDTH = 200;  //ширина строки
const int COMBO_WIDTH_MIN = 150;  //ширина enum
const int COMBO_WIDTH_MAX = 300;
const int BUTTON_WIDTH = 200;      //ширина button

const int SPIN_WIDTH = 120;      //ширина int, float

const int SEPARATOR_HEIGHT = 15;  //высота сепаратора

//Размеры шрифта
const int main_font_size = 18;       //основной размер шрифта
const int strings_font_size = 18;    //шрифт для строк и текстов
const int help_font_size = 18;    //размер шрифта справки
const int console_font_size = 15;    //размер шрифта консоли с логами

//Тип шрифта
//static QString font_family_main() { return "Courier New"; }
QString font_family_values();

//Диалог добавления нового модуля
const int add_module_categories_list_minimum_width = 150; //ширина списка категорий
const int add_module_categories_list_maximum_width = 250;

//максимальный размер для вывода изображения в preview
const int image_preview_small_w=256; //256;
const int image_preview_small_h=256; //128;
const int image_preview_medium_w=384;
const int image_preview_medium_h=384;
const int image_preview_large_w=512;
const int image_preview_large_h=512;



//GUI ------------------------------------------------
//ставит шрифт размером не менее, чем уже стоит
void set_font_size(QWidget *widget, int size);

//ставит цвет шрифта в gray и возвращает исходный цвет - чтобы его потом восстановить
QColor set_font_color_gray(QWidget *widget);
//восстанавливает цвет шрифта
void reset_font_color(QWidget *widget, QColor color);

//выдать в консоль Qt список доступных шрифтов
void print_fonts();

//QWidget с горизонтальным или вертикальным layout из элементов,
//либо просто QHBoxLayout или QVBoxLayout из элементов
//margin == -1 - значит не менять Margin
//Например, чтобы добавить к виджету сверху метку, можно вызвать так:
//QWidget *categories = xclu::vlayout(-1,
//                                    new QLabel(tr("Categories")), 0,
//                                    category_list_,0);
//И даже так:
//QGroupBox *image_protection = new QGroupBox("Image");
//QLineEdit *line_folder_;
//QPushButton *line_folder_button;
//image_protection->setLayout(vlayout(-1,
//                                    new QLabel("Folder"), 0,
//                                    hwidget(0,
//                                        line_folder_ = new QLineEdit("Press button to choose folder --->"), 10,
//                                        line_folder_button = new QPushButton("..."), 0
//                                           ), 0,
//                                    hwidget(0, new QPushButton("Make"),0, new QLabel(""), 10), 0
//                                    )
//                            );

//TODO           vbox->addStretch(1); - если вставляется нулевой объект с ненулевым стретчем, то это addStretch

QWidget *hwidget(int margin = -1, QWidget *widget1 = nullptr, int stretch1 = 0,
                 QWidget *widget2 = nullptr, int stretch2 = 0,
                 QWidget *widget3 = nullptr, int stretch3 = 0,
                 QWidget *widget4 = nullptr, int stretch4 = 0,
                 QWidget *widget5 = nullptr, int stretch5 = 0);
QWidget *vwidget(int margin = -1, QWidget *widget1 = nullptr, int stretch1 = 0,
                 QWidget *widget2 = nullptr, int stretch2 = 0,
                 QWidget *widget3 = nullptr, int stretch3 = 0,
                 QWidget *widget4 = nullptr, int stretch4 = 0,
                 QWidget *widget5 = nullptr, int stretch5 = 0);
QHBoxLayout *hlayout(int margin = -1, QWidget *widget1 = nullptr, int stretch1 = 0,
                     QWidget *widget2 = nullptr, int stretch2 = 0,
                     QWidget *widget3 = nullptr, int stretch3 = 0,
                     QWidget *widget4 = nullptr, int stretch4 = 0,
                     QWidget *widget5 = nullptr, int stretch5 = 0);
QVBoxLayout *vlayout(int margin = -1, QWidget *widget1 = nullptr, int stretch1 = 0,
                     QWidget *widget2 = nullptr, int stretch2 = 0,
                     QWidget *widget3 = nullptr, int stretch3 = 0,
                     QWidget *widget4 = nullptr, int stretch4 = 0,
                     QWidget *widget5 = nullptr, int stretch5 = 0);



};  //namespace xclu


#endif // XCLU_GUI_CONST_H
