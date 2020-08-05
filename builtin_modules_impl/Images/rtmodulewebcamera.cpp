#include "rtmodulewebcamera.h"
#include "incl_qtcpp.h"
#include "rtmoduleregistrar.h"
#include <QProcess>
#include "projectruntime.h"

#include <QMediaService>
#include <QMediaRecorder>
#include <QCameraViewfinder>
#include <QCameraInfo>
#include <QMediaMetaData>
#include <QCamera>
#include <QAbstractVideoSurface>

#include <QImageWriter>
#include <QImageReader>

#include "xcluobjectimage.h"



//заполнение имени класса и регистрация класса
REGISTRAR(Webcamera)


//---------------------------------------------------------------------
RtModuleWebcameraSurface::RtModuleWebcameraSurface(RtModuleWebcamera *module) {
    module_ = module;
}

//---------------------------------------------------------------------
QList<QVideoFrame::PixelFormat> RtModuleWebcameraSurface::supportedPixelFormats(
        QAbstractVideoBuffer::HandleType handleType) const
{
    Q_UNUSED(handleType); //это просто пометка, чтобы компилятор не говорил что переменная не используется

    // Return the formats you will support
    return QList<QVideoFrame::PixelFormat>() << QVideoFrame::Format_RGB32; // << ...; // here return whatever formats you will handle

}

//---------------------------------------------------------------------
bool RtModuleWebcameraSurface::present(const QVideoFrame &frame)
{
    //Q_UNUSED(frame);
    // Handle the frame and do your processing

    if (frame.isValid()) { // && ...) {
        QVideoFrame cloneFrame(frame);
        cloneFrame.map(QAbstractVideoBuffer::ReadOnly);

        //создаваемое изображение не копирует память
        const QImage img(cloneFrame.bits(),
                         cloneFrame.width(),
                         cloneFrame.height(),
                         QVideoFrame::imageFormatFromPixelFormat(cloneFrame.pixelFormat()));

        //auto format = cloneFrame.pixelFormat();
        //qDebug() << "format " << format;

        //обновляем изображение в surface_data().image
        //Камера давает кадры в собственном потоке, с собственной скоростью
        //но внутреннее состояние изображения в модуле меняется ТОЛЬКО при update
        //поэтому мы сохраняем изображение, но не вставляем его в результа работы модуля

        RtModuleWebcameraSurfaceData &data = module_->surface_data();
        DataAccess access(data);
        //ловим исключение, чтобы в случае ошибки мютекс не заблокировался
        try {
            data.is_new_frame = 1;
            data.captured_frames++;

            bool mirrory = true;        //включаем переворот по Y на Windows
            ObjectReadWrite image(data.image);
            XcluObjectImage::create_from_QImage(image, img, data.channels, data.data_type, false, mirrory);
        }
        catch(XCluException& e) {
            //отправляем информацию об ошибке в модуль
            DataAccess access(data);
            data.err = e.err();
        }

        cloneFrame.unmap();
        return true;
    }
    return false;

}

//---------------------------------------------------------------------
//---------------------------------------------------------------------
//---------------------------------------------------------------------
/*static*/ RtModuleWebcamera *RtModuleWebcamera::new_module() {
    return new RtModuleWebcamera();
}

//---------------------------------------------------------------------
RtModuleWebcamera::RtModuleWebcamera()
    :RtModule(*static_class_name_ptr), surface_(this)
{

}

//---------------------------------------------------------------------
RtModuleWebcamera::~RtModuleWebcamera()
{
    stop_camera();
}

//---------------------------------------------------------------------
void RtModuleWebcamera::execute_start_internal() {
    //здесь мы не стартуем камеру, так как делаем это в update
    //в зависимости от capture_source

    //Очистка переменных
    camera_tried_to_start_ = false;
    print_devices_worked_ = false;
    print_formats_worked_ = false;

    //данные surface
    {
        DataAccess access(data_);
        data_.clear();
    }

    processed_frames_ = 0;

    set_started(false); //также ставит gui-элемент is_started

    set_string("connected_device_name", "");
    set_int("is_new_frame", 0);
    set_string("frames_captured", "");

    set_string("local_console", "");

    //если требуется, напечатать все устройства
    print_devices();
    //------------------------------------

}

//---------------------------------------------------------------------
void RtModuleWebcamera::execute_update_internal() {
    //если требуется, напечатать все устройства
    print_devices();
    //если требуется, вывести в консоль поддерживаемые разрешения и частоты кадров
    print_formats();

    //захват с камеры или считывание изображений
    int source = get_int("capture_source");
    if (source == CaptureSourceCamera) update_camera();
    if (source == CaptureSourceLoad_Frames) update_load_frames();
    //запись кадров - внутри проверяется, что новый кадр
    //if (get_int("save_frames")) {
    //    update_save_frames();
    //}

    //обработка ошибки
    {
        DataAccess access(data_);
        data_.err.throw_error();
    }
}

