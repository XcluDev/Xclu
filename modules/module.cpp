#include <QJsonObject>
#include <QJsonArray>

#include "module.h"
#include "incl_cpp.h"
#include "modulesfactory.h"
#include "xobject.h"

//---------------------------------------------------------------------
Module::Module(ModuleSeed *info_external, XModule *rtmodule_new)
{
    info_external_ = info_external;

    interf_ = new ModuleInterface(*info_external);
    xmodule_ = rtmodule_new;
    xc_assert(xmodule_, "Empty run-time module in Module constructor for '" + info_external->description.class_name + "'");

    //установка самого модуля в rt-модуль и интерфейсный модуль, чтобы они могли обмениваться данными
    xmodule_->set_module(this);
    interf_->set_module(this);

    //также, нужно вызвать событие, что модуль был загружен
    //- после загрузки из json или после создания
    //поэтому здесь это закомментировано: execute(ModuleExecuteStageLoaded);
}

//---------------------------------------------------------------------
Module::~Module() {
    if (xmodule_) {
        delete xmodule_;
    }
    if (interf_) {
        delete interf_;
    }
}

//---------------------------------------------------------------------
ModuleDescription &Module::description() {
    return interf_->description();
}

//---------------------------------------------------------------------
QString Module::name() {
    return name_;
}

//---------------------------------------------------------------------
void Module::set_name(QString name) {
    name_ = name;
}

//---------------------------------------------------------------------
/*QString Module::name() {
    //name нужно не просто считать, а сделать gui_to_var,
    //так как это значение используется в Project::update_names(),
    //а оно вызывается до BeforeStarting,
    //так как name могут понадобиться в вычислении expression
    auto *var = interf_->var("name");

    //считываем из gui - если attached, он сам это проверит
    var->gui_to_var(false);

    return var->value_string();
}*/

//---------------------------------------------------------------------
/*void Module::set_id(QString name) {
    auto *varid = interf_->var("name");
    varid->set_value_string(name);
    varid->var_to_gui();
}*/

//---------------------------------------------------------------------
Module *Module::duplicate(QString new_nameid) {
    //сохраняем данные из GUI
    gui_action(GuiStageBeforeGuiDetached);

    //создаем копию модуля
    Module *module = FACTORY.create_unnamed_module(description().class_name);

    //копируем данные и ставим имя
    if (module) {
        interf()->copy_data_to(module->interf());
        module->set_name(new_nameid);
    }
    return module;
}

//---------------------------------------------------------------------
//Невизуальный интерфейс
ModuleInterface *Module::interf() {
    return interf_;
}

//---------------------------------------------------------------------
//Исполняемый модуль
XModule *Module::xmodule() {
    return xmodule_;
}

//---------------------------------------------------------------------
void Module::gui_attached(XGuiEditor *editor) {
    //qDebug() << "module " << name() << ": GUI attached";
    interf()->gui_attached(editor);
}

//---------------------------------------------------------------------
void Module::gui_detached() {
    //qDebug() << "module " << name() << " - GUI detached";
    interf()->gui_detached();
}

//---------------------------------------------------------------------
bool Module::is_gui_attached() {
    return interf()->is_gui_attached();
}

//---------------------------------------------------------------------
//Вычисление expressions и работа с GUI, см. определение GuiStage
//Предполагается, что извне приходят только действия с проектом: GuiStageProjectLoaded и GuiStageProjectBeforeSaving
//Побочное действие - также ставит и выключает is_running
void Module::gui_action(GuiStage stage, bool affect_is_running) {
    switch (stage) {
    case GuiStageProjectAfterLoading:   //ничего не делаем, это для уровня проекта
    break;

    case GuiStageAfterGuiAttached:
        interf()->vars_to_gui(XQualifierMask::get_all());
        interf()->state_to_gui();
        //если дело происходит при уже запущенном проекте - то заблокировать константы
        if (is_running()) {
            interf()->block_gui(XQualifierMask(XQualifierConst));
        }
        //enable buttons
        interf()->update_is_running(is_running());
    break;

    case GuiStageBeforeStart: {   //GUI -> const и in, блокировка констант
        interf()->gui_to_vars(XQualifierMask::get_const_in());
        if (affect_is_running) {
            interf()->block_gui(XQualifierMask(XQualifierConst));
            set_running(true);
        }
        //Пометить, что все переменные были изменены
        interf()->reset_was_changed();

        //update links and "was_changed"
        interf()->update();

        //enable buttons
        interf()->update_is_running(true);
    }
        break;

    case GuiStageBeforeUpdate:   //GUI -> in; expressions
        interf()->gui_to_vars(XQualifierMask(XQualifierIn), true);
        //update links and "was_changed"
        interf()->update();
        break;
    case GuiStageAfterUpdate:    //out -> GUI
        interf()->vars_to_gui(XQualifierMask::get_out_link());
        break;

    case GuiStageAfterStop:     //GUI -> const, in;  out -> GUI, разблокировка констант
        //disable buttons
        interf()->update_is_running(false);

        interf()->gui_to_vars(XQualifierMask::get_const_in());
        interf()->vars_to_gui(XQualifierMask::get_out_link());
        if (affect_is_running) {
            interf()->unblock_gui(XQualifierMask(XQualifierConst));
            set_running(false);
        }
        break;

    case GuiStageProjectBeforeSaving: //GUI -> const, in;
    case GuiStageBeforeGuiDetached:   //то же
        interf()->gui_to_vars(XQualifierMask::get_const_in());
        interf()->gui_to_state();
        break;

    default:
        xc_halt("Internal error: Module::gui_action - not implemented rule for GuiStage " + QString::number(stage));
    }

}

