#ifndef XMODULEPROJECT_H
#define XMODULEPROJECT_H

//Control project:
//FPS
//Autostart

#include <QObject>
#include <QLabel>
#include <QThread>

#include "sdk_h.h"
#include "xclass.h"

struct WatchdogThreadParams {
    int wait_sec = 10;
    int tick_sec = 1;
    float threshold_rate=1;  //Minimal allowed frame rate to continue work, else kill this app, frames/sec
};

class WatchdogThread : public QThread
{
    Q_OBJECT
    void run() override;
public:
    void set_params(WatchdogThreadParams params) { params_ = params; }
    void update_frame(int new_frame) { frame_ = new_frame; }    //TODO mutex to set frame_
    float measured_fps() { return fps_; }
    //signals:
    //    void resultReady(const QString &s);
protected:
    WatchdogThreadParams params_;

    int frame_ = 0;     //TODO process with mutex
    int last_frame_ = 0;

    float fps_ = 0;
};


class XModuleProject: public XClass
{
    Q_OBJECT
public:
    XModuleProject(QString class_name);
    virtual ~XModuleProject();
protected:
#include "auto.h"

    //Выполнение
    virtual void on_loaded();
    virtual void start();
    virtual void update();
    virtual void stop();

    void apply_control_values();

    bool watchdog_ = false;
    int watch_frame_ = 0;

    //TODO use QScopedPointer
    WatchdogThread *thread_ = 0;

};

#endif // XMODULEPROJECT_H
