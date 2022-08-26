#include <QApplication>
#include "qt_widgets.h"
#include <QScreen>
#include "xmodulewindow.h"

#include "incl_cpp.h"
#include "registrarxmodule.h"
#include "project_props.h"
#include "module.h"
#include "xobject.h"
#include "xraster.h"
#include "xobjectimage.h"

//registering module implementation
REGISTER_XMODULE(Window)

//---------------------------------------------------------------------
XModuleWindow::XModuleWindow(QString class_name)
    :XClass(class_name)
{

}

//---------------------------------------------------------------------
XModuleWindow::~XModuleWindow()
{

}

//---------------------------------------------------------------------
void XModuleWindow::set_size(int w, int h) {
    window_->resize(w, h);
}

//---------------------------------------------------------------------
void XModuleWindow::set_position(int x, int y) {
    //window_->setGeometry(x, y, window_->width(), window_->height());
    window_->move(x, y);
}

//---------------------------------------------------------------------
//получить экран в зависимости от настроек
QScreen *XModuleWindow::get_screen() {
    return QGuiApplication::primaryScreen();
/*    WindowScreen screen = WindowScreen(i_screen"));
    switch (screen) {
    case WindowScreen_Default:
        return QGuiApplication::primaryScreen();
        break;
    case WindowScreen_Custom: {
            int index = i_screen_index");
            auto screens = QGuiApplication::screens();
            xc_assert(index>=0 && index<screens.count(),
                        QString("Bad screen index %1").arg(index));
            return screens.at(index);
        }
        break;
    default:
        xc_exception("XModuleWindow - Unknown screen specifier");
    }

    //если что-то пошло не так, возвращаем экран по умолчанию
    return QGuiApplication::primaryScreen();*/
}

//---------------------------------------------------------------------
//создание и установка начальных настроек окна
void XModuleWindow::setup_window() {
    //Создание окна на нужном экране
    //QScreen *screen = get_screen();
    window_.reset(new QMainWindow());


    //??????????
    //window_.setAttribute(Qt::WA_DeleteOnClose); //???
    //window_.setUnifiedTitleAndToolBarOnMac(true);

    //??????????
    //connect(window_.data(), &QMainWindow::visibleChanged, this, &XModuleWindow::on_visibleChanged);
    //connect(window_.data(), &QMainWindow::windowStateChanged, this, &XModuleWindow::on_windowStateChanged);

    notify_visible_change_ = false;

    //Borderless
    //Qt::FramelessWindowHint

    //шрифт
    if (gete_font_size() == font_size_Custom) {    //Custom
        int font_size = geti_font_size_pix();
        auto font = window_->font();
        font.setPixelSize(font_size);
        window_->setFont(font);
    }

    //Структура окна
    create_layouts();

    //need apply value of starting_mode
    need_apply_initial_state_ = true;

}

//---------------------------------------------------------------------
//прочитать данные из интерфейса и использовать для управления окном
//он использует was_changed - поэтому, при старте всегда эти значения будут использованы (при старте все переменные was_changed)
void XModuleWindow::update_window() {
    //проверка, что пользователь закрыл окно
    if (notify_visible_change_) {
        notify_visible_change_ = false;
        if (geti_visible() && !window_->isVisible()) {
            //пользователь нажал кнопку закрытия окна или другой сигнал для закрытия
            auto on_close = gete_on_close();
            switch (on_close) {
            case  on_close_Ignore:
                window_->setVisible(true);  //делаем видимым
                break;
            case on_close_Stop:
                set_stop_out(); //команда остановки
                break;
            default:
                xc_exception("XModuleWindow - Unknown on_close specifier");
            }

        }
    }

    //title
    if (was_changed_title()) {
        window_->setWindowTitle(gets_title());
    }

    //TODO!!!!!!!!!!!!!!!!!!!!!!!!!! если меняем размер и положение - то сразу установить setGeometry
    //Size
    bool size_changed = false;
    auto size = gete_size();
    if (was_changed_size()
            || (size == size_Custom && (was_changed_size_x() || was_changed_size_y()))) {
        size_changed = true;
        switch (size) {
        case size_Default:
            break;
        case size_Custom: set_size(geti_size_x(), geti_size_y());
            break;
        case size_640x480: set_size(640,480);
            break;
        case size_800x600: set_size(800,600);
            break;
        case size_1024x768: set_size(1024,768);
            break;
        case size_1280x720: set_size(1280,720);
            break;
        case size_1920x1080: set_size(1920,1080);
            break;
        case size_1920x1200: set_size(1920,1200);
            break;
        default:
            xc_exception("XModuleWindow - Unknown window size specifier");
        }
    }

    //Position
    //меняем положение, даже если изменили размер - если были настройки "в центре экрана"
    auto position = gete_position();
    if (size_changed || was_changed_position()
            || (position == position_Custom && (was_changed_pos_x() || was_changed_pos_y()))) {
        switch (position) {
        case position_Default:
            break;
        case position_Custom: set_position(geti_pos_x(), geti_pos_y());
            break;
        case position_Screen_Center: {
                QRect screenGeometry = get_screen()->geometry();
                int height = screenGeometry.height();
                int width = screenGeometry.width();
                set_position((width - window_->width())/2, (height - window_->height())/2);
            }
            break;
        default:
            xc_exception("XModuleWindow - Unknown window position specifier");
        }
    }


    //Visibility, fullscreen

    int visible = geti_visible();
    if (was_changed_visible() || (visible && need_apply_initial_state_)) {
        if (!visible) {
            window_->setVisible(false);
        }
        else {
            window_->setVisible(true);

            if (need_apply_initial_state_) {
                need_apply_initial_state_ = false;

                //minimized,maximized,fullscreen
                Qt::WindowStates state = 0;
                //NOTE: also can make active: Qt::WindowActive

                auto mode = gete_initial_state();
                switch (mode) {
                case initial_state_Minimized: state = Qt::WindowMinimized;
                    break;
                case initial_state_Normal_Window: state = 0;
                    break;
                case initial_state_Maximized: state = Qt::WindowMaximized;
                    break;
                case initial_state_Full_Screen: state = Qt::WindowFullScreen;
                    break;
                default:
                    xc_exception("XModuleWindow - Unknown window initial state specifier");
                }
                window_->setWindowState(state);
            }
        }
    }
}

