#include "xmodulewebcamera.h"
#include "incl_cpp.h"
#include "registrarxmodule.h"
#include <QProcess>
#include "xc_project.h"

#include <QMediaService>
#include <QMediaRecorder>
#include <QCameraViewfinder>
#include <QCameraInfo>
#include <QMediaMetaData>
#include <QCamera>
#include <QAbstractVideoSurface>

#include <QImageWriter>
#include <QImageReader>

#include "xobjectimage.h"

//registering module implementation
REGISTER_XMODULE(Webcamera)


//---------------------------------------------------------------------
XModuleWebcameraSurface::XModuleWebcameraSurface(XModuleWebcamera *module) {
    module_ = module;
}

//---------------------------------------------------------------------
QList<QVideoFrame::PixelFormat> XModuleWebcameraSurface::supportedPixelFormats(
        QAbstractVideoBuffer::HandleType handleType) const
{
    Q_UNUSED(handleType); //это просто пометка, чтобы компилятор не говорил что переменная не используется

    // Return the formats you will support
    return QList<QVideoFrame::PixelFormat>() << QVideoFrame::Format_RGB32; // << ...; // here return whatever formats you will handle

}

//---------------------------------------------------------------------
bool XModuleWebcameraSurface::present(const QVideoFrame &frame)
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

        XModuleWebcameraSurfaceData &data = module_->surface_data();
        DataAccess access(data);

        //(ловим исключение, чтобы в случае ошибки мютекс не заблокировался)
        try {
            data.is_new_frame = 1;
            data.captured_frames++;

            bool mirrory = true;        //включаем переворот по Y на Windows
            XObject &image = data.image;
            XObjectImage::create_from_QImage(image, img, data.channels, data.data_type, false, mirrory);
        }
        catch(XException& e) {
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
XModuleWebcamera::XModuleWebcamera(QString class_name)
    :XModule(class_name), surface_(this)
{

}

//---------------------------------------------------------------------
XModuleWebcamera::~XModuleWebcamera()
{
    stop_camera();
}

//---------------------------------------------------------------------
void XModuleWebcamera::on_loaded() {
    clear_string_frames_captured();
    clear_string_local_console();
}

//---------------------------------------------------------------------
void XModuleWebcamera::on_button_pressed(QString button) {
    if (button == button_print_devices()) {
        print_devices();
    }
}

//---------------------------------------------------------------------
void XModuleWebcamera::start() {
    //здесь мы не стартуем камеру, так как делаем это в update
    //в зависимости от capture_source

    //Очистка переменных
    camera_tried_to_start_ = false;

    //данные surface
    {
        DataAccess access(data_);
        data_.clear();
    }

    //link transformed image
    transformed_image_gui_.clear();
    setobject_image_transformed(&transformed_image_gui_);

    processed_frames_ = 0;

    set_started(false); //также ставит gui-элемент is_started

    clear_string_connected_device_name();
    seti_is_new_frame(0);

    clear_string_frames_captured();
    clear_string_local_console();

    //------------------------------------

}

//---------------------------------------------------------------------
void XModuleWebcamera::update() {

    //захват с камеры или считывание изображений
    auto source = gete_capture_source();
    if (source == capture_source_Camera) update_camera();
    if (source == capture_source_Load_Frames) update_load_frames();
    //запись кадров - внутри проверяется, что новый кадр
    //if (geti_save_frames")) {
    //    update_save_frames();
    //}

    //обработка ошибки
    {
        DataAccess access(data_);
        data_.err.throw_error();
    }
}

//---------------------------------------------------------------------
void XModuleWebcamera::stop() {
    //qDebug() << "stop";
    stop_camera();

}

//---------------------------------------------------------------------
void XModuleWebcamera::update_camera() {
    //запуск камеры, если еще не запущена
    start_camera();

    //если камера не стартовала - то делать нечего
    //TODO возможно стоит попробовать запустить камеру снова через некоторое время
    if (!camera_started_) return;

    //на всякий случай ставим, что нет новых кадров
    //чтобы в случае ошибки не осталось "1"
    seti_is_new_frame(0);

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
        seti_is_new_frame(is_new_frame);
        processed_frames_++;

        //копируем изображение для использования вовне и показа в GUI
        {
            auto image_write = getobject_image()->write();
            XObject *object = image_write.pointer();

            DataAccess access(data_);
            data_.image.copy_to(object);
        }

        //if transformation is required - do it
        transform();
    }

    //метка числа обработанных кадров
    QString processed = QString("Captured %1, Processed %2, Dropped %3 frame(s)")
            .arg(data_.captured_frames).arg(processed_frames_).arg(data_.captured_frames-processed_frames_);
    sets_frames_captured(processed);

}