//---------------------------------------------------------------------
void RtModuleWebcamera::execute_stop_internal() {
    //qDebug() << "stop";
    stop_camera();

}

//---------------------------------------------------------------------
void RtModuleWebcamera::update_camera() {
    //запуск камеры, если еще не запущена
    start_camera();

    //если камера не стартовала - то делать нечего
    //TODO возможно стоит попробовать запустить камеру снова через некоторое время
    if (!camera_started_) return;

    //на всякий случай ставим, что нет новых кадров
    //чтобы в случае ошибки не осталось "1"
    set_int("is_new_frame", 0);

    //начинаем менять данные для surface - обновлять и считывать
    bool is_new_frame;
    {
        DataAccess access(data_);
        is_new_frame = data_.is_new_frame;
        data_.is_new_frame = 0;
    }

    //считываем формат данных в data_ - они могут обновляться
    read_gui_output_data_format();

    //обрабатываем только новые кадры
    if (is_new_frame) {
        set_int("is_new_frame", is_new_frame);
        processed_frames_++;

        //копируем изображение для использования вовне и показа в GUI
        XcluObject *object = get_object("image");

        DataAccess access(data_);
        ObjectRead(&data_.image).copy_to(object);
    }

    //метка числа обработанных кадров
    QString processed = QString("Captured %1, Processed %2, Dropped %3 frame(s)")
            .arg(data_.captured_frames).arg(processed_frames_).arg(data_.captured_frames-processed_frames_);
    set_string("frames_captured", processed);


}


//---------------------------------------------------------------------
//печать в консоль доступных камер
void RtModuleWebcamera::print_devices() {
    int print = get_int("print_devices");
    if (!print) {
        print_devices_worked_ = false;
    }
    else {
        if (!print_devices_worked_) {
            print_devices_worked_ = true;
            QStringList list;
            list.append("Connected Web Cameras:");
            //xclu_console_append("Connected Web Cameras:");

            const QList<QCameraInfo> cameras = QCameraInfo::availableCameras();
            for (int i=0; i<cameras.size(); i++) {
                auto &info = cameras.at(i);
                QString camera = QString::number(i) + ": " + info.description();
                list.append(camera);
                //xclu_console_append(camera);
            }
            QString text = list.join("\n") + "\n\n";
            append_string("local_console", text);
        }
    }
}

//---------------------------------------------------------------------
//печать в консоль разрешений запускаемой камеры
//внимание, эта функция запускает camera_->load()
void RtModuleWebcamera::print_formats() {
    if (camera_tried_to_start_
            && !print_formats_worked_
            && get_int("print_formats")) {
        print_formats_worked_ = true;

        QString device_name = get_string("connected_device_name");

        QStringList list;
        list.append("Supported Formats for '" + device_name + "'");
        //xclu_console_append("Supported Formats for '" + device_name + "'");

        //загружаем камеру, чтобы можно было получить список форматов
        if (!camera_started_) {
            camera_->load();
        }

        //получаем список форматов
        auto settings = camera_->supportedViewfinderSettings();

        for (int i=0; i<settings.size(); i++) {
            auto &s = settings.at(i);

            int fps0 = s.minimumFrameRate();
            int fps1 = s.maximumFrameRate();
            QString line = (fps0 == fps1) ? QString("  %1x%2, %3 FPS"): QString("  %1x%2, %3-%4 FPS");
            line = line.arg(s.resolution().width()).arg(s.resolution().height())
                    .arg(fps0).arg(fps1);
            list.append(line);
            //xclu_console_append(line);
        }

        QString text = list.join("\n") + "\n\n";
        append_string("local_console", text);
    }
}

//---------------------------------------------------------------------
void RtModuleWebcamera::start_camera() {
    //запуск камеры
    if (!camera_tried_to_start_) {
        //пытаемся стартовать камеру
        camera_tried_to_start_ = true;

        //выбор устройства
        const QList<QCameraInfo> cameras = QCameraInfo::availableCameras();
        xclu_assert(!cameras.empty(), "No connected devices");

        SelectDevice method = SelectDevice(get_int("select_device"));
        switch (method) {
        case SelectDeviceDefault: {
            start_camera(QCameraInfo::defaultCamera());
            break;
        }
        case SelectDeviceByIndex: {
                int name = get_int("device_index");
                xclu_assert(name >= 0 && name < cameras.size(), "Bad device index " + QString::number(name));
                start_camera(cameras[name]);
                break;
        }
        case SelectDeviceByName: {
            QString name = get_string("device_name");
            for (int i=0; i<cameras.size(); i++) {
                auto &info = cameras.at(i);
                if (info.description().contains(name)) {
                    start_camera(info);
                    break;
                }
            }
            break;
        }
        default:
            //мы здесь не должны быть, так как все методы запуска рассмотренли,
            //поэтому выдаем ошибку
            xclu_exception(QString("Bad select_device value '%1'").arg(method));
        }
    }

}

