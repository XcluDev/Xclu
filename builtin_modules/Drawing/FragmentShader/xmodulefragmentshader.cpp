#include "xmodulefragmentshader.h"
#include <QApplication>
#include <QScreen>

#include "incl_cpp.h"
#include "registrarxmodule.h"
#include "projectruntime.h"
#include "module.h"

//registering module implementation
REGISTRAR(FragmentShader)

//---------------------------------------------------------------------
/*static*/ XModuleFragmentShader *XModuleFragmentShader::new_module() {
    return new XModuleFragmentShader();
}

//---------------------------------------------------------------------
XModuleFragmentShader::XModuleFragmentShader()
    :XModule(*static_class_name_ptr)
{

}

//---------------------------------------------------------------------
XModuleFragmentShader::~XModuleFragmentShader()
{

}

//---------------------------------------------------------------------
void XModuleFragmentShader::impl_start() {
    //создание и установка начальных настроек окна
    //setup_window();

    //установка начальных обновляемых параметров
    //update_window();
}

//---------------------------------------------------------------------
void XModuleFragmentShader::impl_update() {

    //update_window();   //обновляем данные
}


//---------------------------------------------------------------------
void XModuleFragmentShader::impl_stop() {
   // window_.reset();
}

//---------------------------------------------------------------------
//Вызов
void XModuleFragmentShader::impl_call(QString /*function*/, XStruct * /*input*/, XStruct * /*output*/) {
    //"sound_buffer_add"
    //if (function == functions_names::sound_buffer_add()) {

        //получаем доступ к данным и звуковому буферу
        //DataAccess access(data_);
        //qDebug() << "PCM params: " << data_.image_background << data_.pcm_speed_hz;
        //XStructRead sound(input);

        //float sample_rate = sound.var_int("sample_rate");
        //return;
    //}

}

//---------------------------------------------------------------------
