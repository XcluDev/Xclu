#include "xclassexecute.h"
#include "incl_cpp.h"
#include "registrarxclass.h"
#include <QProcess>
#include "project_props.h"
#include "xobjectvis.h"


//registering module implementation
REGISTER_XCLASS(Execute)

//---------------------------------------------------------------------
XClassExecute::XClassExecute(QString class_name)
    :XClass(class_name)
{

}

//---------------------------------------------------------------------
XClassExecute::~XClassExecute()
{

}

//---------------------------------------------------------------------
void XClassExecute::start() {
    //run
    sete_status(status_Not_Started);
    seti_exit_code(0);

    clear_string_error_details();

    //read, write
    console_clear();

    //debug
    seti_debug_executed_times(0);
    seti_debug_write_times(0);
    seti_debug_read_times(0);
    seti_debug_received_times(0);
    clear_string_debug_folder_path();
    clear_string_debug_file_path();

    //image
    getobject_console_write_image_transformed()->write().data().link(image_transformed_holder_);
    getobject_console_write_image_transformed()->write().data().data<XRaster>()->clear();

    //process
    subprocess_.reset();

    crashed_ = false;

    finished_ = false;

    was_written_ = false;

    //run at first frame
    if (gete_execute_event() == execute_event_At_First_Frame) {
        process_run();
    }
}

//---------------------------------------------------------------------
void XClassExecute::update() {
    bool need_run = false;
    //buttons
    if (geti_run_button()) {
        need_run = true;
    }
    if (geti_stop_button()) {
        process_stop();
    }

    //events
    auto execute_event = gete_execute_event();
    if (execute_event == execute_event_Each_Frame) {
        need_run = true;
    }

    //process if finished
    if (finished_) {
        on_finish(exit_code_, QProcess::ExitStatus(exit_status_));
    }


    //write to console if required
    //if "geti_write_at_least_once" - then checks if we sent something
    //it's meaningful for sending images - often they are empty at start
    bool need_write = geti_write_each_frame() || (geti_write_at_least_once() && !was_written_);
    if (need_write) {
        console_write();
    }

    //run if required
    if (need_run) {
        process_run();
    }

    //read from console if required
    if (gete_read() == read_Each_Frame) {
        console_read();
    }


}

//---------------------------------------------------------------------
void XClassExecute::stop() {
    subprocess_.reset();
}

//---------------------------------------------------------------------
void XClassExecute::process_stop() {
    if (subprocess_.data()) {
        if (gete_status() == status_Running) {
            subprocess_->terminate();
            //on_finish(); //TODO I think it's not needed
        }
    }
}

//---------------------------------------------------------------------
void XClassExecute::console_clear() {
    clear_string_console_errors_text();
    clear_string_console_read_string();
    clear_string_console_read_text();

}

//---------------------------------------------------------------------
void XClassExecute::process_run() {
    if (gete_status() == status_Running)  {
        return;
    }

    finished_ = false;

    //compute paths
    QString folder = gets_folder_name();
    QString file_name_short = gets_file_name();

    folder = xc_project_folder() + "/" + folder;
    sets_debug_folder_path(folder);

    //file name
    xc_assert(!file_name_short.isEmpty(), "File Name is empty");
    QString file_name = folder + "/" + file_name_short;
    //if user provided absolute path - then use it - we detect it as if file_name doesn't extsts
    if (!QFileInfo::exists(file_name)) {
        file_name = file_name_short;
    }
    sets_debug_file_path(file_name);

    //check that folder exists
    xc_assert(xc_folder_exists(folder), "Folder '" + folder + "' doesn't exists");

    //check that file exists if required
    if (geti_file_must_exists()) {
        xc_assert(QFileInfo::exists(file_name), "File '" + file_name + "' doesn't exists");
    }

    //starting time
    //double start_time = xc_elapsed_time_sec();
    //setf_last_time(start_time);

    //qDebug() << "execute...";

    //create process
    //Note: this stops current process if exists - don't know, should we manage this additionally
    subprocess_.reset(new QProcess);

    QProcess &subprocess = *subprocess_;
    subprocess.setWorkingDirectory(folder);
    subprocess.setProgram(file_name);

    //arguments
    QStringList arguments;
    arguments << gets_args();
    subprocess.setArguments(arguments);

    //variables
    //timeout - if -1, then wait infinite
    int timeout = (geti_enable_timeout()) ? int(getf_timeout_sec()*1000): -1;

    crashed_ = false;

    //connect events listeners
    subprocess.setReadChannel(QProcess::StandardOutput);
    subprocess.setProcessChannelMode(QProcess::SeparateChannels); //separate output and error to process them differently
    //subprocess.setProcessChannelMode(QProcess::MergedChannels);

    connect(&subprocess, QOverload<QProcess::ProcessError>::of(&QProcess::error), this, &XClassExecute::crashed);

    //start process
    sete_status(status_Running);
    subprocess.start(QProcess::Unbuffered | QProcess::ReadWrite );

    //increase counter
    increase_int_debug_executed_times();

    //decide - wait finishing or work async
    auto thread_mode = gete_thread_mode();

    if (thread_mode == thread_mode_Wait_Finishing) {
        //sync run
        if (geti_write_at_least_once()) {
            console_write();
        }
        bool no_timeout = subprocess.waitForFinished(timeout);
        int exit_code = subprocess.exitCode();
        auto exit_status = subprocess.exitStatus();

        //process finish code and also read console
        on_finish(exit_code, exit_status, !no_timeout);
    }
    else {
        //async run
        //implement async events
        //connect(&subprocess, &QProcess::readyReadStandardOutput, this, &XClassExecute::onReadyReadStandardOutput);
        connect(&subprocess, &QProcess::readyReadStandardError, this, &XClassExecute::onReadyReadStandardError);

        connect(&subprocess, QOverload<int,QProcess::ExitStatus>::of(&QProcess::finished), this, &XClassExecute::finished);
    }

    //double time = xc_elapsed_time_sec();
    //setf_last_duration(time - start_time);
}

