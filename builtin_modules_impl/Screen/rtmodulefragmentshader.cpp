#include "rtmodulefragmentshader.h"
#include <QApplication>
#include <QScreen>

#include "incl_cpp.h"
#include "rtmoduleregistrar.h"
#include "projectruntime.h"
#include "module.h"

//заполнение имени класса и регистрация класса
REGISTRAR(FragmentShader)

//---------------------------------------------------------------------
/*static*/ RtModuleFragmentShader *RtModuleFragmentShader::new_module() {
    return new RtModuleFragmentShader();
}

//---------------------------------------------------------------------
RtModuleFragmentShader::RtModuleFragmentShader()
    :RtModule(*static_class_name_ptr)
{

}

//---------------------------------------------------------------------
RtModuleFragmentShader::~RtModuleFragmentShader()
{

}

//---------------------------------------------------------------------
void RtModuleFragmentShader::start_impl() {
    //создание и установка начальных настроек окна
    //setup_window();

    //установка начальных обновляемых параметров
    //update_window();
}

//---------------------------------------------------------------------
void RtModuleFragmentShader::update_impl() {

    //update_window();   //обновляем данные
}


//---------------------------------------------------------------------
void RtModuleFragmentShader::stop_impl() {
   // window_.reset();
}

//---------------------------------------------------------------------
//Вызов
void RtModuleFragmentShader::call_impl(QString /*function*/, XDict * /*input*/, XDict * /*output*/) {
    //"sound_buffer_add"
    //if (function == functions_names::sound_buffer_add()) {

        //получаем доступ к данным и звуковому буферу
        //DataAccess access(data_);
        //qDebug() << "PCM params: " << data_.image_background << data_.pcm_speed_hz;
        //XDictRead sound(input);

        //float sample_rate = sound.var_int("sample_rate");
        //return;
    //}

}

//---------------------------------------------------------------------
