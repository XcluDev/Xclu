#include "qt_widgets.h"
#include "xguipage.h"
#include "xitempage.h"
#include "xcluscrollarea.h"

//---------------------------------------------------------------------
XGuiPage::XGuiPage(XGuiPageCreator &input, XItemPage *item)
    :XGui(input, item)
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
    input.grid->setColumnStretch(xclu::gui_page_link_column,1);  //stretch for link column

    //страница, содержащая сетку
    QWidget *page = new QWidget;
    page->setLayout(input.grid);

    //Setting up name for using in QSS as `QWidget#GuiEditorPage` and set its background
    atribute_as_GuiEditorPage(page);  //set background as a whole page

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
XGuiPage::~XGuiPage() {

}

//---------------------------------------------------------------------
//закончить страницу
/*static*/ void XGuiPage::finalize_page(XGuiPageCreator &input) {
    if (input.grid) {
        //вставляем spacer в конце
        QSpacerItem *spacer = new QSpacerItem(1,10);
        input.grid->addItem(spacer,input.y,0,1,2);
        input.grid->setRowStretch(input.y,1);
        input.y++;
    }
}

//---------------------------------------------------------------------
int XGuiPage::get_vscroll() {
    return scrollarea_->get_vscroll();
}

//---------------------------------------------------------------------
void XGuiPage::set_vscroll(int v) {
   scrollarea_->set_vscroll(v);
}

//---------------------------------------------------------------------
//будет посылать сигнал изменения, только если это произошло уже после загрузки
void XGuiPage::on_vscroll_changed() {
    if (scrollarea_->is_shown()) {
        on_value_changed();
    }
}


//---------------------------------------------------------------------
