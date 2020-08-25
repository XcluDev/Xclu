#include "rtmodulefbo.h"
#include <QApplication>
#include <QScreen>

#include "incl_cpp.h"
#include "rtmoduleregistrar.h"
#include "projectruntime.h"
#include "module.h"

//заполнение имени класса и регистрация класса
REGISTRAR(Fbo)

//---------------------------------------------------------------------
/*static*/ RtModuleFbo *RtModuleFbo::new_module() {
    return new RtModuleFbo();
}

//---------------------------------------------------------------------
RtModuleFbo::RtModuleFbo()
    :RtModule(*static_class_name_ptr)
{

}

//---------------------------------------------------------------------
RtModuleFbo::~RtModuleFbo()
{

}

//---------------------------------------------------------------------
void RtModuleFbo::execute_start_internal() {
    //создание и установка начальных настроек окна
    //setup_window();

    //установка начальных обновляемых параметров
    //update_window();
}

//---------------------------------------------------------------------
void RtModuleFbo::execute_update_internal() {

    //update_window();   //обновляем данные
}


//---------------------------------------------------------------------
void RtModuleFbo::execute_stop_internal() {
   // window_.reset();
}

//---------------------------------------------------------------------
//Вызов
void RtModuleFbo::call_internal(QString /*function*/, XcluObject * /*input*/, XcluObject * /*output*/) {
    //"sound_buffer_add"
    //if (function == call_function_name::sound_buffer_add()) {

        //получаем доступ к данным и звуковому буферу
        //DataAccess access(data_);
        //qDebug() << "PCM params: " << data_.image_background << data_.pcm_speed_hz;
        //ObjectRead sound(input);

        //float sample_rate = sound.var_int("sample_rate");
        //return;
    //}

}

//---------------------------------------------------------------------

