#include "qt_widgets.h"
#include "xmoduleproject.h"
#include "incl_cpp.h"
#include "registrarxmodule.h"
#include "project_props.h"


//Register implementation class
REGISTER_XMODULE(Project)

//---------------------------------------------------------------------
XModuleProject::XModuleProject(QString class_name)
    :XModule(class_name)
{

}

//---------------------------------------------------------------------
XModuleProject::~XModuleProject()
{

}

//---------------------------------------------------------------------
void XModuleProject::on_loaded() {
    if (is_enabled()) {
        apply_control_values();
    }
}

//---------------------------------------------------------------------
void XModuleProject::apply_control_values() {
    xc_working_properties().set_frame_rate(geti_frame_rate());
    xc_working_properties().set_autostart(geti_autostart(), geti_autostart_wait_sec());
    xc_working_properties().set_dont_save_at_exit(geti_dont_save_at_exit());
}

//---------------------------------------------------------------------
void XModuleProject::start() {

    apply_control_values();

    //frame number
    seti_frame(xc_frame());

    // Watchdog
    watchdog_ = geti_watchdog_enabled();
        watch_frame_ = 0;

        if (watchdog_) {
            WatchdogThreadParams params;
            params.wait_sec = geti_watchdog_wait_sec();
            params.tick_sec = geti_watchdog_tick_sec();
            params.threshold_rate = getf_watchdog_threshold_rate();

            thread_ = new WatchdogThread();
            thread_->set_params(params);
            //connect(workerThread, &WorkerThread::resultReady, this, &MyObject::handleResults);
            //connect(workerThread, &WorkerThread::finished, workerThread, &QObject::deleteLater);
            thread_->start();

        }

}

//---------------------------------------------------------------------
void XModuleProject::update() {
    setf_elapsed_time_sec(xc_elapsed_time_sec());

    float dt = xc_dt();
    setf_dt(dt);

    float fps = 10000;
    if (dt > 0) fps = 1.0 / dt;
    setf_measured_frame_rate(fps);

    //frame number
    //increase_int_frame();
    seti_frame(xc_frame());

    // Watchdog
    if (watchdog_) {
          watch_frame_ = geti_watchdog_frame();
          thread_->update_frame(watch_frame_);

          setf_watchdog_measured_fps(thread_->measured_fps());
      }

      //Test pause
      if (geti_test_pause()) {
          QThread::sleep(3);
      }

}

//---------------------------------------------------------------------
void XModuleProject::stop() {
    if (watchdog_) {
        thread_->terminate();
        delete thread_;
        thread_ = 0;
    }
}

//---------------------------------------------------------------------
//---------------------------------------------------------------------
//---------------------------------------------------------------------
void WatchdogThread::run() {
    sleep(params_.wait_sec);
    while (isRunning()) {
        int delta = frame_ - last_frame_;   //TODO mutex to read frame_
        if (delta >= 0) {
            fps_ = float(delta) / qMax(params_.tick_sec,1);
            int expected = params_.tick_sec * params_.threshold_rate;
            if (delta < expected) {
                xc_console_append("Watchdog fired, terminating app");
                xc_console_repaint();

                _Exit(0);       // Exit hardly, without notifications - we need guarantee what it's happen
                // exit(0);  commented, because it's "soft" exit.
            }
        }
        //qDebug() << "watchdog tick";
        last_frame_ = frame_;
        sleep(params_.tick_sec);
    }
    //emit resultReady(result);
}

//---------------------------------------------------------------------
