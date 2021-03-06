#include "xmodulefragmentshader.h"
#include <QApplication>
#include <QScreen>

#include "incl_cpp.h"
#include "registrarxmodule.h"
#include "xcore.h"
#include "module.h"

//registering module implementation
REGISTER_XMODULE(FragmentShader)

//---------------------------------------------------------------------
XModuleFragmentShader::XModuleFragmentShader(QString class_name)
    :XModule(class_name)
{

}

//---------------------------------------------------------------------
XModuleFragmentShader::~XModuleFragmentShader()
{

}

//---------------------------------------------------------------------
void XModuleFragmentShader::start() {
    //создание и установка начальных настроек окна
    //setup_window();

    //установка начальных обновляемых параметров
    //update_window();
}

//---------------------------------------------------------------------
void XModuleFragmentShader::update() {

    //update_window();   //обновляем данные
}


//---------------------------------------------------------------------
void XModuleFragmentShader::stop() {
   // window_.reset();
}

//---------------------------------------------------------------------
//Вызов
void XModuleFragmentShader::on_call(QString /*function*/, XObject * /*input*/, XObject * /*output*/) {
    //"sound_buffer_add"
    //if (function == functions_names::sound_buffer_add()) {

        //получаем доступ к данным и звуковому буферу
        //DataAccess access(data_);
        //qDebug() << "PCM params: " << data_.image_background << data_.pcm_speed_hz;
        //XObjectRead sound(input);

        //float sample_rate = sound.var_int("sample_rate");
        //return;
    //}

}

//---------------------------------------------------------------------
