#include "qt_widgets.h"
#include "rtmodulescalar.h"

#include "incl_qtcpp.h"
#include "rtmoduleregistrar.h"
#include "projectruntime.h"
#include "module.h"
#include "xcluobject.h"

#include "xcluspinbox.h"


//заполнение имени класса и регистрация класса
REGISTRAR(Scalar)

//---------------------------------------------------------------------
/*static*/ RtModuleScalar *RtModuleScalar::new_module() {
    return new RtModuleScalar();
}

//---------------------------------------------------------------------
RtModuleScalar::RtModuleScalar()
    :RtModule(*static_class_name_ptr)
{

}

//---------------------------------------------------------------------
RtModuleScalar::~RtModuleScalar()
{

}

//---------------------------------------------------------------------
void RtModuleScalar::execute_start_internal() {
    //сбрасываем родителя - это будет установлено в call_internal, когда родитель запросит
    parent_was_set_ = false;
    parent_id_ = "";
    set_string("parent_id", "");

    DataAccess access(data_);
    data_.clear();

}

//---------------------------------------------------------------------
void RtModuleScalar::execute_update_internal() {

    //установка всех значений, если они изменились
    update_all(false);
}


//---------------------------------------------------------------------
void RtModuleScalar::execute_stop_internal() {
    //нам не надо удалять виджет - так как он будет удален родителем
    //поэтому, просто обнуляем
    widget_ = nullptr;
    spin_ = nullptr;
}

//---------------------------------------------------------------------
//Вызов
void RtModuleScalar::call_internal(QString function, XcluObject *input, XcluObject *output) {
    //"get_widget_pointer"
    if (function == call_function_name::get_widget_pointer()) {
        xclu_assert(!parent_was_set_, "Widget can have only one parent, and it's already set to '" + parent_id_ + "'")

        //call get_widget_pointer
        //Window calls GUI elements to insert them into itself.
        //string parent_id
        //out pointer widget_pointer

        //проверка, что оба объекта переданы
        xclu_assert(input, "Internal error, input object is nullptr");
        xclu_assert(output, "Internal error, output object is nullptr");

        //устанавливаем, кто использует
        parent_id_ = ObjectRead(input).get_string("parent_id");
        set_string("parent_id", parent_id_);
        parent_was_set_ = true;

        //проверяем, что еще не стартовали
        xclu_assert(status().was_started,
                    QString("Can't create widget, because module '%1' was not started yet."
                            " You need to place it before parent '%2'.")
                    .arg(module_->name())
                    .arg(parent_id_));

        //создаем виджет
        create_widget();

        //ставим его в объект
        ObjectReadWrite(output).set_pointer("widget_pointer", widget_);


        return;
    }

}

//---------------------------------------------------------------------
void RtModuleScalar::create_widget() {
    //insert_label(input);

    spin_ = new XcluSpinBox();
    spin_->setMinimumWidth(xclu::SPIN_WIDTH);
    spin_->setMaximumWidth(xclu::SPIN_WIDTH);

    widget_ = spin_;

    //spin_->setMinimum(item->min_value());
    //spin_->setMaximum(item->max_value());

    //вставка на страницу
    //если есть единицы измерения - создаем блок с Label
    //QString units = item->units();
    //if (!units.isEmpty()) {
        //qDebug() << "units" << units;
    //    insert_widget_with_spacer(xclu::hwidget(0,
    //                                            spin_,0,
    //                                            new QLabel(units), 0),
    //                              spin_, input);
    //}
    //else {
    //    insert_widget_with_spacer(spin_, spin_, input);
    //}

    //очистка данных - важно чтобы уничтожились перед вызовом update_all()
    {
        DataAccess access(data_);
        data_.clear();
    }

    //отслеживание изменений
    connect(spin_, QOverload<int>::of(&QSpinBox::valueChanged),
          [=](int /*i*/){ spin_changed(); });

    //установка всех значений
    update_all(true);
}

//---------------------------------------------------------------------
void RtModuleScalar::spin_changed() {    //вызывается, если значение изменилось
    //это может вызваться не в основном потоке
    DataAccess access(data_);
    data_.gui_changed = 1;

}

//---------------------------------------------------------------------
void RtModuleScalar::update_all(bool force) {
    if (!widget_) {
        return;
    }
    //parent_id - set by call

    //int visible
    if (force || was_changed("visible")) {
        widget_->setVisible(get_int("visible"));
    }

    //итоговое значение обновляем с force, или если изменился источник
    update_value(force || was_changed("source"));


}


//---------------------------------------------------------------------
RtModuleScalar::Source RtModuleScalar::get_source() {
    return Source(get_int("source"));
}

//---------------------------------------------------------------------
void RtModuleScalar::update_value(bool force) {
    //enum source=GUI [Fixed_Value,GUI,Other_Module_Value,Expression]
    Source source = get_source();
    switch (source) {
    case Source_Fixed_Value:
        if (force || was_changed("fixed_value")) {
            set_value(get_int("fixed_value"));
        }
        break;
    case Source_GUI: {
        bool changed = false;
        {
            DataAccess access(data_);
            if (force || data_.gui_changed) {
                data_.gui_changed = 0;
                changed = true;
            }
        }
        //важно чтобы DataAccess уже был уничтожен
        if (changed) {
            set_value(spin_->value());
        }
    }
        break;
    case Source_Other_Module_Value:
    {
        //взятие значение из другого модуля
        VarLink link(get_string("int_link"));
        Module *module = RUNTIME.get_module(link.module);
        int value = module->access_get_int(link.var);
        set_value(value);
    }
        break;
    case Source_Expression: {
        //JS-скрипт
    }
        break;
    default:
        xclu_exception("Unknown 'source' in '" + module()->name());
    }

}

//---------------------------------------------------------------------
void RtModuleScalar::set_value(int v) {
    set_int("value", v);
    if (get_source() != Source_GUI) {
        spin_->setValue(v);
    }
}

//---------------------------------------------------------------------













