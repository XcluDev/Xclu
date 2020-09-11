#ifndef INTERFACEGUIPAGE_H
#define INTERFACEGUIPAGE_H

#include "interfacegui.h"

class XItemPage;
class XcluScroollArea;

class InterfaceGuiPage : public InterfaceGui
{
    Q_OBJECT
public:
    InterfaceGuiPage(InterfaceGuiPageCreator &input, XItemPage *item);
    ~InterfaceGuiPage();

    //закончить страницу
    static void finalize_page(InterfaceGuiPageCreator &input);

    int get_vscroll();
    void set_vscroll(int v);
protected:
    //скролл-область, которая восстановит свое положение после создания
    XcluScroollArea *scrollarea_ = nullptr;

    //Указываем, что в подсказке страницы требуется только описание, без имени
    //(так как имя - это и есть заголовок)
    virtual Tip_Style get_tip_style() { return Tip_Description; }


protected slots:
    //будет посылать сигнал изменения, только если это произошло уже после загрузки
    void on_vscroll_changed();
};

#endif // INTERFACEGUIPAGE_H