//---------------------------------------------------------------------
void RtModuleWebcamera::start_camera(const QCameraInfo &cameraInfo) {
    //перед запуском камеры мы должны убедиться, что данные о формате считаны
    read_gui_output_data_format();

    camera_.reset(new QCamera(cameraInfo));
    camera_->load();    //вообще это не требуется, но пробуем устранить ошибку с зависанием при старте.

    connect(camera_.data(), &QCamera::stateChanged, this, &RtModuleWebcamera::on_changed_camera_state);
    connect(camera_.data(), QOverload<QCamera::Error>::of(&QCamera::error), this, &RtModuleWebcamera::on_camera_error);

    //считывание разрешения
    int w, h;
    get_gui_resolution(w, h);

    //считывание FPS
    int fps = get_gui_frame_rate();

    if (w > 0 && h > 0 && fps > 0) {
        //установка разрешения и FPS в камеру
        QCameraViewfinderSettings settings;
        if (w > 0 && h > 0) {
            settings.setResolution(w, h);
        }
        if (fps > 0) {
            settings.setMinimumFrameRate(fps);
            settings.setMaximumFrameRate(fps);
        }
        //TODO проверить, что камера такое поддерживает
        camera_->setViewfinderSettings(settings);
    }

    //ставим захват изображений в нашу surface_
    camera_->setViewfinder(&surface_);

    on_changed_camera_state(camera_->state());

    QString device_name = cameraInfo.description();
    set_string("connected_device_name", device_name);
    append_string("local_console", "Starting: " + device_name + "\n\n");

    //если требуется, вывести в консоль поддерживаемые разрешения и частоты кадров
    //делаем тут это до старта камеры, и в функции делаем "camera_->load()",
    //чтобы в случае ее падения увидеть поддерживаемые разрешения
    print_formats();

    camera_->start();
}

//---------------------------------------------------------------------
//считать из GUI разрешение камеры, -1 - использовать по умолчанию
void RtModuleWebcamera::get_gui_resolution(int &w, int &h) {
    QString res_string = get_string("resolution");
    if (res_string == "Camera_Default") {
        w = -1;
        h = -1;
        return;
    }
    if (res_string == "Custom") {
        w = get_int("res_x");
        h = get_int("res_y");
    }
    else {
        //требуется распарсить "1280_x_720"
        auto list = res_string.split("_x_");
        xclu_assert(list.size() == 2, "Can't start camera, bad resolution string " + res_string);
        w = list.at(0).toInt();
        h = list.at(1).toInt();
    }
    xclu_assert(w > 0 && h > 0, QString("Can't start camera, bad resolution %1x%2").arg(w).arg(h));
}

//---------------------------------------------------------------------
//считать из GUI частоту кадров, -1 - использовать по умолчанию
int RtModuleWebcamera::get_gui_frame_rate() {
    QString fps_string = get_string("frame_rate");
    if (fps_string == "Camera_Default") {
        return -1;
    }
    int fps = 30;
    if (fps_string == "Custom") {
        fps = get_int("custom_frame_rate");
    }
    else {
        //FPS записано числом в строке
        fps = fps_string.toUInt();
    }
    xclu_assert(fps > 0, QString("Can't start camera, bad frame rate %1").arg(fps));
    return fps;
}

//---------------------------------------------------------------------
//получить из GUI описание данных
void RtModuleWebcamera::read_gui_output_data_format() {
    DataAccess access(data_);
    data_.channels = get_string("image_channels");
    data_.data_type = get_string("image_data_type");
}

//---------------------------------------------------------------------
void RtModuleWebcamera::set_started(bool started) { //ставит camera_started_ и gui-элемент is_started
    camera_started_ = started;
    set_int("is_started", started);
}

//---------------------------------------------------------------------
void RtModuleWebcamera::on_changed_camera_state(QCamera::State state) {
    switch (state) {
    case QCamera::ActiveState:
        set_started(true);
        break;
    case QCamera::UnloadedState:
    case QCamera::LoadedState:
        set_started(false);
        break;
    }
}

//---------------------------------------------------------------------
void RtModuleWebcamera::on_camera_error() {
    DataAccess access(data_);
    data_.err.setup(tr("Camera Error: ") + camera_->errorString());
}

//---------------------------------------------------------------------
void RtModuleWebcamera::stop_camera() {
    if (camera_.data()) {
        //camera_->stop();  //Это не полная остановка, камера продолжает потреблять энергию
        camera_->unload();    //Остановка камеры
        camera_.reset();
    }
}

//---------------------------------------------------------------------
//работа с surface_ - чтобы он мог установить обновленное изображение
RtModuleWebcameraSurfaceData &RtModuleWebcamera::surface_data() {
    return data_;
}

//---------------------------------------------------------------------
//---------------------------------------------------------------------
//---------------------------------------------------------------------
void RtModuleWebcamera::update_load_frames() {

}

//---------------------------------------------------------------------
void RtModuleWebcamera::update_save_frames() {
    //проверить, что пришел новый кадр
}

//---------------------------------------------------------------------
