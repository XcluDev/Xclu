#ifndef XITEMRASTER_H
#define XITEMRASTER_H


//Raster

#include "incl_h.h"
#include "xcluprotecteddata.h"
#include "xitem.h"

/*
class ModuleInterface;

template<typename TRaster>
class XItemRaster_: public XItem
{
public:
    //parse_range - мы будем ставить false в checkbox
    XItemRaster_(ModuleInterface *interf, const XItemPreDescription &pre_description);


    //не поддерживаем скаляры, но будем записывать настройки в строку
    bool supports_string() { return true; }
    QString value_string() { return ""; }
    void set_value_string(const QString &value) {}

    bool supports_int() { return false; }

    //raster access
    bool is_empty();

    //returns nullptr if empty
    TRaster *get_raster();

    //raises exception if empty
    TRaster &get_raster_ref();

    //доступ к объекту
    virtual bool supports_object() { return false; }
    //virtual XStruct *get_object() { return object_.data(); }

    //графический интерфейс
    virtual XGui *create_gui(XGuiPageCreator &input);

    //C++ -------------------------
    virtual void export_interface(QStringList &file);
    //-----------------------------

protected:
    XRef<XProtectedData_<TRaster>> raster_;


protected:
    //работа с GUI - вызывается когда is_gui_attached
    virtual void gui_to_var_internal(); //получение значения из gui
    virtual void var_to_gui_internal(); //установка значения в gui

    //копирование данных - для duplicate; предполагается, что имя и тип - одинаковые
    //специальные типы, которые не поддерживают перенос через строку (array и image) - должны переписать copy_data_to_internal
    virtual void copy_data_to_internal(XItem *item);
};

*/


#endif // XITEMRASTER_H
