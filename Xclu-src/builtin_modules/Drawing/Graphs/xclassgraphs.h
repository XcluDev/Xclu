#pragma once

//Drawing graphs

#include <QImage>
#include <QSet>
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
    QVector<QVector<float>> data_;    // Lines for drawing by a channel

    QString separator_;
    QVector<int> indices_;              // Indices of used columns. If empty - use all

    void parse_lines(QStringList lines);  // Push line for processing

    // File read
    QStringList file_;  // text file used for reading or emulation
    int file_pos_ = 0;  // line for reading

    float lines_to_send_ = 0;
};

