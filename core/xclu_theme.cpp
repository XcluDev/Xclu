#include "qt_widgets.h"
#include <QFontDatabase>
#include <QApplication>
#include "xclu_theme.h"
#include "incl_qtcpp.h"

//---------------------------------------------------------------------
QString font_family_values() {
    return "Courier New";
}

//---------------------------------------------------------------------
/*static*/ void XcluTheme::set_theme(QApplication *app) {
    //https://doc.qt.io/qt-5/stylesheet-syntax.html

    //включаем распространение стиля на все виджеты
    QCoreApplication::setAttribute(Qt::AA_UseStyleSheetPropagationInWidgetStyles, true);


    QString theme = //"Default";
    //"Combinear"; //темно-оранжевый, похож на исходный Default
    //"EasyCode";     //серый, простоват "детское"
    //"Geoo";    //темный, похож на исходный Default
    "Integrid"; //элегантный кремовый, только сделать основной шрифт черным (сейчас белый), и потолще scrollbar
    //"Medize"; //светло-голубой тон
    //"VisualScript"; //темно-морковный

    QString style_file_name = xclu::builtin_theme_folder() + xclu::builtin_theme_name() + ".qss";
    QFile file(style_file_name);
    xclu_assert(file.open(QFile::ReadOnly | QFile::Text), "Can't load theme from '" + style_file_name + "'");
    QString style_sheet = QLatin1String(file.readAll());


    //qApp->setStyleSheet(style_sheet);
    app->setStyleSheet(style_sheet);
}

//---------------------------------------------------------------------
/*static*/ void XcluTheme::set_theme(QMainWindow *window) {
    //https://doc.qt.io/qt-5/stylesheet.html
    //https://wiki.qt.io/How_to_Change_the_Background_Color_of_QWidget


    //ставим стиль
    //qApp->setStyleSheet("QGroupBox, QGroupBox * { color: red; }");
    //widget->setStyleSheet("background-color:#444444;");

  /*  QString style_file_name = xclu::builtin_folder() + "/theme.css";
    QFile file(style_file_name);
    xclu_assert(file.open(QFile::ReadOnly | QFile::Text), "Can't load theme from '" + style_file_name + "'");
    QString style_sheet = QLatin1String(file.readAll());

    window->setStyleSheet(style_sheet);
*/
    //qApp->setStyleSheet(style_sheet);
}

//---------------------------------------------------------------------
/*static*/ void XcluTheme::set_theme(QListWidget *list) {
    list->setAlternatingRowColors(true);
  /*  //https://doc.qt.io/qt-5/stylesheet-examples.html
    //https://doc.qt.io/qt-5/stylesheet-examples.html#customizing-qlistview
    list->setStyleSheet("background-color:#383838;"
                        "color: white;"
                        "selection-color: white;"
                        "selection-background-color: white;"// #5a7c99;"
                        );
                        */
}

//---------------------------------------------------------------------
//---------------------------------------------------------------------
//---------------------------------------------------------------------

namespace xclu {
//---------------------------------------------------------------------
//ставит шрифт не менее, чем уже стоит
void set_font_size(QWidget *widget, int size) {
   /* auto font = widget->font();
    if (font.pixelSize() < size) {
        font.setPixelSize(size);
    }
    widget->setFont(font);*/
}

//---------------------------------------------------------------------
//ставит цвет шрифта в gray и возвращает исходный цвет - чтобы его потом восстановить
QColor set_font_color_gray(QWidget *widget) {
    QPalette palette = widget->palette();
    QColor color = palette.color(widget->foregroundRole());
    palette.setColor(widget->foregroundRole(), Qt::gray);
    widget->setPalette(palette);
    return color;
}

//---------------------------------------------------------------------
//восстанавливает цвет шрифта
void reset_font_color(QWidget *widget, QColor color) {
    QPalette palette = widget->palette();
    palette.setColor(widget->foregroundRole(), color);
    widget->setPalette(palette);
}

//---------------------------------------------------------------------
//выдать в консоль Qt список доступных шрифтов
void print_fonts() {
    qDebug() << "Fonts:";
    QFontDatabase database;
    foreach (const QString &family, database.families()) {
        qDebug() << "  " << family;
        foreach (const QString &style, database.styles(family)) {
            QString sizes;
            foreach (int points, database.smoothSizes(family, style)) {
                sizes += QString::number(points) + " ";
            }
            qDebug() << "      " << style << " - " << sizes;

        }
    }
}

//---------------------------------------------------------------------
//папка со встроенными ресурсами - темы, общие XGUI
//это файлы ресурсов, поэтому путь начинается с ":/"
QString builtin_resources_folder() {
    return  ":/builtin_resources/";
}

