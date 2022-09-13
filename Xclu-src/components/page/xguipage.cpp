#include "qt_widgets.h"
#include "xguipage.h"
#include "xitempage.h"
#include "xcluscrollarea.h"

//---------------------------------------------------------------------
/*
Widget structures for different controls:

float, int:     0 label, 1 control,  2 measure unit, 3 slider,     4 link label
checkbox:       0 label, 1 control                                 4 link label
checkbox_group: 0--------1 control,  2---------------3 horiz.line  4 link label
separator:      0 "control"
button:                  1 control                                 4 link label
string, text:   0 label                                            4 link label
                0 -------------------------------------------------4 control
object:         0 label                                            4 link label
                0--------------------2 thumbnail     3-------------4 description
*/

//---------------------------------------------------------------------
XGuiPage::XGuiPage(XGuiPageBuilder &page_builder, XItemPage *item)
    :XGuiComp(page_builder, item)
{
    //end the previous page
    finalize_page(page_builder);

    //new page:
    //grid
    page_builder.grid = new QGridLayout();
    if (xclu::gui_page_grid_margin != -1) {
        page_builder.grid->setMargin(xclu::gui_page_grid_margin);
    }
    if (xclu::gui_page_grid_spacing != -1) {
        page_builder.grid->setSpacing(xclu::gui_page_grid_spacing);    //расстояние между элементами
    }
    page_builder.grid->setColumnStretch(xclu::gui_page_link_column,1);  //stretch for link column

    //page, containing the grid
    QWidget *page = new QWidget;
    page->setLayout(page_builder.grid);

    //Setting up name for using in QSS as `QWidget#GuiEditorPage` and set its background
    attribute_as_GuiEditorPage(page);  //set background as a whole page

    //scrollarea
    scrollarea_ = new XcluScroollArea;
    scrollarea_->setWidget(page);
    scrollarea_->setWidgetResizable(true);
    //scrollarea_->setBackgroundRole(QPalette::Dark);

    //insert to tabs
    QWidget *scrollWidget = xclu::vwidget(0, scrollarea_, 0);


    auto *tabs = page_builder.tabs;
    tabs->addTab(scrollWidget, item->title());
    //устанавливаем подсказку
    tabs->setTabToolTip(tabs->count()-1, get_tip());

    //reset position
    page_builder.pos = int2(0,0);

    //track changes of scroll area
    connect(scrollarea_->verticalScrollBar(), SIGNAL (valueChanged(int)), this, SLOT (on_vscroll_changed()));

}

//---------------------------------------------------------------------
XGuiPage::~XGuiPage() {

}

//---------------------------------------------------------------------
//закончить страницу
/*static*/ void XGuiPage::finalize_page(XGuiPageBuilder &page_builder) {
    if (page_builder.grid) {
        //insert spacer at the end
        QSpacerItem *spacer = new QSpacerItem(1,10);
        page_builder.grid->addItem(spacer,page_builder.pos.y,0,1,2);
        page_builder.grid->setRowStretch(page_builder.pos.y,1);
        page_builder.pos.y++;
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
