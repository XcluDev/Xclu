#---------------------------------------------------
#Xclu - built-in modules
#---------------------------------------------------

SOURCES += \
    builtin_modules_impl/Screen/rtmodulewimage.cpp \
    builtin_modules_impl/Screen/rtmodulefbo.cpp \
    builtin_modules_impl/Screen/rtmodulefragmentshader.cpp \
    builtin_modules_impl/Sound/rtmodulesynthfromimage.cpp \
    builtin_modules_impl/Images/rtmodulewebcamera.cpp \
    builtin_modules_impl/Sound/rtmodulesoundout.cpp \
    builtin_modules_impl/System/rtmoduleexecute.cpp \
    builtin_modules_impl/Utils/rtmoduletest.cpp \
    builtin_modules_impl/Core/rtmodulescalar.cpp \
    builtin_modules_impl/Screen/rtmodulewindow.cpp \
    builtin_modules_impl/Sound/rtmodulesoundosc.cpp \
    builtin_modules_impl/Communication/rtmoduleserial.cpp \
    builtin_modules_impl/Project/rtmoduleproject.cpp 

HEADERS += \
    builtin_modules_impl/Screen/rtmodulewimage.h \
    builtin_modules_impl/Screen/rtmodulefbo.h \
    builtin_modules_impl/Screen/rtmodulefragmentshader.h \
    builtin_modules_impl/Sound/rtmodulesynthfromimage.h \
    builtin_modules_impl/Images/rtmodulewebcamera.h \
    builtin_modules_impl/Sound/rtmodulesoundout.h \
    builtin_modules_impl/System/rtmoduleexecute.h \
    builtin_modules_impl/Utils/rtmoduletest.h \
    builtin_modules_impl/Core/rtmodulescalar.h \
    builtin_modules_impl/Screen/rtmodulewindow.h \
    builtin_modules_impl/Sound/rtmodulesoundosc.h \
    builtin_modules_impl/Communication/rtmoduleserial.h \
    builtin_modules_impl/Project/rtmoduleproject.h 

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

SOURCES +=    builtin_modules_impl/Images/rtmodulerealsensecamera.cpp \
    builtin_modules_impl/Images/rtmodulerealsensecamera_impl.cpp

HEADERS +=    builtin_modules_impl/Images/rtmodulerealsensecamera.h \
    builtin_modules_impl/Images/rtmodulerealsensecamera_impl.h


#--------------------------------------------------------------------------