//---------------------------------------------------------------------
//сигнал на изменение состояния окна
void XModuleWindow::on_windowStateChanged(Qt::WindowState /*windowState*/) {

}

//---------------------------------------------------------------------
void XModuleWindow::on_visibleChanged(bool /*arg*/) {
    notify_visible_change_ = true;
}

//---------------------------------------------------------------------
void XModuleWindow::start() {
    //Clear grab image
    getobject_image_cpu()->clear();

    //создание и установка начальных настроек окна
    setup_window();

    //установка начальных обновляемых параметров
    update_window();
}

//---------------------------------------------------------------------
void XModuleWindow::update() {

    update_window();   //обновляем данные

    //grab window, if required
    grab_window();
}


//---------------------------------------------------------------------
void XModuleWindow::stop() {
    //reset all widgets in modules in order nobody call for it
    reset_widgets();

    //reset window (also deletes all widgets)
    window_.reset();

}

//---------------------------------------------------------------------
//Вызов
/*void XModuleWindow::on_custom_call(QString function, XObject *input, XObject *output) {
    //"sound_buffer_add"
    //if (function == functions_names::sound_buffer_add()) {

        //получаем доступ к данным и звуковому буферу
        //DataAccess access(data_);
        //qDebug() << "PCM params: " << data_.image_background << data_.pcm_speed_hz;
        //XObjectRead sound(input);

        //float sample_rate = sound.var_int("sample_rate");
        //return;
    //}

}*/

//---------------------------------------------------------------------
/*
HorizontalLayout
  Tabs 5
    Tab Tab_1
      HorizontalLayout
        wnumber1
        wnumber2
    Tab Tab_2
    Tab Tab_3
  VerticalLayout 0
    wbutton1 0
    wbutton2 0
    Stretch 1
*/


//Создать структуру окна - при этом, запрашиваются виджеты из соответствующих модулей
void XModuleWindow::create_layouts() {
    QStringList lines = get_strings_content();

    //парсим структуру окна
    XcluParseTree tree;
    tree.parse(lines);

    //создаем элементы
    //по умолчанию, используется VerticalLayout, если у дерева несколько узлов самого верхнего уровня и внутри
    XModuleWindowStructureItem item = create_layouts_internal(tree, 0);
    if (item.widget) {
        window_->setCentralWidget(item.take_widget());
    }
    else {
        xc_exception("Error, structure must contains items, not only Stretch!");
    }

}

