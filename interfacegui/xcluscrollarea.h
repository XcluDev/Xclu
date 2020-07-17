#ifndef XCLUSCROLLAREA_H
#define XCLUSCROLLAREA_H


//Кастомный ScrollArea
//Реализуем установку вертикального слайдера в нужное положение после showEvent()
//https://stackoverflow.com/questions/14356121/how-to-call-function-after-window-is-shown
//Сейчас showEvent также не работает (в первый раз - видимо, слишком рано запускается),
//поэтому используем resizeEvent - и ждем, когда в нем появляется вертикальный скроллбар

#include <QWidget>
#include <QScrollArea>
#include "incl_qt.h"

class QShowEvent;
class QResizeEvent;

class XcluScroollArea : public QScrollArea {
    Q_OBJECT
public:
    XcluScroollArea(QWidget *parent = 0);

    void set_vscroll(int scroll);
    int get_vscroll();

    //был ли слайдер уже активирован после загрузки проекта (то есть, окно полностью сформировалось)
    bool is_shown();
protected:
    //событие показа - после него надо установить скроллер в нужное положение
    //void showEvent( QShowEvent* event );

    //событие изменение размера - когда в нем появляется скроллбар, надо установить скроллер в нужное положение
    void resizeEvent(QResizeEvent *);

    bool shown_ = false;
    int vscroll_ = 0;
    void apply_vscroll();

};


#endif // XCLUSCROLLAREA_H
