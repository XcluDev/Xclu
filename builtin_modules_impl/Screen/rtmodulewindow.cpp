#include <QApplication>
#include "qt_widgets.h"
#include <QScreen>
#include "rtmodulewindow.h"

#include "incl_cpp.h"
#include "rtmoduleregistrar.h"
#include "projectruntime.h"
#include "module.h"
#include "xcluobject.h"


//заполнение имени класса и регистрация класса
REGISTRAR(Window)


//---------------------------------------------------------------------
/*static*/ RtModuleWindow *RtModuleWindow::new_module() {
    return new RtModuleWindow();
}

//---------------------------------------------------------------------
RtModuleWindow::RtModuleWindow()
    :RtModule(*static_class_name_ptr)
{

}

//---------------------------------------------------------------------
RtModuleWindow::~RtModuleWindow()
{

}

//---------------------------------------------------------------------
void RtModuleWindow::set_size(int w, int h) {
    window_->resize(w, h);
}

//---------------------------------------------------------------------
void RtModuleWindow::set_position(int x, int y) {
    window_->setGeometry(x, y, window_->width(), window_->height());
}

//---------------------------------------------------------------------
//получить экран в зависимости от настроек
QScreen *RtModuleWindow::get_screen() {
    return QGuiApplication::primaryScreen();
/*    WindowScreen screen = WindowScreen(get_int("screen"));
    switch (screen) {
    case WindowScreen_Default:
        return QGuiApplication::primaryScreen();
        break;
    case WindowScreen_Custom: {
            int index = get_int("screen_index");
            auto screens = QGuiApplication::screens();
            xclu_assert(index>=0 && index<screens.count(),
                        QString("Bad screen index %1").arg(index));
            return screens.at(index);
        }
        break;
    default:
        xclu_exception("RtModuleWindow - Unknown screen specifier");
    }

    //если что-то пошло не так, возвращаем экран по умолчанию
    return QGuiApplication::primaryScreen();*/
}

//---------------------------------------------------------------------
//создание и установка начальных настроек окна
void RtModuleWindow::setup_window() {
    //Создание окна на нужном экране
    //QScreen *screen = get_screen();
    window_.reset(new QMainWindow());


    //??????????
    //window_.setAttribute(Qt::WA_DeleteOnClose); //???
    //window_.setUnifiedTitleAndToolBarOnMac(true);

    //??????????
    //connect(window_.data(), &QMainWindow::visibleChanged, this, &RtModuleWindow::on_visibleChanged);
    //connect(window_.data(), &QMainWindow::windowStateChanged, this, &RtModuleWindow::on_windowStateChanged);

    notify_visible_change_ = false;

    //Borderless
    //Qt::FramelessWindowHint

    //шрифт
    if (get_int("font_size") == 1) {    //Custom
        int font_size = get_int("font_size_pix");
        auto font = window_->font();
        font.setPixelSize(font_size);
        window_->setFont(font);
    }

    //Структура окна
    create_layouts();

}