//---------------------------------------------------------------------
//Рекурсивное создание структуры окна
//При реализации я старался сделать здесь безопасным при exceptions и исключить утечки памяти
//для этого старался использовать QScopedPointer и забирать его указатели с помощью take в безопасные моменты
XModuleWindowStructureItem XModuleWindow::create_layouts_internal(const XcluParseTree &tree, int index) {

    //считываем тип
    //разбиваем на название и параметры
    auto &tree_item = tree.items[index];
    QString line = tree_item.line;
    const int line_index = index;

    //В случае ошибки парсинга - добавим строку
    try {
        //это корень, если line является пустой строкой
        if (line.isEmpty()) {
            int n = tree_item.children.size();
            if (n == 0) {
                //дерево пустое, ничего делать не надо
                return XModuleWindowStructureItem();
            }
            if (n == 1) {
                //один ребенок - вот его и возвратим
                return create_layouts_internal(tree, tree_item.children[0]);
            }
            else {
                //много детей, запаковываем в VerticalLayout
                QScopedPointer<QVBoxLayout> layout;
                layout.reset(new QVBoxLayout());

                for (int i=0; i<n; i++) {
                    XModuleWindowStructureItem item = create_layouts_internal(tree, tree_item.children[i]);
                    item.add_to_layout(layout.data());
                }
                return XModuleWindowStructureItem(layout.take());
            }
        }

        //не корень
        QStringList query = line.split(" ");

        QString name = query.at(0);

        //Layouts --------------------------------
        if (name == "HorizontalLayout" || name == "VerticalLayout") {
            //HorizontalLayout, либо HorizontalLayout 5

            //Делаем так, чтобы чтобы созданные объекты уничтожились, если возникнет exception
            QScopedPointer<QLayout> layout;

            if (name == "HorizontalLayout") {
                layout.reset(new QHBoxLayout());
            }
            else {
                layout.reset(new QVBoxLayout());
            }

            //margin and cpacing
            layout->setMargin(geti_global_margin());
            layout->setSpacing(geti_global_spacing());

            //stretch
            int stretch = xparse_int(query, 1, 0, line);

            //добавляем детей
            for (int i=0; i<tree_item.children.size(); i++) {
                XModuleWindowStructureItem item = create_layouts_internal(tree, tree_item.children[i]);
                item.add_to_layout(layout.data());
            }
            return XModuleWindowStructureItem(layout.take(), stretch);
        }

        //Tabs --------------------------------
        if (name == "Tabs") {
            //Tabs или Tabs 5
            QScopedPointer<QTabWidget> tabs;
            tabs.reset(new QTabWidget);

            //stretch
            int stretch = xparse_int(query, 1, 0, line);

            //добавляем детей
            for (int i=0; i<tree_item.children.size(); i++) {
                XModuleWindowStructureItem item = create_layouts_internal(tree, tree_item.children[i]);
                item.add_to_tabs(tabs.data());  //там при добавлении будет проверка, что добавляется Tab
            }
            return XModuleWindowStructureItem(tabs.take(), stretch);

        }

        //Tab --------------------------------
        if (name == "Tab") {
            //Tab Aaa_bbb
            //считывание имени страницы
            xc_assert(query.size() >= 2, "Expected 'Tab Page_Name'");
            QString tab_title = xc_remove_underscore(query.at(1));

            //добавляем детей
            int n = tree_item.children.size();
            //если n>2 - то выдастся ошибка, так как можем добавлять только один виджет или layout
            xc_assert(n <= 1, "Tab must contain not more than one widget or layout");
            if (n == 0) {
                //просто пустой виджет с именем страницы
                return XModuleWindowStructureItem(new QWidget, tab_title);
            }
            //n == 1
            XModuleWindowStructureItem item = create_layouts_internal(tree, tree_item.children[0]);
            xc_assert(item.widget, "Expected widget or layout");
            return XModuleWindowStructureItem(item.take_widget(), tab_title);
        }

        //Stretch --------------------------------
        if (name == "Stretch") {
            //Stretch или Stretch 5
            //stretch
            int stretch = xparse_int(query, 1, 0, line);
            return XModuleWindowStructureItem(stretch);
        }

        //Widget --------------------------------
        //внешний элемент
        //wint1 или wint1 5

        //для теста создаем просто строку
        //stretch
        int stretch = xparse_int(query, 1, 0, line);
        QString module_name = name;

        return XModuleWindowStructureItem(request_widget(module_name), stretch);

    }
    catch (XException& e) {
        xc_exception(QString("Error (recursive) at line %1 '%2':\n%3")
                       .arg(line_index)
                       .arg(line)
                       .arg(e.whatQt())
                            );
    }

    return XModuleWindowStructureItem();
}


//---------------------------------------------------------------------
//парсить число, если оно есть, иначе - выдать default_value
int XModuleWindow::xparse_int(QStringList list, int index, int default_value, QString line) {
    if (index >= list.size()) {
        return default_value;
    }
    bool ok;
    int v = list.at(index).toInt(&ok);
    xc_assert(ok, "Expected integer, but get '" + list.at(index) + "' at '" + line + "'");
    return v;
}

