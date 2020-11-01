#---------------------------------------------------
#Xclu - built-in modules
#---------------------------------------------------

SOURCES += \
    $$PWD/builtin_modules/Communication/Serial/xmoduleserial.cpp \
    $$PWD/builtin_modules/Core/Random/xmodulerandom.cpp \
    $$PWD/builtin_modules/Core/Scalar/xmodulescalar.cpp \
    $$PWD/builtin_modules/Drawing/Fbo/xmodulefbo.cpp \
    $$PWD/builtin_modules/Drawing/FragmentShader/xmodulefragmentshader.cpp \
    $$PWD/builtin_modules/ImageSources/ImageLoader/xmoduleimageloader.cpp \
    $$PWD/builtin_modules/ImageSources/Webcamera/xmodulewebcamera.cpp \
    $$PWD/builtin_modules/Project/Project/xmoduleproject.cpp \
    $$PWD/builtin_modules/Sound/SoundOsc/xmodulesoundosc.cpp \
    $$PWD/builtin_modules/Sound/SoundOut/xmodulesoundout.cpp \
    $$PWD/builtin_modules/Sound/SynthFromImage/xmodulesynthfromimage.cpp \
    $$PWD/builtin_modules/System/Sleep/xmodulesleep.cpp \
    $$PWD/builtin_modules/System/Execute/xmoduleexecute.cpp \
    $$PWD/builtin_modules/System/PrintConsole/xmoduleprintconsole.cpp \
    $$PWD/builtin_modules/System/ScanFolder/xmodulescanfolder.cpp \
    $$PWD/builtin_modules/Utils/Test/xmoduletest.cpp \
    $$PWD/builtin_modules/Utils/TestDrawing/xmoduletestdrawing.cpp \
    $$PWD/builtin_modules/Window/WImage/xmodulewimage.cpp \
    $$PWD/builtin_modules/Window/Window/xmodulewindow.cpp

HEADERS += \
    $$PWD/builtin_modules/Communication/Serial/auto.h \
    $$PWD/builtin_modules/Communication/Serial/xmoduleserial.h \
    $$PWD/builtin_modules/Core/Random/auto.h \
    $$PWD/builtin_modules/Core/Random/xmodulerandom.h \
    $$PWD/builtin_modules/Core/Scalar/auto.h \
    $$PWD/builtin_modules/Core/Scalar/xmodulescalar.h \
    $$PWD/builtin_modules/Drawing/Fbo/auto.h \
    $$PWD/builtin_modules/Drawing/Fbo/xmodulefbo.h \
    $$PWD/builtin_modules/Drawing/FragmentShader/auto.h \
    $$PWD/builtin_modules/Drawing/FragmentShader/xmodulefragmentshader.h \
    $$PWD/builtin_modules/ImageSources/ImageLoader/xmoduleimageloader.h \
    $$PWD/builtin_modules/ImageSources/Webcamera/auto.h \
    $$PWD/builtin_modules/ImageSources/Webcamera/xmodulewebcamera.h \
    $$PWD/builtin_modules/Project/Project/auto.h \
    $$PWD/builtin_modules/Project/Project/xmoduleproject.h \
    $$PWD/builtin_modules/Sound/SoundOsc/auto.h \
    $$PWD/builtin_modules/Sound/SoundOsc/xmodulesoundosc.h \
    $$PWD/builtin_modules/Sound/SoundOut/auto.h \
    $$PWD/builtin_modules/Sound/SoundOut/xmodulesoundout.h \
    $$PWD/builtin_modules/Sound/SynthFromImage/auto.h \
    $$PWD/builtin_modules/Sound/SynthFromImage/xmodulesynthfromimage.h \
    $$PWD/builtin_modules/System/Sleep/xmodulesleep.h \
    $$PWD/builtin_modules/System/Execute/auto.h \
    $$PWD/builtin_modules/System/Execute/xmoduleexecute.h \
    $$PWD/builtin_modules/System/PrintConsole/auto.h \
    $$PWD/builtin_modules/System/PrintConsole/xmoduleprintconsole.h \
    $$PWD/builtin_modules/System/ScanFolder/auto.h \
    $$PWD/builtin_modules/System/ScanFolder/xmodulescanfolder.h \
    $$PWD/builtin_modules/Utils/Test/auto.h \
    $$PWD/builtin_modules/Utils/Test/xmoduletest.h \
    $$PWD/builtin_modules/Utils/TestDrawing/xmoduletestdrawing.h \
    $$PWD/builtin_modules/Window/WImage/auto.h \
    $$PWD/builtin_modules/Window/WImage/xmodulewimage.h \
    $$PWD/builtin_modules/Window/Window/auto.h \
    $$PWD/builtin_modules/Window/Window/xmodulewindow.h

#--------------------------------------------------------------------------
#Realsense camera support
#Comment this block if Realsense camera is not required
#--------------------------------------------------------------------------
unix {
    INCLUDEPATH += ~/librealsense/include
    LIBS += -lrealsense2
}

#windows 32 bit
#windows {
#    INCLUDEPATH += "C:/Program Files (x86)/Intel RealSense SDK 2.0/include"
#    LIBS += "C:\Program Files (x86)\Intel RealSense SDK 2.0\lib\x86\realsense2.lib"
#}

#windows 64 bit
windows {
    INCLUDEPATH += "C:/Program Files (x86)/Intel RealSense SDK 2.0/include"
    LIBS += "C:\Program Files (x86)\Intel RealSense SDK 2.0\lib\x64\realsense2.lib"
}

SOURCES +=    \
    $$PWD/builtin_modules/ImageSources/RealsenseCamera/xmodulerealsensecamera.cpp \
    $$PWD/builtin_modules/ImageSources/RealsenseCamera/xmodulerealsensecamera_impl.cpp

HEADERS +=    \
    $$PWD/builtin_modules/ImageSources/RealsenseCamera/xmodulerealsensecamera.h \
    $$PWD/builtin_modules/ImageSources/RealsenseCamera/xmodulerealsensecamera_impl.h


#--------------------------------------------------------------------------
