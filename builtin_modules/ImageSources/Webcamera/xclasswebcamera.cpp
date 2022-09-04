#include "xclasswebcamera.h"

#ifdef XCLU_WINDOWS
//For show USB devices, https://www.cyberforum.ru/win-api/thread2806892.html
//#include <windows.h>
//#include <iostream>
#endif

#include "incl_cpp.h"
#include "registrarxclass.h"
#include <QProcess>
#include "project_props.h"

#include <QMediaService>
#include <QMediaRecorder>
#include <QCameraViewfinder>
#include <QCameraInfo>
#include <QMediaMetaData>
#include <QCamera>
#include <QAbstractVideoSurface>

#include <QImageWriter>
#include <QImageReader>

#include "xobjectvis.h"
#include "xdrawhelper.h"

//registering module implementation
REGISTER_XCLASS(Webcamera)


//---------------------------------------------------------------------
XClassWebcameraSurface::XClassWebcameraSurface(XClassWebcamera *module) {
    module_ = module;
}

//---------------------------------------------------------------------
QList<QVideoFrame::PixelFormat> XClassWebcameraSurface::supportedPixelFormats(
        QAbstractVideoBuffer::HandleType handleType) const
{
    Q_UNUSED(handleType); //это просто пометка, чтобы компилятор не говорил что переменная не используется

    // Return the formats you will support
    return QList<QVideoFrame::PixelFormat>() << QVideoFrame::Format_RGB32; // << ...; // here return whatever formats you will handle

}

