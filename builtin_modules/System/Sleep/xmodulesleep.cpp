#include "xmodulesleep.h"
#include "incl_cpp.h"
#include "registrarxmodule.h"
#include <QThread>
#include "xcore.h"


//registering module implementation
REGISTER_XMODULE(Sleep)

//---------------------------------------------------------------------
XModuleSleep::XModuleSleep(QString class_name)
    :XModule(class_name)
{

}

//---------------------------------------------------------------------
XModuleSleep::~XModuleSleep()
{

}

//---------------------------------------------------------------------
void XModuleSleep::impl_start() {
    //start measure dirst delay
    register_bang_time();

    sets_time_left_hms("");
}

//---------------------------------------------------------------------
void XModuleSleep::impl_update() {
    double delay_sec=0;
    auto period = gete_period();
    switch (period) {
    case period_HMS: delay_sec = geti_hms_hours()*60*60 + geti_hms_minutes()*60 + getf_hms_seconds();
        break;
    case period_Hours: delay_sec = getf_hours()*60*60;
        break;
    case period_Minutes: delay_sec = getf_minutes()*60;
        break;
    case period_Seconds: delay_sec = getf_seconds();
        break;
    default:
        xclu_exception("XModuleSleep::impl_update - bad `measure` value");
    }

    //xclu_console_append(QString("delay %1").arg(delay_sec));

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
        xclu_exception("XModuleSleep::impl_update - bad `working_mode` value");

    }

    //buttons
    if (geti_bang_now()) {
        bang();
    }
    if (geti_restart()) {
        register_bang_time();
    }
}

//---------------------------------------------------------------------
void XModuleSleep::impl_stop() {

}

//---------------------------------------------------------------------
//void XModuleSleep::impl_button_pressed(QString button_id) {
//}

//---------------------------------------------------------------------
void XModuleSleep::register_bang_time() {
    time_ = xcore_elapsed_time_sec();
}

//---------------------------------------------------------------------
void XModuleSleep::update_bang(float delay_sec) {
    double time = xcore_elapsed_time_sec();

    float delta = time - time_;
    if (delta >= delay_sec) {
        bang();
    }

    //print remained time
    float left_sec = qMax(time_ + delay_sec - time, 0.0);
    sets_time_left_hms(xparse_seconds_to_hms(left_sec));


}

//---------------------------------------------------------------------
void XModuleSleep::bang() {
    register_bang_time();

    //send bangs
    XCORE.bang(gets_bang_list());
}

//---------------------------------------------------------------------