//---------------------------------------------------------------------
//прочитать данные из интерфейса и использовать для управления окном
//он использует was_changed - поэтому, при старте всегда эти значения будут использованы (при старте все переменные was_changed)
void RtModuleWindow::update_window() {
    //проверка, что пользователь закрыл окно
    if (notify_visible_change_) {
        notify_visible_change_ = false;
        if (get_int("visible") && !window_->isVisible()) {
            //пользователь нажал кнопку закрытия окна или другой сигнал для закрытия
            OnCloseAction on_close = OnCloseAction(get_int("on_close"));
            switch (on_close) {
            case  OnCloseAction_Ignore:
                window_->setVisible(true);  //делаем видимым
                break;
            case OnCloseAction_Stop:
                set_stop_out(); //команда остановки
                break;
            default:
                xclu_exception("RtModuleWindow - Unknown on_close specifier");
            }

        }
    }

    //title
    if (was_changed("title")) {
        window_->setWindowTitle(get_string("title"));
    }

    //TODO!!!!!!!!!!!!!!!!!!!!!!!!!! если меняем размер и положение - то сразу установить setGeometry
    //Size
    bool size_changed = false;
    WindowSize size = WindowSize(get_int("size"));
    if (was_changed("size")
            || (size == WindowSize_Custom && (was_changed("size_x") || was_changed("size_y")))) {
        size_changed = true;
        switch (size) {
        case WindowSize_Default:
            break;
        case WindowSize_Custom: set_size(get_int("size_x"), get_int("size_y"));
            break;
        case WindowSize_640x480: set_size(640,480);
            break;
        case WindowSize_800x600: set_size(800,600);
            break;
        case WindowSize_1024x768: set_size(1024,768);
            break;
        case WindowSize_1280x720: set_size(1280,720);
            break;
        case WindowSize_1920x1080: set_size(1920,1080);
            break;
        case WindowSize_1920x1200: set_size(1920,1200);
            break;
        default:
            xclu_exception("RtModuleWindow - Unknown window size specifier");
        }
    }

    //Position
    //меняем положение, даже если изменили размер - если были настройки "в центре экрана"
    WindowPos position = WindowPos(get_int("position"));
    if (size_changed || was_changed("position")
            || (position == WindowPos_Custom ||(was_changed("pos_x") && was_changed("pos_y")))) {
        switch (position) {
        case WindowPos_Default:
            break;
        case WindowPos_Custom: set_position(get_int("pos_x"), get_int("pos_y"));
            break;
        case WindowPos_ScreenCenter: {
                QRect screenGeometry = get_screen()->geometry();
                int height = screenGeometry.height();
                int width = screenGeometry.width();
                set_position((width - window_->width())/2, (height - window_->height())/2);
            }
            break;
        default:
            xclu_exception("RtModuleWindow - Unknown window position specifier");
        }
    }


    //Visibility, fullscreen
    if (was_changed("visible") || was_changed("mode")) {
        int visible = get_int("visible");
        if (!visible) {
            window_->setVisible(false);
        }
        else {
            window_->setVisible(true);

            //minimized,maximized,fullscreen
            QWindow::Visibility visibility = QWindow::Windowed;

            WindowMode mode = WindowMode(get_int("mode"));
            switch (mode) {
            case WindowMode_Minimized: visibility = QWindow::Minimized;
                break;
            case WindowMode_Normal_Window: visibility = QWindow::Windowed;
                break;
            case WindowMode_Maximized: visibility = QWindow::Maximized;
                break;
            case WindowMode_Full_Screen: visibility = QWindow::FullScreen;
                break;
            default:
                xclu_exception("RtModuleWindow - Unknown window mode specifier");
            }
            window_->setVisible(visibility);
        }
    }


}


//---------------------------------------------------------------------
//сигнал на изменение состояния окна
void RtModuleWindow::on_windowStateChanged(Qt::WindowState /*windowState*/) {

}

//---------------------------------------------------------------------
void RtModuleWindow::on_visibleChanged(bool /*arg*/) {
    notify_visible_change_ = true;
}

//---------------------------------------------------------------------
void RtModuleWindow::execute_start_internal() {
    //создание и установка начальных настроек окна
    setup_window();

    //установка начальных обновляемых параметров
    update_window();
}

//---------------------------------------------------------------------
void RtModuleWindow::execute_update_internal() {

    update_window();   //обновляем данные
}


//---------------------------------------------------------------------
void RtModuleWindow::execute_stop_internal() {
    window_.reset();
}

