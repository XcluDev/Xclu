#pragma once

#include "xguicomp.h"
#include "xprotecteddata.h"

class XItemObject;
class XObject;
class QSpacerItem;

//визуальные компоненты для показа содержимого объекта
class XGuiObjectVisual {
public:
    XGuiObjectVisual();

    void set_text(QString text);

    void set_thumbnail_size(int w, int h);

    int2 thumbnail_size();
    void clear_thumbnail();
    void update_thumbnail();
    void show_thumbnail();
    void hide_thumbnail();

    int2 thumb_size_ = int2(100,100);   // считывается из настроек приложения
    //картинка
    QLabel *thumbnail_ = nullptr;   //удалять не надо
    //текстовое описание
    QLabel *description_ = nullptr;      //удалять не надо
    //разделитель
    //QSpacerItem *spacer_ = nullptr;

    // Картинка для thumb
    QImage image_;
    void resize_image(int w, int h);
    void clear_image();

};

class XGuiObject : public XGuiComp
{
    Q_OBJECT
public:
    XGuiObject(XGuiPageBuilder &page_builder, XItemObject *item);
    virtual ~XGuiObject();

    //показать объект визуально
    //если изображение - то картинкой, если нет - то текстовым описанием
    //мы это делаем только по команде извне
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

    // Храним изменения, чтобы понять, нужно ли перерисовать объект
    const XObject *last_object_ = nullptr;
    XWasChangedChecker was_changed_checker_;
    void reset_last_object();

};
