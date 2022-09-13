#include "xclassfragmentshader.h"
#include <QApplication>
#include <QScreen>

#include "incl_cpp.h"
#include "registrarxclass.h"
#include "project_props.h"

//registering module implementation
REGISTER_XCLASS(FragmentShader)

//---------------------------------------------------------------------
XClassFragmentShader::XClassFragmentShader(QString class_name)
    :XClass(class_name)
{

}

//---------------------------------------------------------------------
XClassFragmentShader::~XClassFragmentShader()
{

}

//---------------------------------------------------------------------
void XClassFragmentShader::start() {
    //создание и установка начальных настроек окна
    //setup_window();

    //установка начальных обновляемых параметров
    //update_window();
}

//---------------------------------------------------------------------
void XClassFragmentShader::update() {

    //update_window();   //обновляем данные
}


//---------------------------------------------------------------------
void XClassFragmentShader::stop() {
   // window_.reset();
}

//---------------------------------------------------------------------
//Вызов
/*void XClassFragmentShader::on_custom_call(QString function, XObject *input, XObject *output) {
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