//---------------------------------------------------------------------
//Вызов
void RtModuleWindow::call_internal(QString /*function*/, XcluObject * /*input*/, XcluObject * /*output*/) {
    //"sound_buffer_add"
    //if (function == call_function_name::sound_buffer_add()) {

        //получаем доступ к данным и звуковому буферу
        //DataAccess access(data_);
        //qDebug() << "PCM params: " << data_.image_background << data_.pcm_speed_hz;
        //ObjectRead sound(input);

        //float sample_rate = sound.var_int("sample_rate");
        //return;
    //}

}

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
void RtModuleWindow::create_layouts() {
    QStringList lines = get_string("content").split("\n");

    //парсим структуру окна
    XcluParseTree tree;
    tree.parse(lines);

    //создаем элементы
    //по умолчанию, используется VerticalLayout, если у дерева несколько узлов самого верхнего уровня и внутри
    RtModuleWindowStructureItem item = create_layouts_internal(tree, 0);
    if (item.widget) {
        window_->setCentralWidget(item.take_widget());
    }
    else {
        xclu_exception("Error, structure must contains items, not only Stretch!");
    }

}

//---------------------------------------------------------------------
//Рекурсивное создание структуры окна
//При реализации я старался сделать здесь безопасным при exceptions и исключить утечки памяти
//для этого старался использовать QScopedPointer и забирать его указатели с помощью take в безопасные моменты
RtModuleWindowStructureItem RtModuleWindow::create_layouts_internal(const XcluParseTree &tree, int index) {

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
                return RtModuleWindowStructureItem();
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
                    RtModuleWindowStructureItem item = create_layouts_internal(tree, tree_item.children[i]);
                    item.add_to_layout(layout.data());
                }
                return RtModuleWindowStructureItem(layout.take());
            }
        }

        //не корень
        QStringList query = line.split(" ");

        QString name = query.at(0);

        //Layouts --------------------------------
        if (name == "HorizontalLayout" || name == "VerticalLayout") {
            //HorizontalLayout, либо HorizontalLayout 5

            //Делаем так, чтобы чтобы созданные объекты уничтожились при исключении
            QScopedPointer<QLayout> layout;

            if (name == "HorizontalLayout") {
                layout.reset(new QHBoxLayout());
            }
            else {
                layout.reset(new QVBoxLayout());
                //layout.reset(new QHBoxLayout());
            }

            //stretch
            int stretch = parse_int(query, 1, 0, line);

            //добавляем детей
            for (int i=0; i<tree_item.children.size(); i++) {
                RtModuleWindowStructureItem item = create_layouts_internal(tree, tree_item.children[i]);
                item.add_to_layout(layout.data());
            }
            return RtModuleWindowStructureItem(layout.take(), stretch);
        }

        //Tabs --------------------------------
        if (name == "Tabs") {
            //Tabs или Tabs 5
            QScopedPointer<QTabWidget> tabs;
            tabs.reset(new QTabWidget);

            //stretch
            int stretch = parse_int(query, 1, 0, line);

            //добавляем детей
            for (int i=0; i<tree_item.children.size(); i++) {
                RtModuleWindowStructureItem item = create_layouts_internal(tree, tree_item.children[i]);
                item.add_to_tabs(tabs.data());  //там при добавлении будет проверка, что добавляется Tab
            }
            return RtModuleWindowStructureItem(tabs.take(), stretch);

        }

        //Tab --------------------------------
        if (name == "Tab") {
            //Tab Aaa_bbb
            //считывание имени страницы
            xclu_assert(query.size() >= 2, "Expected 'Tab Page_Name'");
            QString tab_title = xclu_remove_underscore(query.at(1));

            //добавляем детей
            int n = tree_item.children.size();
            //если n>2 - то выдастся ошибка, так как можем добавлять только один виджет или layout
            xclu_assert(n <= 1, "Tab must contain not more than one widget or layout");
            if (n == 0) {
                //просто пустой виджет с именем страницы
                return RtModuleWindowStructureItem(new QWidget, tab_title);
            }
            //n == 1
            RtModuleWindowStructureItem item = create_layouts_internal(tree, tree_item.children[0]);
            xclu_assert(item.widget, "Expected widget or layout");
            return RtModuleWindowStructureItem(item.take_widget(), tab_title);
        }

        //Stretch --------------------------------
        if (name == "Stretch") {
            //Stretch или Stretch 5
            //stretch
            int stretch = parse_int(query, 1, 0, line);
            return RtModuleWindowStructureItem(stretch);
        }

        //Widget --------------------------------
        //внешний элемент
        //wint1 или wint1 5

        //для теста создаем просто строку
        //stretch
        int stretch = parse_int(query, 1, 0, line);
        QString module_id = name;
        return RtModuleWindowStructureItem(request_widget(module_id), stretch);

    }
    catch (XCluException& e) {
        xclu_exception(QString("Error (recursive) at line %1 '%2':\n%3")
                       .arg(line_index)
                       .arg(line)
                       .arg(e.whatQt())
                            );
    }

    return RtModuleWindowStructureItem();
}