 //папка с темами
QString builtin_themes_folder() {
    return builtin_resources_folder() + "themes/";
}

//имя выбранной темы
QString builtin_theme_name() {
    QString theme =
    "Integrid"; //элегантный кремовый, только сделать основной шрифт черным (сейчас белый), и потолще scrollbar

    //"Default";   //темная, наша кастомная тема
    //"Combinear"; //темно-оранжевый, похож на исходный Default
    //"EasyCode";     //серый, простоват "детское"
    //"Geoo";    //темный, похож на исходный Default
    //"Medize"; //светло-голубой тон
    //"VisualScript"; //темно-морковный
    return theme;
}

//выбранная тема
QString builtin_theme_folder() {

    return builtin_themes_folder() + builtin_theme_name() + "/";
}



//папка с иконками
QString builtin_icons_folder() {
    return builtin_theme_folder() + "icons/";
}

//---------------------------------------------------------------------
//папка с описанием встроенных модулей
//это файлы ресурсов, поэтому путь начинается с ":/"
QString builtin_modules_folder() {
#ifdef XCLU_DEPLOY
    //в режиме сборки Release-Deploy - это встроенные папки, и требуется добавить все в QRC
    //в в остальных режимах - это путь на диске
    return  ":/builtin_modules";
#else
    QFileInfo file("../Xclu/builtin_modules/");
    return file.canonicalFilePath();
#endif

}

//---------------------------------------------------------------------
//Файл с описанием интерфейса страницы General - добавляется во все модули
QString general_page_file() { return builtin_resources_folder() + "general_page" + XGUI_ext(); }

//---------------------------------------------------------------------
//Расширение файлов для описания интерфейса
QString XGUI_ext() {return ".xgui";}

//---------------------------------------------------------------------
QHBoxLayout *hlayout(int margin, QWidget *widget1, int stretch1,
                     QWidget *widget2, int stretch2,
                     QWidget *widget3, int stretch3,
                     QWidget *widget4, int stretch4,
                     QWidget *widget5, int stretch5) {
    QHBoxLayout *layout = new QHBoxLayout;
    if (margin != -1) {
        layout->setMargin(margin);
    }
    if (widget1) layout->addWidget(widget1, stretch1);
    if (widget2) layout->addWidget(widget2, stretch2);
    if (widget3) layout->addWidget(widget3, stretch3);
    if (widget4) layout->addWidget(widget4, stretch4);
    if (widget5) layout->addWidget(widget5, stretch5);
    return layout;
}

//---------------------------------------------------------------------
QVBoxLayout *vlayout(int margin, QWidget *widget1, int stretch1,
                     QWidget *widget2, int stretch2,
                     QWidget *widget3, int stretch3,
                     QWidget *widget4, int stretch4,
                     QWidget *widget5, int stretch5) {
    QVBoxLayout *layout = new QVBoxLayout;
    if (margin != -1) {
        layout->setMargin(margin);
    }
    if (widget1) layout->addWidget(widget1, stretch1);
    if (widget2) layout->addWidget(widget2, stretch2);
    if (widget3) layout->addWidget(widget3, stretch3);
    if (widget4) layout->addWidget(widget4, stretch4);
    if (widget5) layout->addWidget(widget5, stretch5);
    return layout;
}

//---------------------------------------------------------------------
QWidget *hwidget(int margin, QWidget *widget1, int stretch1,
                 QWidget *widget2, int stretch2,
                 QWidget *widget3, int stretch3,
                 QWidget *widget4, int stretch4,
                 QWidget *widget5, int stretch5
                 ) {

    QWidget *widget = new QWidget;
    widget->setLayout(hlayout(margin, widget1, stretch1,
                              widget2, stretch2,
                              widget3, stretch3,
                              widget4, stretch4,
                              widget5, stretch5));
    return widget;
}

//---------------------------------------------------------------------
QWidget *vwidget(int margin, QWidget *widget1, int stretch1,
                 QWidget *widget2, int stretch2,
                 QWidget *widget3, int stretch3,
                 QWidget *widget4, int stretch4,
                 QWidget *widget5, int stretch5
                 ) {

    QWidget *widget = new QWidget;
    widget->setLayout(vlayout(margin, widget1, stretch1,
                              widget2, stretch2,
                              widget3, stretch3,
                              widget4, stretch4,
                              widget5, stretch5));
    return widget;
}

//---------------------------------------------------------------------



};

