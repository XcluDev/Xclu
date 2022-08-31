#pragma once

//BCI Neuroplay, https://neuroplay.ru

#include <QImage>
#include "sdk_h.h"
#include "xclasswidget.h"
#include "xobjectvis.h"
#include "xprotecteddata.h"
#include "sdk_h.h"
#include "neuroplaypro.h"
#include "xtimebuffer.h"

class XClassBciNeuroplay: public XClass
{
public:
    XClassBciNeuroplay(QString class_name);
    ~XClassBciNeuroplay();
protected:
#include "auto.h"
    virtual void on_loaded();
    virtual void start();
    virtual void update();
    virtual void stop();
    virtual void on_button_pressed(QString button_id);

    virtual void draw(QPainter &painter, int w, int h);

protected:
    QScopedPointer<NeuroplayPro> neuroplay_;
    NeuroplayDevice *device_ = nullptr;
    NeuroplayDeviceInfo info_;

    void connect_();
    void disconnect_();

    void on_deviceConnected(NeuroplayDevice *device);

    void reset_stat();
    void update_stat();
    void inc_requests();
    void inc_received();
    int num_requests_ = 0;
    int num_received_ = 0;

    QString exception_; // Not empty in case of errors from BCI device

    void rec_start();
    void rec_stop();
    void rec_clear();
    void rec_update();
    void rec_update_status(QString status);
    void rec_data(QVector<float> values);
    bool recording_ = false;
    float rec_time_start_ = 0;
    QString rec_file_;

    QStringList rec_data_;


    // Graphs
    void set_graphs(const NeuroplayDevice::ChannelsData &data);
    QVector<QVector<QPointF>> graphs_lines_;    // Lines for drawing
    QVector<QVector<float>> graphs_;     // Current frame

    // Eyes Blink
    void update_blink();
    QVector<int> blink_channels_;
    void setup_blink_channels();

    // Rhythms
    // Buffering rhythms values for blink detection
    void set_rhythms(const NeuroplayDevice::ChannelsRhythms &rhythms);
    void process_rhythms(const NeuroplayDevice::ChannelsRhythms &rhythms);
    XTimeBuffer<NeuroplayDevice::ChannelsRhythms> rhythms_buffer_;

};