//---------------------------------------------------------------------
//парсить число, если оно есть, иначе - выдать default_value
int RtModuleWindow::parse_int(QStringList list, int index, int default_value, QString line) {
    if (index >= list.size()) {
        return default_value;
    }
    bool ok;
    int v = list.at(index).toInt(&ok);
    xclu_assert(ok, "Expected integer, but get '" + list.at(index) + "' at '" + line + "'");
    return v;
}

//---------------------------------------------------------------------
//запрос виджета из другого модуля
//важно, что модуль создает виджет и нам просто ссылку передает, и мы должны сами ее удалить
//- например, путем установки его в наши layouts и виджеты
QWidget *RtModuleWindow::request_widget(QString module_id) {
    Module *module = RUNTIME.get_module(module_id);

    //call get_widget_pointer
    //Window calls GUI elements to insert them into itself.
    //string parent_id
    //out pointer widget_pointer

    //формируем запрос
    XcluObject input;
    ObjectReadWrite(input).set_string("parent_id", module_->name());

    XcluObject output;

    module->access_call(call_function_name::get_widget_pointer(), &input, &output);

    //считываем указатель на виджет
    QWidget *widget = (QWidget *)ObjectReadWrite(output).get_pointer("widget_pointer");
    xclu_assert(widget, "Returned empty widget");

    return widget;
}

//---------------------------------------------------------------------
//Структура для создания layouts

RtModuleWindowStructureItem::RtModuleWindowStructureItem() {

}


RtModuleWindowStructureItem::RtModuleWindowStructureItem(QWidget* widget, int stretch) {
    xclu_assert(widget, "Empty widget");
    this->widget = widget;
    this->stretch = stretch;
}

RtModuleWindowStructureItem::RtModuleWindowStructureItem(QLayout *layout, int stretch) {
    widget = new QWidget();
    widget->setLayout(layout);
    this->stretch = stretch;
}

RtModuleWindowStructureItem::RtModuleWindowStructureItem(QWidget* widget, QString tab_title) {
    xclu_assert(widget, "Empty widget");
    this->widget = widget;
    is_tab = true;
    this->tab_title = tab_title;
}

RtModuleWindowStructureItem::RtModuleWindowStructureItem(int stretch) {
    is_stretch = true;
    this->stretch = stretch;
}

RtModuleWindowStructureItem::~RtModuleWindowStructureItem() {
    if (widget) delete widget;
}

//забрать указатель и тут его выставит в nullptr - чтобы деструктор не удалил widget
QWidget *RtModuleWindowStructureItem::take_widget() {
    QWidget *w = widget;
    widget = nullptr;
    return w;
}


void RtModuleWindowStructureItem::add_to_layout(QLayout *layout) {    //вставить в layout
    QHBoxLayout *hlayout = qobject_cast<QHBoxLayout *>(layout);
    QVBoxLayout *vlayout = qobject_cast<QVBoxLayout *>(layout);
    xclu_assert(hlayout || vlayout, "Internal error, unrecognized layout");

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
void RtModuleWindowStructureItem::add_to_tabs(QTabWidget *tabs) {     //вставить в Tabs - должно быть имя страницы
    xclu_assert(is_tab, "Tabs contains only Tab items");
    xclu_assert(widget, "Can't add not widget to Tabs");
    tabs->addTab(take_widget(), tab_title);
}

//---------------------------------------------------------------------
