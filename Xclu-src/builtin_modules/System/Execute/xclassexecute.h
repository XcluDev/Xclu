#pragma once

/*
Execute module implementation - running program from disk

On persistent mode:
Also support persistent connection via console;
it makes realtime link between Xclu and other programs such as Python.

Now you are able to use power of Python equipped with machine learning libraries
such as Tensor Flow with realtime graphics, sound and Arduino in Xclu!

Because you may set up Python and CUDA independently of Xclu,
currently it's the most flexible way of using machine learning algorithms in Xclu.

Technically, the communication goes through input and output console channels.
It's fast and requires minimal changes of your original Python code.

### Python side communication
https://en.wikiversity.org/wiki/Python_Concepts/Console_Output


### Credits
Thanks Pavel Vasev and Michail Bakhterev, who use the approach in their projects
and demonstrate me it's powerfullness.

Article on this:
Bakhterev M.O., Vasev P.A., One method for visualizing the results of supercomputer calculations
//Proceedings of the III All-Russian Scientific and Technical Conference
"Supercomputer Technologies" (SKT-2014), September 29 - October 4, 2014.
Taganrog, NII MVS SFedU. S. 50-55.
https://data2.lact.ru/f1/s/0/299/basic/1605/976/vasev-4.doc

*/


#include "sdk_h.h"
#include "xclass.h"
#include <QProcess>
#include "xraster.h"

class XClassExecute: public XClass
{
public:
    XClassExecute(QString class_name);
    virtual ~XClassExecute();
protected:
#include "auto.h"

    virtual void on_loaded() {}
    virtual void start();
    virtual void update();
    virtual void stop();

    virtual void on_button_pressed(QString button_id);

    QScopedPointer<QProcess> subprocess_;

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
    XRaster image_write_input_u8c3_;
    void console_write_image(int w, int h, int channels, const uint8 *data);

    XRaster image_transformed_holder_;

};