//---------------------------------------------------------------------
//transformation - crop, mirror
void XModuleWebcamera::transform() {
    if (geti_transform()) {
        //read
        XObjectImage::to_raster(getobject_image(), input_image_);
        if (!input_image_.is_empty())  {
            //crop to square
            transformed_image_ = (geti_crop_to_square()) ? input_image_.crop_to_square() : input_image_;

            //mirror
            if (geti_mirror_x()) {
                transformed_image_.mirror(true,false);
            }

            //rotate
            auto rotate = gete_rotate();
            if (rotate == rotate_90) transformed_image_.rotate(90);
            if (rotate == rotate_180) transformed_image_.rotate(180);
            if (rotate == rotate_270) transformed_image_.rotate(270);

            //set to gui image
            XObjectImage::create_from_raster(transformed_image_gui_, transformed_image_);

        }

    }
}

//---------------------------------------------------------------------
//печать в консоль доступных камер
void XModuleWebcamera::print_devices() {
    QStringList list;
    list.append("Connected Web Cameras:");
    //xc_console_append("Connected Web Cameras:");

    bool print_serials = geti_print_serials();

    const QList<QCameraInfo> cameras = QCameraInfo::availableCameras();
    for (int i=0; i<cameras.size(); i++) {
        auto &info = cameras.at(i);
        QString camera = QString::number(i) + ": " + info.description();
        list.append(camera);
        if (print_serials) list.append("  '" + info.deviceName() + "'");
        //xc_console_append(camera);
    }
    clear_string_local_console();
    append_string_local_console(list, 1);
}

//---------------------------------------------------------------------
//печать в консоль разрешений запускаемой камеры
//внимание, эта функция запускает camera_->load()
void XModuleWebcamera::print_formats() {
    if (geti_print_formats()) {
        QString device_name = gets_connected_device_name();

        QStringList list;
        list.append("Supported Formats for '" + device_name + "'");
        //xc_console_append("Supported Formats for '" + device_name + "'");

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
            //xc_console_append(line);
        }
        clear_string_local_console();
        append_string_local_console(list, 1);
    }
}

//---------------------------------------------------------------------
void XModuleWebcamera::start_camera() {
    //запуск камеры
    if (!camera_tried_to_start_) {
        //пытаемся стартовать камеру
        camera_tried_to_start_ = true;

        //выбор устройства
        const QList<QCameraInfo> cameras = QCameraInfo::availableCameras();
        xc_assert(!cameras.empty(), "No connected devices");

        auto method = gete_select_device();
        switch (method) {
        case select_device_Default: {
            start_camera(QCameraInfo::defaultCamera());
            break;
        }
        case select_device_By_Index: {
                int name = geti_device_index();
                xc_assert(name >= 0 && name < cameras.size(), "Bad device index " + QString::number(name));
                start_camera(cameras[name]);
                break;
        }
        case select_device_By_Name: {
            QString name = gets_device_name();
            for (int i=0; i<cameras.size(); i++) {
                auto &info = cameras.at(i);
                if (info.description().contains(name)) {
                    start_camera(info);
                    break;
                }
            }
            break;
        }
        case select_device_By_Serial: {
            QString serial = gets_device_serial();
            for (int i=0; i<cameras.size(); i++) {
                auto &info = cameras.at(i);
                if (info.deviceName().contains(serial)) {
                    start_camera(info);
                    break;
                }
            }
            break;
        }
        default:
            //мы здесь не должны быть, так как все методы запуска рассмотренли,
            //поэтому выдаем ошибку
            xc_exception(QString("Bad select_device value '%1'").arg(method));
        }
    }

}

