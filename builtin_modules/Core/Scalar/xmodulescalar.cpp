#include "qt_widgets.h"
#include "xmodulescalar.h"

#include "incl_cpp.h"
#include "registrarxmodule.h"
#include "xcore.h"
#include "module.h"
#include "xobject.h"

#include "xcluspinbox.h"


//registering module implementation
REGISTER_XMODULE(Scalar)

//---------------------------------------------------------------------
XModuleScalar::XModuleScalar(QString class_name)
    :XModule(class_name)
{

}

//---------------------------------------------------------------------
XModuleScalar::~XModuleScalar()
{

}

//---------------------------------------------------------------------
void XModuleScalar::impl_start() {
    //сбрасываем родителя - это будет установлено в impl_call, когда родитель запросит
    parent_was_set_ = false;
    parent_id_ = "";
    clear_string_parent_id();

    DataAccess access(data_);
    data_.clear();

}

//---------------------------------------------------------------------
void XModuleScalar::impl_update() {

    //установка всех значений, если они изменились
    update_all(false);
}


//---------------------------------------------------------------------
void XModuleScalar::impl_stop() {
    //нам не надо удалять виджет - так как он будет удален родителем
    //поэтому, просто обнуляем
    widget_ = nullptr;
    spin_ = nullptr;
}

//---------------------------------------------------------------------
//`create_widget` call implementation, creates QWidget and returns pointer on it
void *XModuleScalar::impl_create_widget(QString parent_id) {
    xclu_assert(!parent_was_set_, "Widget can have only one parent, and it's already set to '" + parent_id_ + "'")

    parent_id_ = parent_id;
    sets_parent_id(parent_id_);
    parent_was_set_ = true;

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

    //track changes
    connect(spin_, QOverload<int>::of(&QSpinBox::valueChanged),
            [=](int /*i*/){ spin_changed(); });

    //установка всех значений
    update_all(true);

    return widget_;
}

//---------------------------------------------------------------------
void XModuleScalar::spin_changed() {    //вызывается, если значение изменилось
    //это может вызваться не в основном потоке
    DataAccess access(data_);
    data_.gui_changed = 1;

}

//---------------------------------------------------------------------
void XModuleScalar::update_all(bool force) {
    if (!widget_) {
        return;
    }
    //parent_id - set by call

    //int visible
    if (force || was_changed_visible()) {
        widget_->setVisible(geti_visible());
    }

    //итоговое значение обновляем с force, или если изменился источник
    update_value(force || was_changed_source());


}


//---------------------------------------------------------------------
void XModuleScalar::update_value(bool force) {
    //enum source=GUI [Fixed_Value,GUI,Other_Module_Value,Expression]
    auto source = gete_source();
    switch (source) {
    case source_Fixed_Value:
        if (force || was_changed_fixed_value()) {
            set_value(geti_fixed_value());
        }
        break;
    case source_GUI: {
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
    case source_Other_Module_Value:
    {
        //взятие значение из другого модуля
        XLinkParsed link(gets_int_link());
        Module *module = XCORE.get_module(link.module);
        int value = module->geti(link.var);
        set_value(value);
    }
        break;
    case source_Expression: {
        //JS-скрипт
    }
        break;
    default:
        xclu_exception("Unknown 'source' in '" + module()->name());
    }

}

//---------------------------------------------------------------------
void XModuleScalar::set_value(int v) {
    seti_value(v);
    if (gete_source() != source_GUI) {
        spin_->setValue(v);
    }
}

//---------------------------------------------------------------------













