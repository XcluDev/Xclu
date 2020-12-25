#include "xmodulefilecreate.h"
#include "incl_cpp.h"
#include "registrarxmodule.h"
#include <QProcess>
#include "xcore.h"


//registering module implementation
REGISTER_XMODULE(FileCreate)

//---------------------------------------------------------------------
XModuleFileCreate::XModuleFileCreate(QString class_name)
    :XModule(class_name)
{


}

//---------------------------------------------------------------------
XModuleFileCreate::~XModuleFileCreate()
{

}

//---------------------------------------------------------------------
void XModuleFileCreate::on_button_pressed(QString button_id) {
    if (button_id == button_create_file_btn()) {
        //Getting file size
        uint64 size = 0;
        switch (gete_file_size_unit()) {
        case file_size_unit_Bytes:
            size = geti_file_size_b();
            break;
        case file_size_unit_Kilobytes:
            size = uint64(getf_file_size_kb() * 1024);
            break;
        case file_size_unit_Megabytes:
            size = uint64(getf_file_size_mb() * (1024*1024));
            break;
        case file_size_unit_Gigabytes:
            size = uint64(getf_file_size_gb() * (1024*1024*1024));
            break;
        default:
            xc_exception("XModuleFileCreate::on_button_pressed - bad Unit of file size measure");
        }

        //Getting file name and checking it's not exists
        QString file_name0 = gets_file_name();
        xc_assert(!file_name0.isEmpty(), "Empty file name");
        QString file_path = xc_abs_path(gets_file_name());
        QString short_name = QFileInfo(file_name0).fileName();

        //Check file is not exists - currently we support writing only to new files
        xc_assert(!QFile(file_path).exists(), "File '" + short_name + "' already exists, please choose another");


        //Creating file
        QFile file(file_path);
        xc_assert(file.open(QIODevice::WriteOnly), "Can't create " + short_name);

        //Prepare block for writing
        uint64 block_size = 10*1024*1024;  //we will write file by such blocks
        QVector<uint8> block(block_size);

        auto contents = gete_contents();
        uint8 fixed_value = geti_fixed_value();
        if (contents == contents_Fixed_Byte) {
            block.fill(fixed_value);
        }

        //Write
        for (uint64 ready = 0; ready < size; ) {
            int toWrite = qMin(block_size, size-ready);
            if (toWrite > 0) {
                //fill by random is required
                if (contents == contents_Random_Bytes) {
                    for (int i=0; i<toWrite; i++) {
                        block[i] = xrandomi(0, 255);
                    }
                }

                //write
                qint64 written = file.write((char *)&block[0], toWrite);
                xc_assert(written != -1, "Error writing file " + short_name);
                xc_assert(written == toWrite, "Error while writing to file " + short_name + ", may be disk is full");

                ready += written;
            }
            else {
                break;
            }
        }


        xc_assert(file.flush(), "Error while closing file " + short_name + " after writing");

        //Inform user with result
        //TODO Check real file size...
        sets_last_operation(QString("Created %1: %2 bytes").arg(short_name).arg(size));

    }

}

//---------------------------------------------------------------------
void XModuleFileCreate::start() {


}

//---------------------------------------------------------------------
void XModuleFileCreate::update() {


}

//---------------------------------------------------------------------
void XModuleFileCreate::stop() {


}

//---------------------------------------------------------------------