//---------------------------------------------------------------------
//запрос виджета из другого модуля
//важно, что модуль создает виджет и нам просто ссылку передает, и мы должны сами ее удалить
//- например, путем установки его в наши layouts и виджеты
QWidget *XModuleWindow::request_widget(QString module_name) {
    Module *module = xc_find_module(module_name);

    //call create_widget
    //Window calls GUI elements to insert them into itself.
    //string parent_id
    //out pointer widget_pointer

    //формируем запрос
    XObject input;
    input.sets("parent_id", this->module()->name());

    XObject output;

    module->call(XCallTypeCreateWidget, &input, &output);

    //считываем указатель на виджет
    QWidget *widget = (QWidget *)output.get_pointer("widget_pointer");
    xc_assert(widget, "Returned empty widget");

    //append to list to remove at stop
    used_modules_.append(module_name);
    return widget;
}


//---------------------------------------------------------------------
//remove all requested widgets stored at used_modules_
void XModuleWindow::reset_widgets() {
    for (auto &module_name: used_modules_) {
        reset_widget(module_name);
    }
    used_modules_.clear();
}

//---------------------------------------------------------------------
//remove requested widget from another module - called at stopping
void XModuleWindow::reset_widget(QString module_name) {
    Module *module = xc_find_module(module_name);

    //call create_widget
    //Window calls GUI elements to insert them into itself.
    //string parent_id
    //out pointer widget_pointer

    //формируем запрос
    XObject input;
    input.sets("parent_id", "");    //parent_id empty means command to reset widget

    XObject output;

    module->call(XCallTypeCreateWidget, &input, &output);
}

//---------------------------------------------------------------------
//Grab window
void XModuleWindow::grab_window() {
    if (geti_grab_cpu()) {
        auto size = window_->size();
        int w = size.width();
        int h = size.height();
        QImage img(w,h,QImage::Format_ARGB32);
        img.fill(Qt::transparent);
        {
            QPainter ptr(&img);
            window_->render(&ptr);
            //img.save("D:\\temp.png");
        }
        {
            auto write = getobject_image_cpu()->write();
            XObjectImage::create_from_QImage(write.data(), img, "RGBA", "uint8");
        }
       // XRaster_u8c4 bgra;
       // XRaster::convert_bgra(img, bgra);   //fast



    }
}


//---------------------------------------------------------------------
//Структура для создания layouts
//---------------------------------------------------------------------

XModuleWindowStructureItem::XModuleWindowStructureItem() {

}


XModuleWindowStructureItem::XModuleWindowStructureItem(QWidget* widget, int stretch) {
    xc_assert(widget, "Empty widget");
    this->widget = widget;
    this->stretch = stretch;
}

XModuleWindowStructureItem::XModuleWindowStructureItem(QLayout *layout, int stretch) {
    widget = new QWidget();
    widget->setLayout(layout);
    this->stretch = stretch;
}

XModuleWindowStructureItem::XModuleWindowStructureItem(QWidget* widget, QString tab_title) {
    xc_assert(widget, "Empty widget");
    this->widget = widget;
    is_tab = true;
    this->tab_title = tab_title;
}

XModuleWindowStructureItem::XModuleWindowStructureItem(int stretch) {
    is_stretch = true;
    this->stretch = stretch;
}

XModuleWindowStructureItem::~XModuleWindowStructureItem() {
    if (widget) delete widget;
}

//забрать указатель и тут его выставит в nullptr - чтобы деструктор не удалил widget
QWidget *XModuleWindowStructureItem::take_widget() {
    QWidget *w = widget;
    widget = nullptr;
    return w;
}


void XModuleWindowStructureItem::add_to_layout(QLayout *layout) {    //вставить в layout
    QHBoxLayout *hlayout = qobject_cast<QHBoxLayout *>(layout);
    QVBoxLayout *vlayout = qobject_cast<QVBoxLayout *>(layout);
    xc_assert(hlayout || vlayout, "Internal error, unrecognized layout");

    if (widget) {
        if (hlayout) hlayout->addWidget(take_widget(), stretch);
        if (vlayout) vlayout->addWidget(take_widget(), stretch);
    }
    if (is_stretch) {
        if (hlayout) hlayout->addStretch(stretch);
        if (vlayout) vlayout->addStretch(stretch);
    }
}

//---------------------------------------------------------------------
void XModuleWindowStructureItem::add_to_tabs(QTabWidget *tabs) {     //вставить в Tabs - должно быть имя страницы
    xc_assert(is_tab, "Tabs contains only Tab items");
    xc_assert(widget, "Can't add not widget to Tabs");
    tabs->addTab(take_widget(), tab_title);
}

//---------------------------------------------------------------------
