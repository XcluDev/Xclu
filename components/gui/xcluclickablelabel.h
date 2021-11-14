#ifndef XCLUCLICKABLELABEL_H
#define XCLUCLICKABLELABEL_H

//Clickable label
//https://wiki.qt.io/Clickable_QLabel

#include <QLabel>
#include <QWidget>
//#include <Qt>

class XcluClickableLabel: public QLabel
{
Q_OBJECT
public:
    explicit XcluClickableLabel(const QString& text="", QWidget* parent=0);
    virtual ~XcluClickableLabel();
signals:
    void clicked();
protected:
    void mousePressEvent(QMouseEvent* event);
};



#endif // XCLUCLICKABLELABEL_H
