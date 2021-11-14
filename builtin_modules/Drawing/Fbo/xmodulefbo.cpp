#include "xmodulefbo.h"
#include <QApplication>
#include <QScreen>

#include "incl_cpp.h"
#include "registrarxmodule.h"
#include "xc_project.h"
#include "module.h"

//registering module implementation
REGISTER_XMODULE(Fbo)

//---------------------------------------------------------------------
XModuleFbo::XModuleFbo(QString class_name)
    :XModule(class_name)
{

}

//---------------------------------------------------------------------
XModuleFbo::~XModuleFbo()
{

}

//---------------------------------------------------------------------
void XModuleFbo::start() {
    //создание и установка начальных настроек окна
    //setup_window();

    //установка начальных обновляемых параметров
    //update_window();
}

//---------------------------------------------------------------------
void XModuleFbo::update() {

    //update_window();   //обновляем данные
}


//---------------------------------------------------------------------
void XModuleFbo::stop() {
   // window_.reset();
}

//---------------------------------------------------------------------
//Вызов
/*void XModuleFbo::on_custom_call(QString function, XObject *input, XObject *output) {
    //"sound_buffer_add"
    //if (function == functions_names::sound_buffer_add()) {

        //получаем доступ к данным и звуковому буферу
        //DataAccess access(data_);
        //qDebug() << "PCM params: " << data_.image_background << data_.pcm_speed_hz;
        //XObjectRead sound(input);

        //float sample_rate = sound.var_int("sample_rate");
        //return;
    //}

}*/

//---------------------------------------------------------------------

