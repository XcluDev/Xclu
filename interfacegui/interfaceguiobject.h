#ifndef INTERFACEGUIOBJECT_H
#define INTERFACEGUIOBJECT_H

#include "interfacegui.h"

class InterfaceItemObject;
class XDict;
class QSpacerItem;

//визуальные компоненты для показа содержимого объекта
class InterfaceGuiObjectVisual {
public:
    void set_text(QString text);
    void set_image(const QImage &image);
    void clear_image();

    //картинка
    QLabel *preview_label_ = nullptr;   //удалять не надо
    //текстовое описание
    QLabel *info_label_ = nullptr;      //удалять не надо
    //разделитель
    QSpacerItem *spacer_ = nullptr;



};

class InterfaceGuiObject : public InterfaceGui
{
    Q_OBJECT
public:
    InterfaceGuiObject(InterfaceGuiPageCreator &input, InterfaceItemObject *item);
    ~InterfaceGuiObject();

    //значение для проверки видимости детей
    //QString value_string_for_visibility() { return QString::number(value()); };

    //int value();
    //void set_value(int v);

    //показать объект визуально
    //если изображение - то картинкой, если нет - то текстовым описанием
    //мы это делаем только по команде извне - так как не знаем,
    //вдруг с объектом проводятся операции
    //при необходимости - можно ввести mutex в объект
    void show_object(XDict *object);

    //доступ к меткам и другим компонентам для визуализации
    InterfaceGuiObjectVisual &visual();

protected:
    //установка режима read_only - для out и блокировки констант при запуске проекта
    void set_read_only(bool read_only);

private:
    //виджет для всей информации об объекте
    QWidget *object_widget_ = nullptr;  //удалять не надо
    InterfaceGuiObjectVisual visual_; //визуальные компоненты для описания объекта

};


#endif // INTERFACEGUIOBJECT_H
