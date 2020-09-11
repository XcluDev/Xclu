#include "qt_widgets.h"
#include "interfaceguipage.h"
#include "xitempage.h"
#include "xcluscrollarea.h"

//---------------------------------------------------------------------
InterfaceGuiPage::InterfaceGuiPage(InterfaceGuiPageCreator &input, XItemPage *item)
    :InterfaceGui(input, item)
{
    //завершаем предыдущую страницу
    finalize_page(input);

    //новая страница:
    //сетка
    input.grid = new QGridLayout();
    if (xclu::gui_page_grid_margin != -1) {
        input.grid->setMargin(xclu::gui_page_grid_margin);
    }
    if (xclu::gui_page_grid_spacing != -1) {
        input.grid->setSpacing(xclu::gui_page_grid_spacing);    //расстояние между элементами
    }

    //страница, содержащая сетку
    QWidget *page = new QWidget;
    page->setLayout(input.grid);

    //scrollarea
    scrollarea_ = new XcluScroollArea;
    scrollarea_->setWidget(page);
    scrollarea_->setWidgetResizable(true);
    //scrollarea_->setBackgroundRole(QPalette::Dark);

    //вставляем в tabs
    QWidget *scrollWidget = xclu::vwidget(0, scrollarea_, 0);

    auto *tabs = input.tabs;
    tabs->addTab(scrollWidget, item->title());
    //устанавливаем подсказку
    tabs->setTabToolTip(tabs->count()-1, get_tip());

    //начинаем вставлять с верха
    input.y = 0;

    //отслеживание изменений области промотки
    connect(scrollarea_->verticalScrollBar(), SIGNAL (valueChanged(int)), this, SLOT (on_vscroll_changed()));

}

//---------------------------------------------------------------------
InterfaceGuiPage::~InterfaceGuiPage() {

}

//---------------------------------------------------------------------
//закончить страницу
/*static*/ void InterfaceGuiPage::finalize_page(InterfaceGuiPageCreator &input) {
    if (input.grid) {
        //вставляем spacer в конце
        QSpacerItem *spacer = new QSpacerItem(1,10);
        input.grid->addItem(spacer,input.y,0,1,2);
        input.grid->setRowStretch(input.y,1);
        input.y++;
    }
}

//---------------------------------------------------------------------
int InterfaceGuiPage::get_vscroll() {
    return scrollarea_->get_vscroll();
}

//---------------------------------------------------------------------
void InterfaceGuiPage::set_vscroll(int v) {
   scrollarea_->set_vscroll(v);
}

//---------------------------------------------------------------------
//будет посылать сигнал изменения, только если это произошло уже после загрузки
void InterfaceGuiPage::on_vscroll_changed() {
    if (scrollarea_->is_shown()) {
        on_value_changed();
    }
}


//---------------------------------------------------------------------
