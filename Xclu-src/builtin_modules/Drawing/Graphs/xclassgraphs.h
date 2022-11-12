#pragma once

//Drawing graphs

#include <QImage>
#include "sdk_h.h"
#include "xclasswidget.h"
#include "xobjectvis.h"
#include "xprotecteddata.h"
#include "sdk_h.h"
#include "xtimebuffer.h"

class XClassGraphs: public XClass
{
public:
    XClassGraphs(QString class_name);
    ~XClassGraphs();
protected:
#include "auto.h"
    virtual void on_loaded();
    virtual void start();
    virtual void update();
    virtual void stop();

    virtual void draw(QPainter &painter, int w, int h);

protected:
    // Graphs
    QVector<QVector<QPointF>> graphs_lines_;    // Lines for drawing

};

