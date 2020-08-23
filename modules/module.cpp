#include <QJsonObject>
#include <QJsonArray>

#include "module.h"
#include "incl_qtcpp.h"
#include "modulesfactory.h"
#include "xcluobject.h"

//---------------------------------------------------------------------
Module::Module(ModuleInfo *info_external, RtModule *rtmodule_new)
{
    info_external_ = info_external;

    interf_ = new ModuleInterface(*info_external);
    rtmodule_ = rtmodule_new;
    xclu_assert(rtmodule_, "Empty run-time module in Module constructor for '" + info_external->description.class_name + "'");

    //установка интерфейса и самого модуля в rt-модуль
    rtmodule_->set_interface(interf_);
    rtmodule_->set_module(this);

}

//---------------------------------------------------------------------
Module::~Module() {
    if (rtmodule_) {
        delete rtmodule_;
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
RtModule *Module::rtmodule() {
    return rtmodule_;
}

//---------------------------------------------------------------------
void Module::gui_attached(EditorModule *editor) {
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
void Module::gui_action(GuiStage stage) {
    switch (stage) {
    case GuiStageProjectAfterLoading:   //ничего не делаем, это для уровня проекта
    break;

    case GuiStageAfterGuiAttached:
        interf()->vars_to_gui(VarQualifierConst);
        interf()->vars_to_gui(VarQualifierIn);
        interf()->vars_to_gui(VarQualifierOut);
        interf()->state_to_gui();
        //если дело происходит при уже запущенном проекте - то заблокировать константы
        if (is_running()) {
            interf()->block_gui_constants();
        }
    break;

    case GuiStageBeforeStart:   //GUI -> const и in, блокировка констант
        interf()->gui_to_vars(VarQualifierConst);
        interf()->gui_to_vars(VarQualifierIn);
        interf()->block_gui_constants();
        set_running(true);
        break;

    case GuiStageBeforeUpdate:   //GUI -> in; expressions
        interf()->gui_to_vars(VarQualifierIn, true);
        break;
    case GuiStageAfterUpdate:    //out -> GUI
        interf()->vars_to_gui(VarQualifierOut);
        break;

    case GuiStageAfterStop:     //GUI -> const, in;  out -> GUI, разблокировка констант
        interf()->gui_to_vars(VarQualifierConst);
        interf()->gui_to_vars(VarQualifierIn);
        interf()->vars_to_gui(VarQualifierOut);
        interf()->unblock_gui_constants();
        set_running(false);
        break;

    case GuiStageProjectBeforeSaving: //GUI -> const, in;
    case GuiStageBeforeGuiDetached:   //то же
        interf()->gui_to_vars(VarQualifierConst);
        interf()->gui_to_vars(VarQualifierIn);
        interf()->gui_to_state();
        break;

    default:
        xclu_halt("Internal error: Module::gui_action - not implemented rule for GuiStage " + QString::number(stage));
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
//Выполнение
void Module::execute(ModuleExecuteStage stage) {
    switch (stage) {
    case ModuleExecuteStageStart:
        //Установить все in и const переменные
        gui_action(GuiStageBeforeStart);
        //Пометить, что все переменные были изменены
        interf()->set_changed_at_start();
        //запуск start исполняемой части модуля
        rtmodule_->execute(stage);
        gui_action(GuiStageAfterUpdate);
        break;

    case ModuleExecuteStageAfterStart:
        rtmodule_->execute(stage);
        break;

    case ModuleExecuteStageUpdate:
        //Установить все in переменные
        gui_action(GuiStageBeforeUpdate);
        rtmodule_->execute(stage);
        //Забрать все out переменные
        gui_action(GuiStageAfterUpdate);
        break;

    case ModuleExecuteStageBeforeStop:
        rtmodule_->execute(stage);
        break;

    case ModuleExecuteStageStop:
        gui_action(GuiStageBeforeUpdate);
        rtmodule_->execute(stage);
        gui_action(GuiStageAfterStop);
        //Забрать все out переменные
        //Запомнить все const, которые мог изменить пользователь во время выполнения
        //- чтобы они запомнились в параметрах модуля при записи на диск.
        break;

    //case ModuleExecuteStageCallback:
    //    rtmodule_->execute(stage);
    //    break;

    default:
        xclu_exception(QString("Unknown execute stage %1").arg(stage));
    }
}

//---------------------------------------------------------------------
bool Module::is_stop_out() {
    return rtmodule_->is_stop_out();
}

//---------------------------------------------------------------------
//исключение "записывается" в err
void Module::access_call_no_exception(QString function, ErrorInfo &err, XcluObject *input, XcluObject *output) {
    //проверка, что модуль "понимает" запрошенную функцию
    if (!description().accept_calls.accepts(function)) {
        err = ErrorInfo(QString("Function '%1' can't be processed by module '%2' "
                                "because it's unregistered in its accepted calls")
                        .arg(function).arg(name()));
        return;
    }
    rtmodule()->call(function, err, input, output);
}

//---------------------------------------------------------------------
//в случае исключения - оно выдастся
void Module::access_call(QString function, XcluObject *input, XcluObject *output) {
    ErrorInfo err;
    access_call_no_exception(function, err, input, output);
    err.throw_error();
}

//---------------------------------------------------------------------
//Доступ к переменным и запуску из других модулей
QString Module::access_get_string(QString name) {   //int, checkbox, button, enum (rawtext), string, text
    return rtmodule()->get_string(name);
}

//---------------------------------------------------------------------
void Module::access_set_string(QString name, QString v) { //только out: int, checkbox, enum (rawtext), string, text
    rtmodule()->set_string(name, v);
}

//---------------------------------------------------------------------
int Module::access_get_int(QString name) {    //int, checkbox, button, enum (index)
    return rtmodule()->get_int(name);
}

//---------------------------------------------------------------------
void Module::access_set_int(QString name, int v) { //только out: int, checkbox, enum (index)
    rtmodule()->set_int(name, v);
}

//---------------------------------------------------------------------
float Module::access_get_float(QString name) {  //float
    return rtmodule()->get_float(name);
}

//---------------------------------------------------------------------
void Module::access_set_float(QString name, float v) {  //out: float
    rtmodule()->set_float(name, v);
}

//---------------------------------------------------------------------
QString Module::access_get_title_value(QString name) {  //enum (title)
     return rtmodule()->get_title_value(name);
}

//---------------------------------------------------------------------
void Module::access_set_title_value(QString name, QString v) { //только out: enum (title)
    rtmodule()->set_title_value(name, v);
}

//---------------------------------------------------------------------
//доступ к объектам идет только по указателям
//требуется начать и потом закончить доступ (mutex)
XcluObject *Module::access_get_object(QString name) {
    return rtmodule()->get_object(name);
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
    QJsonObject descrObject = json_object(json, "description");

    //Уникальные свойства, которые нужно считывать
    QString name = json_string(descrObject, "name");
    //QString name = json_string(descrObject, "name");
    set_name(name);
    //set_id(name);

    //Переменные
    QJsonObject interfObject = json_object(json, "interface");
    interf()->read_json(interfObject);
}

//---------------------------------------------------------------------