//---------------------------------------------------------------------
void XModuleWebcamera::start_camera(const QCameraInfo &cameraInfo) {
    //перед запуском камеры мы должны убедиться, что данные о формате считаны
    read_gui_output_data_format();

    camera_.reset(new QCamera(cameraInfo));
    camera_->load();    //вообще это не требуется, но пробуем устранить ошибку с зависанием при старте.

    connect(camera_.data(), &QCamera::stateChanged, this, &XModuleWebcamera::on_changed_camera_state);
    connect(camera_.data(), QOverload<QCamera::Error>::of(&QCamera::error), this, &XModuleWebcamera::on_camera_error);

    //считывание разрешения
    int2 res = get_gui_resolution();

    //считывание FPS
    int fps = get_gui_frame_rate();

    if (res.x > 0 && res.y > 0 && fps > 0) {
        //установка разрешения и FPS в камеру
        QCameraViewfinderSettings settings;
        if (res.x > 0 && res.y > 0) {
            settings.setResolution(res.x, res.y);
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
    sets_connected_device_name(device_name);
    append_string_local_console("Starting: " + device_name, 1);

    //если требуется, вывести в консоль поддерживаемые разрешения и частоты кадров
    //делаем тут это до старта камеры, и в функции делаем "camera_->load()",
    //чтобы в случае ее падения увидеть поддерживаемые разрешения
    print_formats();

    camera_->start();
}

//---------------------------------------------------------------------
//считать из GUI разрешение камеры, -1 - использовать по умолчанию
int2 XModuleWebcamera::get_gui_resolution() {
    QString res_string = getraw_resolution();
    if (res_string == "Camera_Default") {
        return int2(-1, -1);
    }
    int2 res(-1, -1);
    if (res_string == "Custom") {
        res = int2(geti_res_x(), geti_res_y());
    }
    else {
        //требуется распарсить "1280_x_720"
        auto list = res_string.split("_x_");
        xc_assert(list.size() == 2, "Can't start camera, bad resolution string " + res_string);
        res = int2(list.at(0).toInt(), list.at(1).toInt());
    }
    xc_assert(res.x > 0 && res.y > 0, QString("Can't start camera, bad resolution %1x%2").arg(res.x).arg(res.y));
    return res;
}

//---------------------------------------------------------------------
//считать из GUI частоту кадров, -1 - использовать по умолчанию
int XModuleWebcamera::get_gui_frame_rate() {
    QString fps_string = getraw_frame_rate();
    if (fps_string == "Camera_Default") {
        return -1;
    }
    int fps = 30;
    if (fps_string == "Custom") {
        fps = geti_custom_frame_rate();
    }
    else {
        //FPS записано числом в строке
        fps = fps_string.toInt();
    }
    xc_assert(fps > 0, QString("Can't start camera, bad frame rate %1").arg(fps));
    return fps;
}

//---------------------------------------------------------------------
//получить из GUI описание данных
void XModuleWebcamera::read_gui_output_data_format() {
    DataAccess access(data_);
    data_.channels = getraw_image_channels();
    data_.data_type = getraw_image_data_type();
}

//---------------------------------------------------------------------
void XModuleWebcamera::set_started(bool started) { //ставит camera_started_ и gui-элемент is_started
    camera_started_ = started;
    seti_is_started(started);
}

//---------------------------------------------------------------------
void XModuleWebcamera::on_changed_camera_state(QCamera::State state) {
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
void XModuleWebcamera::on_camera_error() {
    DataAccess access(data_);
    data_.err.setup(tr("Camera Error: ") + camera_->errorString());
}

//---------------------------------------------------------------------
void XModuleWebcamera::stop_camera() {
    if (camera_.data()) {
        //camera_->stop();  //Это не полная остановка, камера продолжает потреблять энергию
        camera_->unload();    //Остановка камеры
        camera_.reset();
    }
}

//---------------------------------------------------------------------
//работа с surface_ - чтобы он мог установить обновленное изображение
XModuleWebcameraSurfaceData &XModuleWebcamera::surface_data() {
    return data_;
}

//---------------------------------------------------------------------
//---------------------------------------------------------------------
//---------------------------------------------------------------------
void XModuleWebcamera::update_load_frames() {

}

//---------------------------------------------------------------------
void XModuleWebcamera::update_save_frames() {
    //проверить, что пришел новый кадр
}

//---------------------------------------------------------------------