//---------------------------------------------------------------------
void Module::set_running(bool v) {
    running_ = v;
}

//---------------------------------------------------------------------
bool Module::is_running() {
    return running_;
}

//---------------------------------------------------------------------
//Compiling links and other things
bool Module::compile() {
    return interf()->compile();
}

//---------------------------------------------------------------------
//Выполнение
void Module::execute(ModuleExecuteStage stage) {
    switch (stage) {
    case ModuleExecuteStageLoaded:
        //Выполнить что-то, требуемое самому модулю
        xmodule_->execute(stage);
        break;
    case ModuleExecuteStageStart:
        //Установить все in и const переменные
        gui_action(GuiStageBeforeStart);
        //запуск start исполняемой части модуля
        xmodule_->execute(stage);    
        gui_action(GuiStageAfterUpdate);
        break;

    case ModuleExecuteStageAfterStart:
        xmodule_->execute(stage);
        break;

    case ModuleExecuteStageUpdate:
        //Установить все in переменные, update links and "was_change"
        gui_action(GuiStageBeforeUpdate);
        xmodule_->execute(stage);
        //Забрать все out переменные
        gui_action(GuiStageAfterUpdate);
        break;

    case ModuleExecuteStageBeforeStop:
        xmodule_->execute(stage);
        break;

    case ModuleExecuteStageStop:
        gui_action(GuiStageBeforeUpdate);
        xmodule_->execute(stage);
        gui_action(GuiStageAfterStop);
        //Забрать все out переменные
        //Запомнить все const, которые мог изменить пользователь во время выполнения
        //- чтобы они запомнились в параметрах модуля при записи на диск.
        break;

    //case ModuleExecuteStageCallback:
    //    xmodule_->execute(stage);
    //    break;

    default:
        xc_exception(QString("Unknown execute stage %1").arg(stage));
    }
}

//---------------------------------------------------------------------
bool Module::is_stop_out() {
    return xmodule_->is_stop_out();
}

//---------------------------------------------------------------------
void Module::button_pressed(QString button_id) {   //нажатие кнопки, даже при редактировании
    //если присоединен GUI и проект не запущен - то считать значения из GUI
    if (!is_running()) {
        gui_action(GuiStageBeforeStart, false /*not affect is_running()*/);
    }

    //"hit" button in interface - for modules which process pressing inside update
    interf()->_hit_button_(button_id);

    //исполнение нажатия кнопки
    xmodule()->button_pressed(button_id);

    //если присоединен GUI и проект не запущен - то обновить GUI
    if (!is_running()) {
        gui_action(GuiStageAfterUpdate, false /*not affect is_running()*/);
    }
}

//---------------------------------------------------------------------
void Module::bang() {        //Bang button
    xmodule()->general_bang();
}

//---------------------------------------------------------------------
//исключение "записывается" в err
void Module::call_function_no_exception(XCallType function, ErrorInfo &err, XObject *input, XObject *output) {
    //проверка, что модуль "понимает" запрошенную функцию
    if (!description().accept_calls.accepts(function)) {
        err = ErrorInfo(QString("Function '%1' can't be processed by module '%2' "
                                "because it's unregistered in its accepted calls")
                        .arg(xcalltype_to_string_for_user(function)).arg(name()));
        return;
    }
    xmodule()->call_function(function, err, input, output);
}

//---------------------------------------------------------------------
//в случае исключения - оно выдастся
void Module::call_function(XCallType function, XObject *input, XObject *output) {
    ErrorInfo err;
    call_function_no_exception(function, err, input, output);
    err.throw_error();
}

