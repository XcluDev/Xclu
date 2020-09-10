#---------------------------------------------------
#Xclu - built-in modules
#---------------------------------------------------

SOURCES += \
    builtin_modules_impl/Screen/xmodulewimage.cpp \
    builtin_modules_impl/Screen/xmodulefbo.cpp \
    builtin_modules_impl/Screen/xmodulefragmentshader.cpp \
    builtin_modules_impl/Sound/xmodulesynthfromimage.cpp \
    builtin_modules_impl/Images/xmodulewebcamera.cpp \
    builtin_modules_impl/Sound/xmodulesoundout.cpp \
    builtin_modules_impl/System/xmoduleexecute.cpp \
    builtin_modules_impl/Utils/xmoduletest.cpp \
    builtin_modules_impl/Core/xmodulescalar.cpp \
    builtin_modules_impl/Screen/xmodulewindow.cpp \
    builtin_modules_impl/Sound/xmodulesoundosc.cpp \
    builtin_modules_impl/Communication/xmoduleserial.cpp \
    builtin_modules_impl/Project/xmoduleproject.cpp 

HEADERS += \
    builtin_modules_impl/Screen/xmodulewimage.h \
    builtin_modules_impl/Screen/xmodulefbo.h \
    builtin_modules_impl/Screen/xmodulefragmentshader.h \
    builtin_modules_impl/Sound/xmodulesynthfromimage.h \
    builtin_modules_impl/Images/xmodulewebcamera.h \
    builtin_modules_impl/Sound/xmodulesoundout.h \
    builtin_modules_impl/System/xmoduleexecute.h \
    builtin_modules_impl/Utils/xmoduletest.h \
    builtin_modules_impl/Core/xmodulescalar.h \
    builtin_modules_impl/Screen/xmodulewindow.h \
    builtin_modules_impl/Sound/xmodulesoundosc.h \
    builtin_modules_impl/Communication/xmoduleserial.h \
    builtin_modules_impl/Project/xmoduleproject.h 

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

SOURCES +=    builtin_modules_impl/Images/xmodulerealsensecamera.cpp \
    builtin_modules_impl/Images/xmodulerealsensecamera_impl.cpp

HEADERS +=    builtin_modules_impl/Images/xmodulerealsensecamera.h \
    builtin_modules_impl/Images/xmodulerealsensecamera_impl.h


#--------------------------------------------------------------------------