//---------------------------------------------------------------------
bool XClassWebcameraSurface::present(const QVideoFrame &frame)
{
    if (frame.isValid()) {
        QVideoFrame cloneFrame(frame);
        cloneFrame.map(QAbstractVideoBuffer::ReadOnly);

        // создаваемое изображение не копирует память,
        // но мы делаем переворот по y с помощью mirrored()
        const QImage qimage = QImage(cloneFrame.bits(),
                         cloneFrame.width(),
                         cloneFrame.height(),
                         QVideoFrame::imageFormatFromPixelFormat(cloneFrame.pixelFormat()))
                .mirrored();

        //auto format = cloneFrame.pixelFormat();
        //qDebug() << "format " << format;

        //обновляем изображение в surface_data().image
        //Камера давает кадры в собственном потоке, с собственной скоростью
        //но внутреннее состояние изображения в модуле меняется ТОЛЬКО при update
        //поэтому мы сохраняем изображение, но не вставляем его в результа работы модуля

        auto &data_protected = module_->surface_data();
        auto write = data_protected.write();
        auto &data = write.data();

        //(ловим исключение, чтобы в случае ошибки мютекс не заблокировался)
        try {
            data.is_new_frame = 1;
            data.captured_frames++;

            XRaster &raster = data.raster;

            XRasterUtils::convert(qimage, raster, data.desired_type);

            // Test
            //XRasterUtils::save(raster, "D:\\temp.png");
            XRasterUtils::load(raster, "D:\\temp.png");
        }
        catch(XException& e) {
            //отправляем информацию об ошибке в модуль            
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
XClassWebcamera::XClassWebcamera(QString class_name)
    :XClass(class_name), surface_(this)
{

}

//---------------------------------------------------------------------
XClassWebcamera::~XClassWebcamera()
{
    stop_camera();
}

//---------------------------------------------------------------------
void XClassWebcamera::on_loaded() {
    seti_frames_captured(0);
    seti_frames_dropped(0);
    clear_string_local_console();
}

//---------------------------------------------------------------------
void XClassWebcamera::on_button_pressed(QString button) {
    if (button == button_print_devices()) {
        print_devices();
    }
    //if (button == button_print_usb()) {
    //    print_usb();
    //}
}

//---------------------------------------------------------------------
void XClassWebcamera::draw(QPainter &painter, int w, int h) {
    if (!geti_draw_enabled()) {
        return;
    }
    auto image_read = geti_transform() ? getobject_image_transformed()->read():getobject_image()->read();
    const XObject *object = image_read.pointer();
    XDrawHelper::draw_XObject_fit(object, getf_draw_x(), getf_draw_y(), getf_draw_size(), painter, w, h);
}

//---------------------------------------------------------------------
void XClassWebcamera::start() {
    // Here we don't start the camera, and do it at the first update,
    // depending on capture_source.
    // So we perform "Resolver" computations.
    resolver_work();

    //Очистка переменных
    camera_tried_to_start_ = false;

    last_frame_time_ = 0;

    //данные surface
    {
        data_.write().data().clear();
    }

    //link images
    image_holder_u8c3_.clear();
    transformed_image_holder_u8c3_.clear();
    getobject_image()->write().data().link(image_holder_u8c3_);
    getobject_image_transformed()->write().data().link(transformed_image_holder_u8c3_);

    processed_frames_ = 0;

    set_started(false); //также ставит gui-элемент is_started

    clear_string_connected_device_name();
    clear_string_connected_device_serial();
    seti_is_new_frame(0);

    seti_frames_captured(0);
    seti_frames_dropped(0);
    clear_string_local_console();

    //------------------------------------

}

//---------------------------------------------------------------------
// Resolver working
// Resolve cameras indices based on given parts of serial number (higher priority) and names (lower priority).
void XClassWebcamera::resolver_work() {
    if (!geti_resolver_enabled()) return;
    const QList<QCameraInfo> cameras = QCameraInfo::availableCameras();
    int in_n = cameras.size();
    int out_n = geti_resolver_cameras();


    // First pass - collect independent scores
    QVector<int> scores(in_n * out_n);
    for (int y=0; y<out_n; y++) {
        QString name;
        QString serials_str;
        switch (y) {
        case 0: name = gets_resolver_name1(); serials_str = gets_resolver_serials1();
            break;
        case 1: name = gets_resolver_name2(); serials_str = gets_resolver_serials2();
            break;
        case 2: name = gets_resolver_name3(); serials_str = gets_resolver_serials3();
            break;
        case 3: name = gets_resolver_name4(); serials_str = gets_resolver_serials4();
            break;
        }
        auto serials = serials_str.split(" ");
        for (int x=0; x<in_n; x++) {
            QString Name = cameras.at(x).description();     // Human readable
            QString Serial = cameras.at(x).deviceName();    // Unique ID
            bool found_name = false;
            bool found_serial = false;
            if (!name.isEmpty() && Name.contains(name)) {
                found_name = true;
            }
            for (auto s: serials) {
                if (!s.isEmpty() && Serial.contains(s)) {
                    found_serial = true;
                    break;
                }
            }
            scores[x + in_n*y] = 2*found_serial + 1*found_name;
        }
    }
    // Second pass - find unique best matches for each real camera.
    // It can repeats many times.
    QVector<int> match(out_n);
    match.fill(-1);
    while (true) {
        bool found = false;
        for (int x=0; x<in_n; x++) {
            int bestv = -1;
            int besty = -1;
            int count = 0;
            for (int y=0; y<out_n; y++) {
                int v = scores[x + in_n*y];
                if (v == -1) continue;
                if (v == bestv) {
                    count++;
                }
                else {
                    if (v > bestv) {
                        bestv = v;
                        besty = y;
                        count = 1;
                    }
                }
            }
            if (count == 1) {   // We are interested in unique matches
                match[besty] = x;
                // Set scores for camera x in all y to -1 to prevent double selection
                for (int y=0; y<out_n; y++) {
                    scores[x + in_n*y] = -1;
                }
                // Set scores for resolver to prevent double checking
                for (int j=0; j<in_n; j++) {
                    scores[j + in_n*besty] = -1;
                }
                found = true;
            }
        }
        if (!found) {   // No more unique matches
            break;
        }
    }

    // Now we just found the best match, and choose the first in case of ambiguity
    for (int y=0; y<out_n; y++) {
        if (match[y] == -1) {
            int bestv = -1;
            int bestx = -1;
            int count = 0;
            for (int x=0; x<in_n; x++) {
                int v = scores[x + in_n*y];
                if (v == -1) continue;
                if (v == bestv) {
                    count++;
                }
                if (v > bestv) {
                    bestv = v;
                    bestx = x;
                    count = 1;
                }

            }
            if (count > 0) {
                //Warn if ambiguity
                if (count > 1) {
                    xc_console_append(QString("Webcamera Resolver ambiguity: physical camera %1 has several variants").arg(bestx));
                }
                // Set match
                match[y] = bestx;
                // Clear x in other cameras
                for (int y1=0; y1<out_n; y1++) {
                    scores[bestx + in_n*y1] = -1;
                }
            }
        }
    }

    // Warn if no matches
    for (int y=0; y<out_n; y++) {
        if (match[y] == -1) {
            xc_console_append(QString("Webcamera Resolver warning: no camera for slot %1").arg(y+1));
        }
    }

    // Now we define matches, set them to UI
    if (out_n >= 1) {
        sete_resolver_resulted_presence1(enum_resolver_resulted_presence1(match[0] >= 0));
        seti_resolver_resulted_index1((match[0] >= 0)?match[0]:1000);
    }
    if (out_n >= 2) {
        sete_resolver_resulted_presence2(enum_resolver_resulted_presence2(match[1] >= 0));
        seti_resolver_resulted_index2((match[1] >= 0)?match[1]:1000);
    }

    if (out_n >= 3) {
        sete_resolver_resulted_presence3(enum_resolver_resulted_presence3(match[2] >= 0));
        seti_resolver_resulted_index3((match[2] >= 0)?match[2]:1000);
    }

    if (out_n >= 4) {
        sete_resolver_resulted_presence4(enum_resolver_resulted_presence4(match[3] >= 0));
        seti_resolver_resulted_index4((match[3] >= 0)?match[3]:1000);
    }


}


//---------------------------------------------------------------------
void XClassWebcamera::update() {

    //захват с камеры или считывание изображений
    auto source = gete_capture_source();
    if (source == capture_source_Camera) update_camera();
    if (source == capture_source_Load_Frames) update_load_frames();

    //обработка ошибки
    {
        if (!geti_ignore_error_on_start()) {
            data_.read().data().err.throw_error();
        }
    }

    // Save image button
    if (geti_save_image()) {
        QString file_name = xc_absolute_path_from_project(gets_save_image_file_name());

        auto read = geti_transform() ? getobject_image_transformed()->read():getobject_image()->read();
        auto *raster = read.data().data<XRaster>();
        if (raster) {
            XRasterUtils::save(*raster,file_name);
            xc_console_append("Saved `" + file_name + "`");
        }
        else {
            xc_console_append("Not saved `" + file_name + "` - no image");
        }
    }
}

//---------------------------------------------------------------------
void XClassWebcamera::stop() {
    //qDebug() << "stop";
    stop_camera();

}

//---------------------------------------------------------------------
void XClassWebcamera::update_camera() {
    //запуск камеры, если еще не запущена
    start_camera();

    last_frame_time_ += xc_dt();

    // If camera not started or not long time the frame - try to restart
    bool auto_restart = geti_auto_restart();
    if (auto_restart) {
        if (last_frame_time_ >= geti_auto_restart_wait_seconds()) {
            xc_console_append("Restarting camera " + name());
            stop_camera();
            start_camera();
            last_frame_time_ = 0;

        }
    }
    if (!camera_started_) return;

    //на всякий случай ставим, что нет новых кадров
    //чтобы в случае ошибки не осталось "1"
    seti_is_new_frame(0);

    //начинаем менять данные для surface - обновлять и считывать
    bool is_new_frame;
    {
        auto write = data_.write();
        is_new_frame = write.data().is_new_frame;
        write.data().is_new_frame = 0;
    }

    //считываем формат данных в data_ - они могут обновляться
    read_gui_output_data_format();

    //обрабатываем только новые кадры
    if (is_new_frame) {
        seti_is_new_frame(is_new_frame);
        processed_frames_++;
        last_frame_time_ = 0;       // Reset timer of last frame received

        //копируем изображение для использования вовне и показа в GUI
        *getobject_image()->write().data().data<XRaster>() = data_.read().data().raster;

        //if transformation is required - do it
        transform();
    }

    //метка числа обработанных кадров
    seti_frames_captured(processed_frames_);
    seti_frames_dropped(data_.read().data().captured_frames-processed_frames_);

}


//---------------------------------------------------------------------
//transformation - crop, mirror
void XClassWebcamera::transform() {
    if (geti_transform()) {
        auto read = getobject_image()->read();
        const XRaster *raster = read.data().data<XRaster>();
        if (raster && !raster->is_empty())  {
            //crop to square
            auto write = getobject_image_transformed()->write();
            XRaster &transf = *write.data().data<XRaster>();
            transf = (geti_crop_to_square()) ? raster->crop_to_square() : *raster;

            //mirror
            if (geti_mirror_x()) {
                transf.mirror_inplace(true,false);
            }

            //rotate
            auto rotate = gete_rotate();
            if (rotate == rotate_90) transf.rotate_inplace(90);
            if (rotate == rotate_180) transf.rotate_inplace(180);
            if (rotate == rotate_270) transf.rotate_inplace(270);
        }
    }
}

//---------------------------------------------------------------------
//печать в консоль доступных камер
void XClassWebcamera::print_devices() {
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
void XClassWebcamera::print_formats() {
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
void XClassWebcamera::start_camera() {
    //запуск камеры
    if (!camera_tried_to_start_) {
        //пытаемся стартовать камеру
        camera_tried_to_start_ = true;

        bool ignore_error = geti_ignore_error_on_start();

        //выбор устройства
        const QList<QCameraInfo> cameras = QCameraInfo::availableCameras();
        xc_assert_ignore(!cameras.empty(), "No connected devices", ignore_error);

        auto method = gete_select_device();
        switch (method) {
        case select_device_Default: {
            start_camera(QCameraInfo::defaultCamera());
            break;
        }
        case select_device_By_Index: {
                int name = geti_device_index();
                xc_assert_ignore(name >= 0 && name < cameras.size(), "Bad device index " + QString::number(name), ignore_error);
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
void XClassWebcamera::start_camera(const QCameraInfo &cameraInfo) {
    //перед запуском камеры мы должны убедиться, что данные о формате считаны
    read_gui_output_data_format();

    camera_.reset(new QCamera(cameraInfo));
    camera_->load();    //вообще это не требуется, но пробуем устранить ошибку с зависанием при старте.

    connect(camera_.data(), &QCamera::stateChanged, this, &XClassWebcamera::on_changed_camera_state);
    connect(camera_.data(), QOverload<QCamera::Error>::of(&QCamera::error), this, &XClassWebcamera::on_camera_error);

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
    sets_connected_device_serial(cameraInfo.deviceName());
    append_string_local_console("Starting: " + device_name, 1);

    //если требуется, вывести в консоль поддерживаемые разрешения и частоты кадров
    //делаем тут это до старта камеры, и в функции делаем "camera_->load()",
    //чтобы в случае ее падения увидеть поддерживаемые разрешения
    print_formats();

    camera_->start();
}

//---------------------------------------------------------------------
//считать из GUI разрешение камеры, -1 - использовать по умолчанию
int2 XClassWebcamera::get_gui_resolution() {
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
int XClassWebcamera::get_gui_frame_rate() {
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
void XClassWebcamera::read_gui_output_data_format() {
    auto write = data_.write();
    auto &data = write.data();
    switch (gete_pixel_type()) {
    case pixel_type_Grayscale: data.desired_type = XType::u8;
    break;
    case pixel_type_RGB: data.desired_type = XType::rgb_u8;
        break;
    default:
        xc_exception(name() + " - bad type " + getraw_pixel_type());
    }
}

//---------------------------------------------------------------------
void XClassWebcamera::set_started(bool started) { //ставит camera_started_ и gui-элемент is_started
    camera_started_ = started;
    seti_is_started(started);
}

//---------------------------------------------------------------------
void XClassWebcamera::on_changed_camera_state(QCamera::State state) {
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
void XClassWebcamera::on_camera_error() {
    data_.write().data().err.setup(tr("Camera Error: ") + camera_->errorString());
}

//---------------------------------------------------------------------
void XClassWebcamera::stop_camera() {
    set_started(false);
    if (camera_.data()) {
        //camera_->stop();  //Это не полная остановка, камера продолжает потреблять энергию
        camera_->unload();    //Остановка камеры
        camera_.reset();
    }
    camera_tried_to_start_ = false;
}

//---------------------------------------------------------------------
//работа с surface_ - чтобы он мог установить обновленное изображение
XProtectedData_<XClassWebcameraSurfaceData> &XClassWebcamera::surface_data() {
    return data_;
}

//---------------------------------------------------------------------
//---------------------------------------------------------------------
//---------------------------------------------------------------------
void XClassWebcamera::update_load_frames() {

}

//---------------------------------------------------------------------
void XClassWebcamera::update_save_frames() {
    //проверить, что пришел новый кадр
}


//---------------------------------------------------------------------
// Show USB devices
// https://www.cyberforum.ru/win-api/thread2806892.html
// It appears that QT's cameras IDs not related to USB IDs, so commented this
//---------------------------------------------------------------------
// Print USB ports details (Windows only)
/*void XClassWebcamera::print_usb() {
    // Program
       std::cout << "USB Device Lister." << std::endl;

       // Get Number Of Devices
       UINT nDevices = 0;
       GetRawInputDeviceList(NULL, &nDevices, sizeof(RAWINPUTDEVICELIST));

       // Got Any?
       if (nDevices < 1)
       {
           // Exit
           std::cout << "ERR: 0 Devices?";
           //cin.get();
           return;
       }

       // Allocate Memory For Device List
       PRAWINPUTDEVICELIST pRawInputDeviceList;
       pRawInputDeviceList = new RAWINPUTDEVICELIST[sizeof(RAWINPUTDEVICELIST) * nDevices];

       // Got Memory?
       if (pRawInputDeviceList == NULL)
       {
           // Error
           std::cout << "ERR: Could not allocate memory for Device List.";
           return;
       }

       // Fill Device List Buffer
       int nResult;
       nResult = GetRawInputDeviceList(pRawInputDeviceList, &nDevices, sizeof(RAWINPUTDEVICELIST));

       // Got Device List?
       if (nResult < 0)
       {
           // Clean Up
           delete[] pRawInputDeviceList;

           // Error
           std::cout << "ERR: Could not get device list.";
           //cin.get();
           return;
       }

       // Loop Through Device List
       for (UINT i = 0; i < nDevices; i++)
       {
           // Get Character Count For Device Name
           UINT nBufferSize = 0;
           nResult = GetRawInputDeviceInfo(pRawInputDeviceList[i].hDevice, // Device
               RIDI_DEVICENAME,                // Get Device Name
               NULL,                           // NO Buff, Want Count!
               &nBufferSize);                 // Char Count Here!

                                              // Got Device Name?
           if (nResult < 0)
           {
               // Error
               std::cout << "ERR: Unable to get Device Name character count.. Moving to next device." << std::endl << std::endl;

               // Next
               continue;
           }

           // Allocate Memory For Device Name
           WCHAR* wcDeviceName = new WCHAR[nBufferSize + 1];

           // Got Memory
           if (wcDeviceName == NULL)
           {
               // Error
               std::cout << "ERR: Unable to allocate memory for Device Name.. Moving to next device." << std::endl << std::endl;

               // Next
               continue;
           }

           // Get Name
           nResult = GetRawInputDeviceInfo(pRawInputDeviceList[i].hDevice, // Device
               RIDI_DEVICENAME,                // Get Device Name
               wcDeviceName,                   // Get Name!
               &nBufferSize);                 // Char Count

                                              // Got Device Name?
           if (nResult < 0)
           {
               // Error
               std::cout << "ERR: Unable to get Device Name.. Moving to next device." << std::endl << std::endl;

               // Clean Up
               delete[] wcDeviceName;

               // Next
               continue;
           }

           // Set Device Info & Buffer Size
           RID_DEVICE_INFO rdiDeviceInfo;
           rdiDeviceInfo.cbSize = sizeof(RID_DEVICE_INFO);
           nBufferSize = rdiDeviceInfo.cbSize;

           // Get Device Info
           nResult = GetRawInputDeviceInfo(pRawInputDeviceList[i].hDevice,
               RIDI_DEVICEINFO,
               &rdiDeviceInfo,
               &nBufferSize);

           // Got All Buffer?
           if (nResult < 0)
           {
               // Error
               std::cout << "ERR: Unable to read Device Info.. Moving to next device." << std::endl << std::endl;

               // Next
               continue;
           }

           // Mouse
           if (rdiDeviceInfo.dwType == RIM_TYPEMOUSE)
           {
               // Current Device
               std::cout << std::endl << "Displaying device " << i + 1 << " information. (MOUSE)" << std::endl;
               std::wcout << L"Device Name: " << wcDeviceName << std::endl;
               std::cout << "Mouse ID: " << rdiDeviceInfo.mouse.dwId << std::endl;
               std::cout << "Mouse buttons: " << rdiDeviceInfo.mouse.dwNumberOfButtons << std::endl;
               std::cout << "Mouse sample rate (Data Points): " << rdiDeviceInfo.mouse.dwSampleRate << std::endl;
               if (rdiDeviceInfo.mouse.fHasHorizontalWheel)
               {
                   std::cout << "Mouse has horizontal wheel" << std::endl;
               }
               else
               {
                   std::cout << "Mouse does not have horizontal wheel" << std::endl;
               }
           }

           // Keyboard
           else if (rdiDeviceInfo.dwType == RIM_TYPEKEYBOARD)
           {
               // Current Device
               std::cout << std::endl << "Displaying device " << i + 1 << " information. (KEYBOARD)" << std::endl;
               std::wcout << L"Device Name: " << wcDeviceName << std::endl;
               std::cout << "Keyboard mode: " << rdiDeviceInfo.keyboard.dwKeyboardMode << std::endl;
               std::cout << "Number of function keys: " << rdiDeviceInfo.keyboard.dwNumberOfFunctionKeys << std::endl;
               std::cout << "Number of indicators: " << rdiDeviceInfo.keyboard.dwNumberOfIndicators << std::endl;
               std::cout << "Number of keys total: " << rdiDeviceInfo.keyboard.dwNumberOfKeysTotal << std::endl;
               std::cout << "Type of the keyboard: " << rdiDeviceInfo.keyboard.dwType << std::endl;
               std::cout << "Subtype of the keyboard: " << rdiDeviceInfo.keyboard.dwSubType << std::endl;
           }

           // Some HID
           else // (rdi.dwType == RIM_TYPEHID)
           {
               // Current Device
               std::cout << std::endl << "Displaying device " << i + 1 << " information. (HID)" << std::endl;
               std::wcout << L"Device Name: " << wcDeviceName << std::endl;
               std::cout << "Vendor Id:" << rdiDeviceInfo.hid.dwVendorId << std::endl;
               std::cout << "Product Id:" << rdiDeviceInfo.hid.dwProductId << std::endl;
               std::cout << "Version No:" << rdiDeviceInfo.hid.dwVersionNumber << std::endl;
               std::cout << "Usage for the device: " << rdiDeviceInfo.hid.usUsage << std::endl;
               std::cout << "Usage Page for the device: " << rdiDeviceInfo.hid.usUsagePage << std::endl;
           }

           // Delete Name Memory!
           delete[] wcDeviceName;
       }

       // Clean Up - Free Memory
       delete[] pRawInputDeviceList;

       // Exit
       std::cout << std::endl << "Finished." << std::endl;
}*/
//---------------------------------------------------------------------
