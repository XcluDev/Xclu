#include "xclasstimer.h"
#include "incl_cpp.h"
#include "registrarxclass.h"
#include <QThread>
#include "project_props.h"


//registering module implementation
REGISTER_XCLASS(Timer)

//---------------------------------------------------------------------
XClassTimer::XClassTimer(QString class_name)
    :XClass(class_name)
{

}

//---------------------------------------------------------------------
XClassTimer::~XClassTimer()
{

}


//---------------------------------------------------------------------
void XClassTimer::set_working(bool v) {
    working_ = v;
    seti_working(v);
}

//---------------------------------------------------------------------
void XClassTimer::start() {
    set_working(false);

    sets_time_left_hms("");
    setf_time_left_sec(0);
    setf_time_elapsed_sec(0);
    setf_time_uniform(0);
}

//---------------------------------------------------------------------
void XClassTimer::update() {
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
        xc_exception("XClassTimer::update - bad `measure` value");
    }

    //xc_console_append(QString("delay %1").arg(delay_sec));

    auto working_mode = gete_working_mode();
    switch (working_mode) {
    case working_mode_Pause_Execution:
        register_bang_time();
        xc_sleep_sec(delay_sec);
        break;
    case working_mode_Bang:
        update_bang(delay_sec);
        break;
    default:
        xc_exception("XClassTimer::update - bad `working_mode` value");

    }

    //buttons
    if (geti_stop_button()) {
        set_working(false);
    }
    if (geti_one_shot_button()) {
        one_shot();
    }

    //auto-restart
    if (geti_repeating() && !working_) {
        one_shot();
    }
}

//---------------------------------------------------------------------
void XClassTimer::stop() {

}

//---------------------------------------------------------------------
//void XClassTimer::on_button_pressed(QString button_id) {
//}

//---------------------------------------------------------------------
void XClassTimer::one_shot() {
    register_bang_time();
    working_ = true;
    seti_working(true);
}

//---------------------------------------------------------------------
void XClassTimer::register_bang_time() {
    time_ = xc_elapsed_time_sec();
}

//---------------------------------------------------------------------
void XClassTimer::update_bang(float delay_sec) {
    if (working_) {
        double time = xc_elapsed_time_sec();

        float delta = time - time_;
        if (delta >= delay_sec) {
            bang();
            set_working(false);
        }

        //print time
        float left_sec = xclampf(time_ + delay_sec - time, 0, delay_sec);
        float uniform = (delay_sec > 0) ? xmapf_clamped(delta, 0, delay_sec, 0, 1) : 1;
        float elapsed_sec = xclampf(delta, 0, delay_sec);

        setf_time_left_sec(left_sec);
        setf_time_uniform(uniform);
        setf_time_elapsed_sec(elapsed_sec);
        sets_time_left_hms(xparse_seconds_to_hms(left_sec));
    }

}

//---------------------------------------------------------------------
void XClassTimer::bang() {
    //send bangs
    XModuleUtils::press_button_by_link(get_strings_bang_list());
}

//---------------------------------------------------------------------
