#pragma once

#include "xgui.h"
#include "xprotecteddata.h"

class XItemObject;
class XObject;
class QSpacerItem;

//визуальные компоненты для показа содержимого объекта
class XGuiObjectVisual {
public:
    void set_text(QString text);

    void set_thumbnail_size(int w, int h);
    QPainter *thumbnail_painter();
    int2 thumbnail_size();
    void clear_thumbnail();

    //картинка
    QLabel *thumbnail_ = nullptr;   //удалять не надо
    //текстовое описание
    QLabel *description_ = nullptr;      //удалять не надо
    //разделитель
    //QSpacerItem *spacer_ = nullptr;

};

class XGuiObject : public XGui
{
    Q_OBJECT
public:
    XGuiObject(XGuiPageBuilder &page_builder, XItemObject *item);
    virtual ~XGuiObject();

    //значение для проверки видимости детей
    //QString value_string_for_visibility() { return QString::number(value()); };

    //int value();
    //void set_value(int v);

    //показать объект визуально
    //если изображение - то картинкой, если нет - то текстовым описанием
    //мы это делаем только по команде извне - так как не знаем,
    //вдруг с объектом проводятся операции
    //при необходимости - можно ввести mutex в объект
    void show_object(XProtectedObject* object);

    //доступ к меткам и другим компонентам для визуализации
    XGuiObjectVisual &visual();

protected:
    //установка режима read_only - для out и блокировки констант при запуске проекта
    void set_read_only_(bool read_only);

private:
    //виджет для всей информации об объекте
    QWidget *object_widget_ = nullptr;  //удалять не надо
    XGuiObjectVisual visual_; //визуальные компоненты для описания объекта

};