//---------------------------------------------------------------------
void XClassExecute::on_finish(int exit_code, QProcess::ExitStatus exit_status, bool timeout) {
    if (subprocess_.data()) {
        if (gete_status() == status_Running) {
            //read console
            if (gete_read() != read_Disabled) {
                console_read();
            }

            //read console error
            console_read_error();

            //exit code
            seti_exit_code(exit_code);

            //exit status
            bool success = (exit_status == QProcess::NormalExit) && (exit_code == 0);
            enum_status status = (timeout) ? status_Timeout : (success?status_Success:status_Error);
            sete_status(status);

            QString error_details;
            if (!timeout && crashed_) {
                error_details = crash_text_;
                status = status_Crashed;
            }
            sets_error_details(error_details);


            //delete process
            subprocess_.reset();

            //error handling
            if (status == status_Timeout) xc_exception("Timeout");
            if (status == status_Error) xc_exception("Execution error, see Run page for console error output");

        }
    }
}

//---------------------------------------------------------------------
void XClassExecute::onReadyReadStandardError() {
    //Note, this is can be async callback
    console_read_error();
}

//---------------------------------------------------------------------
//void XClassExecute::onReadyReadStandardOutput() {
    //Note, this is async callback

//}

//---------------------------------------------------------------------
//slot
void XClassExecute::finished(int exit_code, QProcess::ExitStatus exit_status) {
    //Note, this is can be async callback
    finished_ = true;
    exit_code_ = exit_code;
    exit_status_ = exit_status;
    //on_finish will be called on the next update:
    //on_finish(exit_code, exit_status, false);
}

//---------------------------------------------------------------------
void XClassExecute::crashed(QProcess::ProcessError error) {
    //Note, this is can be async callback

    //async process - inform main thread:
    crashed_ = true;

    switch (error) {
    case QProcess::FailedToStart:  crash_text_ = "File not found, resource error"; break;
    case QProcess::Crashed: crash_text_ = "Crashed"; break;
    case QProcess::Timedout: crash_text_ = "Timedout"; break;
    case QProcess::ReadError: crash_text_ = "ReadError"; break;
    case QProcess::WriteError: crash_text_ = "WriteError"; break;
    case QProcess::UnknownError: crash_text_ = "UnknownError"; break;
    default: crash_text_ = "Unknown reason";
    }

    crash_text_ = "Process crashed, the reason: " + crash_text_;

    //xc_exception("Execute Crashed");
}


//---------------------------------------------------------------------
void XClassExecute::console_read_error() {
    QProcess *subprocess = subprocess_.data();
    if (subprocess) {
        auto console_errors = gete_console_errors();
        if (console_errors != console_errors_Ignore) {
            QString text = subprocess->readAllStandardError();
            if (!text.isEmpty()) {
                append_string_console_errors_text(text);

                //stop process if required
                if (console_errors == console_errors_Show_And_Stop) {
                    crashed_ = true;
                    crash_text_ = "Process printed something to Error Console";
                }
            }
        }
    }
}

