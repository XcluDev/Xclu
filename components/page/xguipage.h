#pragma once

#include "xgui.h"

class XItemPage;
class XcluScroollArea;

class XGuiPage : public XGui
{
    Q_OBJECT
public:
    XGuiPage(XGuiPageBuilder &page_builder, XItemPage *item);
    virtual ~XGuiPage();

    //end the previous page (used also in XGuiEditor)
    static void finalize_page(XGuiPageBuilder &page_builder);

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

