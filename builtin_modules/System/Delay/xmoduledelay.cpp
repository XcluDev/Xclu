#include "xmoduledelay.h"
#include "incl_cpp.h"
#include "registrarxmodule.h"
#include <QThread>
#include "xcore.h"


//registering module implementation
REGISTER_XMODULE(Delay)

//---------------------------------------------------------------------
XModuleDelay::XModuleDelay(QString class_name)
    :XModule(class_name)
{

}

//---------------------------------------------------------------------
XModuleDelay::~XModuleDelay()
{

}

//---------------------------------------------------------------------
void XModuleDelay::impl_start() {
    //start measure dirst delay
    register_bang_time();

    sets_time_left_hms("");
}

//---------------------------------------------------------------------
void XModuleDelay::impl_update() {
    double delay_sec=0;
    auto measure = gete_measure();
    switch (measure) {
    case measure_HMS: delay_sec = geti_hms_hours()*60*60 + geti_hms_minutes()*60 + getf_hms_seconds();
        break;
    case measure_Hours: delay_sec = getf_hours()*60*60;
        break;
    case measure_Minutes: delay_sec = getf_minutes()*60;
        break;
    case measure_Seconds: delay_sec = getf_seconds();
        break;
    default:
        xclu_exception("XModuleDelay::impl_update - bad `measure` value");
    }

    xclu_console_append(QString("delay %1").arg(delay_sec));

    auto working_mode = gete_working_mode();
    switch (working_mode) {
    case working_mode_Pause_Execution:
        register_bang_time();
        QThread::msleep(delay_sec*1000);
        break;
    case working_mode_Bang:
        update_bang(delay_sec);
        break;
    default:
        xclu_exception("XModuleDelay::impl_update - bad `working_mode` value");

    }

}

//---------------------------------------------------------------------
void XModuleDelay::impl_stop() {

}

//---------------------------------------------------------------------
void XModuleDelay::register_bang_time() {
    time_ = xcore_elapsed_time_sec();
}

//---------------------------------------------------------------------
void XModuleDelay::update_bang(float delay_sec) {
    double time = xcore_elapsed_time_sec();

    float delta = time - time_;
    if (delta <= 0) {
        register_bang_time();
    }


}

//---------------------------------------------------------------------
