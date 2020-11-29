#ifndef XGUIRASTER_H
#define XGUIRASTER_H


#include "xgui.h"

/*
template<typename T>
class XItemRaster_;

class XObject;
class QSpacerItem;

//визуальные компоненты для показа содержимого объекта
class XGuiRasterVisual {
public:
    void set_text(QString text);
    void set_image(const QImage &image);
    void clear_image();

    //картинка
    QLabel *thumbnail_ = nullptr;   //удалять не надо
    //текстовое описание
    QLabel *description_ = nullptr;      //удалять не надо
    //разделитель
    QSpacerItem *spacer_ = nullptr;

    //TODO сделать рисование через виджет - и не обновлять, если невидимая картинка.
    //это сэкономит ресурсы.
};

class XGuiRaster: public XGui
{
    Q_OBJECT
public:
    template<typename T>
    XGuiRaster(XGuiPageBuilder &page_builder, XItemRaster_<T> *item);
    ~XGuiRaster();

    //значение для проверки видимости детей
    //QString value_string_for_visibility() { return QString::number(value()); };

    //int value();
    //void set_value(int v);

    //показать объект визуально
    //если изображение - то картинкой, если нет - то текстовым описанием
    //мы это делаем только по команде извне - так как не знаем,
    //вдруг с объектом проводятся операции
    //при необходимости - можно ввести mutex в объект
    void show_object(XObject *object);

    //доступ к меткам и другим компонентам для визуализации
    XGuiRasterVisual &visual();

protected:
    //установка режима read_only - для out и блокировки констант при запуске проекта
    void set_read_only_(bool read_only);

private:
    //виджет для всей информации об объекте
    QWidget *object_widget_ = nullptr;  //удалять не надо
    XGuiRasterVisual visual_; //визуальные компоненты для описания объекта

};*/

#endif // XGUIRASTER_H