//---------------------------------------------------------------------
//Доступ к переменным и запуску из других модулей

//int, checkbox, button, enum (index), string, text
//index>=0: string, text separated by ' ' - no error if no such string!
//index2>=0: string, text separated by '\n' and ' ' - no error if no such string!
QString Module::gets(QString name, int index, int index2) {
    return interf()->gets(name, index, index2);
}

//---------------------------------------------------------------------
QString Module::gets(XLinkParsed *link) {
    return gets(link->var, link->index, link->index2);
}

//---------------------------------------------------------------------
//splits text using "\n"
QStringList Module::get_strings(QString name) {
    return interf()->get_strings(name);
}

//---------------------------------------------------------------------
void Module::sets(QString name, QString v) { //только out: int, checkbox, enum (index), string, text
    interf()->sets(name, v);
}

//---------------------------------------------------------------------
void Module::clear_string(QString name) {
    interf()->clear_string(name);
}

//---------------------------------------------------------------------
void Module::append_string(QString name, QString v, int extra_new_lines_count) {
    interf()->append_string(name, v, extra_new_lines_count);
}

//---------------------------------------------------------------------
void Module::append_string(QString name, QStringList v, int extra_new_lines_count) {
    interf()->append_string(name, v, extra_new_lines_count);
}

//---------------------------------------------------------------------
//int, checkbox, button, enum (index)
//index>=0: string, text separated by ' ' - no error if no such string!
//index2>=0: string, text separated by '\n' and ' ' - no error if no such string!
int Module::geti(QString name, int index, int index2) {
    return interf()->geti(name, index, index2);
}

//---------------------------------------------------------------------
int Module::geti(XLinkParsed *link) {
    return geti(link->var, link->index, link->index2);
}


//---------------------------------------------------------------------
void Module::seti(QString name, int v) { //только out: int, checkbox, enum (index)
    interf()->seti(name, v);
}

//---------------------------------------------------------------------
void Module::increase_int(QString name, int increase) {
    interf()->increase_int(name, increase);
}

//---------------------------------------------------------------------
//float
//index>=0: string, text separated by ' ' - no error if no such string!
//index2>=0: string, text separated by '\n' and ' ' - no error if no such string!
float Module::getf(QString name, int index, int index2) {
    return interf()->getf(name, index, index2);
}

//---------------------------------------------------------------------
float Module::getf(XLinkParsed *link) {
    return getf(link->var, link->index, link->index2);
}

//---------------------------------------------------------------------
void Module::setf(QString name, float v) {  //out: float
    interf()->setf(name, v);
}

//---------------------------------------------------------------------
QString Module::getraw(QString name) {  //enum (rawtext)
     return interf()->getraw(name);
}

//---------------------------------------------------------------------
void Module::set_raw(QString name, QString v) { //только out: enum (rawtext)
    interf()->set_raw(name, v);
}

//---------------------------------------------------------------------
QString Module::get_title_value(QString name) {  //enum (title)
     return interf()->get_title_value(name);
}

//---------------------------------------------------------------------
void Module::set_title_value(QString name, QString v) { //только out: enum (title)
    interf()->set_title_value(name, v);
}

//---------------------------------------------------------------------
XProtectedObject * Module::get_object(QString name) {
    return interf()->get_object(name);
}

//---------------------------------------------------------------------
void Module::set_object(QString name, XProtectedObject *object) {
    interf()->set_object(name, object);
}

//---------------------------------------------------------------------
//Запись в json
void Module::write_json(QJsonObject &json) {
    QJsonObject descrObject;
    auto &descr = description();
    //для загрузки модуля достаточно указать его класс и версию
    //это не нужно затем считывать:
    descrObject["class"] = descr.class_name;
    descrObject["version"] = descr.version;

    //Уникальные свойства, которые нужно считывать:
    descrObject["name"] = name();
    descrObject["name"] = name();

    json["description"] = descrObject;

    //Переменные
    QJsonObject interfObject;
    interf()->write_json(interfObject);
    json["interface"] = interfObject;
}

//---------------------------------------------------------------------
//Считывание из json
void Module::read_json(const QJsonObject &json) {
    QJsonObject descrObject = JsonUtils::json_object(json, "description");

    //Уникальные свойства, которые нужно считывать
    QString name = JsonUtils::json_string(descrObject, "name");
    //QString name = json_string(descrObject, "name");
    set_name(name);
    //set_id(name);

    //Переменные
    QJsonObject interfObject = JsonUtils::json_object(json, "interface");
    interf()->read_json(interfObject);
}

//---------------------------------------------------------------------