//---------------------------------------------------------------------
void XClassExecute::console_read() {
    QProcess *subprocess = subprocess_.data();
    if (subprocess) {
        auto data = subprocess->readAllStandardOutput();
        //increase counter
        increase_int_debug_read_times();

        bool is_new_data = !data.isEmpty();
        seti_console_read_received(is_new_data);
        if (is_new_data) {            
            auto read_type = gete_read_type();

            if (read_type == read_type_String) {
                sets_console_read_string(data);
            }
            if (read_type == read_type_Text) {
                //append or replace
                if (geti_console_read_text_append()) {
                    append_string_console_read_text(data);
                }
                else {
                    sets_console_read_text(data);
                }
            }
            if (read_type == read_type_Image) {
                xc_exception("Reading image from process console is not implemented yet");
            }

            //increase counter
            increase_int_debug_received_times();

            //Send bang
            xc_bang(get_strings_console_bang_on_received());

            //Write if required
            if (geti_write_on_receive()) {
                console_write();
            }
        }
    }

}

//---------------------------------------------------------------------
void XClassExecute::console_write() {
    if (gete_status() != status_Running) {
        return;
    }

    QProcess *subprocess = subprocess_.data();
    if (subprocess) {
        bool written = false;

        auto write_type = gete_write_type();
        if (write_type == write_type_String) {
            QString str = gets_console_write_string();
            auto ts = gete_line_term(); //None,\n,\r,\r\n
            if (ts == line_term__n) str += "\n";
            if (ts == line_term__r) str += "\r";
            if (ts == line_term__r_n) str += "\r\n";
            subprocess->write(str.toLatin1());
            written = true;
        }
        if (write_type == write_type_Text) {
            subprocess->write(gets_console_write_text().toLatin1());
            written = true;
        }
        if (write_type == write_type_Image) {
            written = console_write_image();   //If no image ready, then skip
        }

        if (written) {
            was_written_ = true;
            //increase counter
            increase_int_debug_write_times();

        }
    }

}

//---------------------------------------------------------------------
bool XClassExecute::console_write_image() {
    //Read image
    auto &image = image_write_input_u8c3_;
    auto console_image_read = getobject_console_write_image()->read();
    const XRaster *raster = console_image_read.data().data<XRaster>();
    if (!raster) {
        xc_console_warning("XClassExecute::console_write_image - can't sent image to console, because it's empty");
    }

    XRasterUtils::convert(*raster, image, XType::rgb_u8);

    //no transform
    if (!geti_console_write_image_transform()) {
        console_write_image(image.w, image.h, XType_channels(image.type), image.data<u8>());
    }
    else
    {
        //transform
        XRaster *img_use = &image;

        XRaster image_resized;// = image_write_input_;
        auto resize = gete_console_write_image_resize();
        if (resize == console_write_image_resize_Pixel_Size) {
            XRasterUtils::resize_nearest(image, image_resized, geti_console_write_image_sizex(), geti_console_write_image_sizey());
            img_use = &image_resized;
        }
        if (resize == console_write_image_resize_Rescale) {
            XRasterUtils::resize_nearest(image, image_resized, getf_console_write_image_resize_scale());
            img_use = &image_resized;
        }
        //now img contains current image, resized if necessary
        //convert to grayscale if required, or sent rgb8

        XRaster image_u8;
        if (geti_console_write_image_to_grayscale()) {
            XRasterUtils::convert(*img_use, image_u8, XType::u8);
            img_use = &image_u8;
        }

        //send to console
        console_write_image(img_use->w, img_use->h, XType_channels(img_use->type), img_use->data<u8>());

        //set to gui image
        *getobject_console_write_image_transformed()->write().data().data<XRaster>() = *img_use;

    }
    return true;

}

//---------------------------------------------------------------------
void XClassExecute::console_write_image(int w, int h, int channels, const uint8 *data) {
    QProcess *subprocess = subprocess_.data();
    int data_size = w*h*channels;

    //send header or not
    if (geti_console_write_image_header()) {
        //send data and header
        //make single array
        int header_size = 5;
        QVector<uint8> buffer(header_size + data_size);

        uint8* bufp = buffer.data();

        *(uint16 *)bufp = w;
        *(uint16 *)(bufp+2) = h;
        *(uint8 *)(bufp+4) = channels;
        for (int i=0; i<data_size; i++) {
            bufp[i+header_size] = data[i];  //TODO use memcpy
        }

        subprocess->write((char *)bufp, buffer.size());
    }
    else {
        //only data without header
        subprocess->write((char *)data, data_size);
    }
}

//---------------------------------------------------------------------
