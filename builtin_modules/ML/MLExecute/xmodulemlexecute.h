#ifndef XMODULEMLEXECUTE_H
#define XMODULEMLEXECUTE_H

/*
Universal ML train and running operations using bat/bash scripts, provided by user.
*/


#include "sdk_h.h"
#include "xclass.h"
#include <QProcess>

class XModuleMLExecute: public XClass
{
public:
    XModuleMLExecute(QString class_name);
    virtual ~XModuleMLExecute();
protected:
#include "auto.h"

    virtual void on_loaded() {}
    virtual void start();
    virtual void update();
    virtual void stop();

/*    QScopedPointer<QProcess> subprocess_;

    void process_run();
    void process_stop();

    void console_clear();
    void console_read();
    void console_read_error();

    void console_write();
    void on_finish(int exit_code, QProcess::ExitStatus exit_status, bool timeout = false);

protected slots:
    //void onReadyReadStandardOutput();
    void onReadyReadStandardError();
    void finished(int exit_code, QProcess::ExitStatus exit_status);
    void crashed(QProcess::ProcessError error);

protected:
    bool crashed_ = false;
    QString crash_text_;

    bool finished_ = false;
    int exit_code_ = 0;
    int exit_status_ = 0;

    bool was_written_ = false;  //was something was written to console or not
    //it's meaningful for sending images - often they are empty at start

    bool console_write_image();
    XRaster_u8c3 image_write_input_;
    void console_write_image(int w, int h, int channels, uint8 *data);

*/
};



#endif // XMODULEEXECUTE_H
