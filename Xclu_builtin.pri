#---------------------------------------------------
#Xclu - built-in modules
#---------------------------------------------------

SOURCES += \
    $$PWD/builtin_modules/Communication/BciNeuroplay/neuroplaypro.cpp \
    $$PWD/builtin_modules/Communication/BciNeuroplay/neuroplayprodevice.cpp \
    $$PWD/builtin_modules/Communication/BciNeuroplay/xmodulebcineuroplay.cpp \
    $$PWD/builtin_modules/Bots/TelegramBot/xmoduletelegrambot.cpp \
    $$PWD/builtin_modules/Communication/Serial/xmoduleserial.cpp \
    $$PWD/builtin_modules/Contrib/MadRobot/xmodulemadrobot.cpp \
    $$PWD/builtin_modules/Core/Random/xmodulerandom.cpp \
    $$PWD/builtin_modules/Core/Scalar/xmodulescalar.cpp \
    $$PWD/builtin_modules/Core/ValueMap/xmodulevaluemap.cpp \
    $$PWD/builtin_modules/Drawing/Fbo/xmodulefbo.cpp \
    $$PWD/builtin_modules/Drawing/FragmentShader/xmodulefragmentshader.cpp \
    $$PWD/builtin_modules/ImageSources/ImageLoader/xmoduleimageloader.cpp \
    $$PWD/builtin_modules/ImageSources/Webcamera/xmodulewebcamera.cpp \
    $$PWD/builtin_modules/Interactive/MotionDetector/xmodulemotiondetector.cpp \
    $$PWD/builtin_modules/Interactive/MotionDetectorRouter/xmodulemotiondetectorrouter.cpp \
    $$PWD/builtin_modules/ML/MLExecute/xmodulemlexecute.cpp \
    $$PWD/builtin_modules/Project/Project/xmoduleproject.cpp \
    $$PWD/builtin_modules/Sound/SoundIn/xmodulesoundin.cpp \
    $$PWD/builtin_modules/Sound/SoundOsc/xmodulesoundosc.cpp \
    $$PWD/builtin_modules/Sound/SoundOut/xmodulesoundout.cpp \
    $$PWD/builtin_modules/Sound/SoundPlay/xmodulesoundplay.cpp \
    $$PWD/builtin_modules/Sound/SoundsDatabaseAnalyze/soundsamplesanalyze.cpp \
    $$PWD/builtin_modules/Sound/SoundsDatabaseAnalyze/soundsamplesdatabase.cpp \
    $$PWD/builtin_modules/Sound/SoundsDatabaseAnalyze/xmodulessoundsdatabaseanalyze.cpp \
    $$PWD/builtin_modules/Sound/SoundsSeaOfWords/xmodulessoundseaofwords.cpp \
    $$PWD/builtin_modules/Sound/SynthFromImage/xmodulesynthfromimage.cpp \
    $$PWD/builtin_modules/System/FileCreate/xmodulefilecreate.cpp \
    $$PWD/builtin_modules/System/Timer/xmoduletimer.cpp \
    $$PWD/builtin_modules/System/Execute/xmoduleexecute.cpp \
    $$PWD/builtin_modules/System/PrintConsole/xmoduleprintconsole.cpp \
    $$PWD/builtin_modules/System/ScanFolder/xmodulescanfolder.cpp \
    $$PWD/builtin_modules/Text/TextVariation/xmoduletextvariation.cpp \
    $$PWD/builtin_modules/Utils/Test/xmoduletest.cpp \
    $$PWD/builtin_modules/Utils/TestDrawing/xmoduletestdrawing.cpp \
    $$PWD/builtin_modules/Window/WImage/xmodulewimage.cpp \
    $$PWD/builtin_modules/Window/Window/xmodulewindow.cpp \
    $$PWD/builtin_modules/Window/RenderArea/xmodulerenderarea.cpp \
    $$PWD/builtin_modules/Project/Notes/xmodulenotes.cpp \
    $$PWD/builtin_modules/Window/RenderElement/xmodulerenderelement.cpp \
    $$PWD/builtin_modules/ComputerVision/FaceDetect/xmodulefacedetect.cpp

HEADERS += \
    $$PWD/builtin_modules/Bots/TelegramBot/auto.h \
    $$PWD/builtin_modules/Bots/TelegramBot/xmoduletelegrambot.h \
    $$PWD/builtin_modules/Communication/BciNeuroplay/auto.h \
    $$PWD/builtin_modules/Communication/BciNeuroplay/neuroplaypro.h \
    $$PWD/builtin_modules/Communication/BciNeuroplay/neuroplayprodevice.h \
    $$PWD/builtin_modules/Communication/BciNeuroplay/xmodulebcineuroplay.h \
    $$PWD/builtin_modules/Communication/Serial/auto.h \
    $$PWD/builtin_modules/Communication/Serial/xmoduleserial.h \
    $$PWD/builtin_modules/Contrib/MadRobot/auto.h \
    $$PWD/builtin_modules/Contrib/MadRobot/xmodulemadrobot.h \
    $$PWD/builtin_modules/Core/Random/auto.h \
    $$PWD/builtin_modules/Core/Random/xmodulerandom.h \
    $$PWD/builtin_modules/Core/Scalar/auto.h \
    $$PWD/builtin_modules/Core/Scalar/xmodulescalar.h \
    $$PWD/builtin_modules/Core/ValueMap/auto.h \
    $$PWD/builtin_modules/Core/ValueMap/xmodulevaluemap.h \
    $$PWD/builtin_modules/Drawing/Fbo/auto.h \
    $$PWD/builtin_modules/Drawing/Fbo/xmodulefbo.h \
    $$PWD/builtin_modules/Drawing/FragmentShader/auto.h \
    $$PWD/builtin_modules/Drawing/FragmentShader/xmodulefragmentshader.h \
    $$PWD/builtin_modules/ImageSources/ImageLoader/xmoduleimageloader.h \
    $$PWD/builtin_modules/ImageSources/Webcamera/auto.h \
    $$PWD/builtin_modules/ImageSources/Webcamera/xmodulewebcamera.h \
    $$PWD/builtin_modules/Interactive/MotionDetector/auto.h \
    $$PWD/builtin_modules/Interactive/MotionDetector/xmodulemotiondetector.h \
    $$PWD/builtin_modules/Interactive/MotionDetectorRouter/auto.h \
    $$PWD/builtin_modules/Interactive/MotionDetectorRouter/xmodulemotiondetectorrouter.h \
    $$PWD/builtin_modules/ML/MLExecute/auto.h \
    $$PWD/builtin_modules/ML/MLExecute/xmodulemlexecute.h \
    $$PWD/builtin_modules/Project/Project/auto.h \
    $$PWD/builtin_modules/Project/Project/xmoduleproject.h \
    $$PWD/builtin_modules/Sound/SoundIn/auto.h \
    $$PWD/builtin_modules/Sound/SoundIn/xmodulesoundin.h \
    $$PWD/builtin_modules/Sound/SoundOsc/auto.h \
    $$PWD/builtin_modules/Sound/SoundOsc/xmodulesoundosc.h \
    $$PWD/builtin_modules/Sound/SoundOut/auto.h \
    $$PWD/builtin_modules/Sound/SoundOut/xmodulesoundout.h \
    $$PWD/builtin_modules/Sound/SoundPlay/auto.h \
    $$PWD/builtin_modules/Sound/SoundPlay/xmodulesoundplay.h \
    $$PWD/builtin_modules/Sound/SoundsDatabaseAnalyze/auto.h \
    $$PWD/builtin_modules/Sound/SoundsDatabaseAnalyze/soundsamplesanalyze.h \
    $$PWD/builtin_modules/Sound/SoundsDatabaseAnalyze/soundsamplesdatabase.h \
    $$PWD/builtin_modules/Sound/SoundsDatabaseAnalyze/xmodulessoundsdatabaseanalyze.h \
    $$PWD/builtin_modules/Sound/SoundsSeaOfWords/auto.h \
    $$PWD/builtin_modules/Sound/SoundsSeaOfWords/xmodulessoundseaofwords.h \
    $$PWD/builtin_modules/Sound/SynthFromImage/auto.h \
    $$PWD/builtin_modules/Sound/SynthFromImage/xmodulesynthfromimage.h \
    $$PWD/builtin_modules/System/FileCreate/auto.h \
    $$PWD/builtin_modules/System/FileCreate/xmodulefilecreate.h \
    $$PWD/builtin_modules/System/Timer/xmoduletimer.h \
    $$PWD/builtin_modules/System/Execute/auto.h \
    $$PWD/builtin_modules/System/Execute/xmoduleexecute.h \
    $$PWD/builtin_modules/System/PrintConsole/auto.h \
    $$PWD/builtin_modules/System/PrintConsole/xmoduleprintconsole.h \
    $$PWD/builtin_modules/System/ScanFolder/auto.h \
    $$PWD/builtin_modules/System/ScanFolder/xmodulescanfolder.h \
    $$PWD/builtin_modules/Text/TextVariation/xmoduletextvariation.h \
    $$PWD/builtin_modules/Utils/Test/auto.h \
    $$PWD/builtin_modules/Utils/Test/xmoduletest.h \
    $$PWD/builtin_modules/Utils/TestDrawing/xmoduletestdrawing.h \
    $$PWD/builtin_modules/Window/WImage/auto.h \
    $$PWD/builtin_modules/Window/WImage/xmodulewimage.h \
    $$PWD/builtin_modules/Window/Window/auto.h \
    $$PWD/builtin_modules/Window/Window/xmodulewindow.h \
    $$PWD/builtin_modules/Window/RenderArea/auto.h \
    $$PWD/builtin_modules/Window/RenderArea/xmodulerenderarea.h \
    $$PWD/builtin_modules/Project/Notes/auto.h \
    $$PWD/builtin_modules/Project/Notes/xmodulenotes.h \
    $$PWD/builtin_modules/Window/RenderElement/auto.h \
    $$PWD/builtin_modules/Window/RenderElement/xmodulerenderelement.h \
    $$PWD/builtin_modules/ComputerVision/FaceDetect/auto.h \
    $$PWD/builtin_modules/ComputerVision/FaceDetect/xmodulefacedetect.h


#--------------------------------------------------------------------------
# OpenCV 3.1
#--------------------------------------------------------------------------
# windows 64 bit
windows {
    INCLUDEPATH += \
        libs/opencv \
        libs/opencv/include \
        libs/opencv/include/opencv \
        libs/opencv/include/opencv2 \
        libs/opencv/include/opencv2/calib3d \
        libs/opencv/include/opencv2/core \
        libs/opencv/include/opencv2/core/cuda \
        libs/opencv/include/opencv2/core/cuda/detail \
        libs/opencv/include/opencv2/core/hal \
        libs/opencv/include/opencv2/core/opencl \
        libs/opencv/include/opencv2/core/opencl/runtime \
        libs/opencv/include/opencv2/features2d \
        libs/opencv/include/opencv2/flann \
        libs/opencv/include/opencv2/highgui \
        libs/opencv/include/opencv2/imgcodecs \
        libs/opencv/include/opencv2/imgproc \
        libs/opencv/include/opencv2/imgproc/detail \
        libs/opencv/include/opencv2/ml \
        libs/opencv/include/opencv2/objdetect \
        libs/opencv/include/opencv2/photo \
        libs/opencv/include/opencv2/shape \
        libs/opencv/include/opencv2/stitching \
        libs/opencv/include/opencv2/stitching/detail \
        libs/opencv/include/opencv2/superres \
        libs/opencv/include/opencv2/ts \
        libs/opencv/include/opencv2/video \
        libs/opencv/include/opencv2/videoio \
        libs/opencv/include/opencv2/videostab \
		libs/ippicv/include

    CONFIG(release) {
        LIBS += -l$$PWD/libs/opencv/lib/opencv_world310
    }
    CONFIG(debug) {
        LIBS += -l$$PWD/libs/opencv/lib/opencv_world310d
    }    
        
    #CONFIG(release, debug|release) {
    #    LIBS += -L$$PWD/libs/opencv/lib/vs/x64/Release \
    #    -llibwebp -lopencv_imgproc310 -lopencv_shape310 -lopencv_superres310 -lopencv_videoio310 \
    #    -lopencv_stitching310 -lopencv_flann310 -lopencv_calib3d310 -lopencv_videostab310 \
    #    -lopencv_features2d310 -lopencv_ml310 -lopencv_core310 -lopencv_imgcodecs310 -lopencv_objdetect310 \
    #    -lopencv_photo310 -lopencv_video310 -lopencv_highgui310 \
    #    -lzlib
	#	
    #    LIBS += -l$$PWD/libs/ippicv/lib/vs/x64/ippicvmt
    #}
    #CONFIG(debug, debug|release) {
    #    LIBS += -L$$PWD/libs/opencv/lib/vs/x64/Debug \
    #    -llibwebpd -lopencv_imgproc310d -lopencv_shape310d -lopencv_superres310d -lopencv_videoio310d \
    #    -lopencv_stitching310d -lopencv_flann310d -lopencv_calib3d310d -lopencv_videostab310d \
    #    -lopencv_features2d310d -lopencv_ml310d -lopencv_core310d -lopencv_imgcodecs310d -lopencv_objdetect310d \
    #    -lopencv_photo310d -lopencv_video310d -lopencv_highgui310d \
    #    -lzlibd
	#	
    #    LIBS += -l$$PWD/libs/ippicv/lib/vs/x64/ippicvmt
    #}
}

# astra linux
unix {
    INCLUDEPATH += \
        /usr/include/opencv \
        /usr/include/opencv2 \
        /usr/include/opencv2/calib3d \
        /usr/include/opencv2/core \
        /usr/include/opencv2/core/cuda \
        /usr/include/opencv2/core/cuda/detail \
        /usr/include/opencv2/core/hal \
        /usr/include/opencv2/core/opencl \
        /usr/include/opencv2/core/opencl/runtime \
        /usr/include/opencv2/features2d \
        /usr/include/opencv2/flann \
        /usr/include/opencv2/highgui \
        /usr/include/opencv2/imgcodecs \
        /usr/include/opencv2/imgproc \
        /usr/include/opencv2/imgproc/detail \
        /usr/include/opencv2/ml \
        /usr/include/opencv2/objdetect \
        /usr/include/opencv2/photo \
        /usr/include/opencv2/shape \
        /usr/include/opencv2/stitching \
        /usr/include/opencv2/stitching/detail \
        /usr/include/opencv2/superres \
        /usr/include/opencv2/ts \
        /usr/include/opencv2/video \
        /usr/include/opencv2/videoio \
        /usr/include/opencv2/videostab \

    LIBS += \ #-L/usr/lib/x86_64-linux-gnu/ \
            /usr/lib/x86_64-linux-gnu/libopencv_core.so \
            /usr/lib/x86_64-linux-gnu/libopencv_imgproc.so \
            /usr/lib/x86_64-linux-gnu/libopencv_video.so \
            /usr/lib/x86_64-linux-gnu/libopencv_highgui.so
            #-lopencv_imgcodecs310 \
            #-lzlib

    #LIBS += -l$$PWD/libs/ippicv/lib/vs/x64/ippicvmt
}


#--------------------------------------------------------------------------
#Windows, USB enumeration for Webcamera module
#--------------------------------------------------------------------------
#windows 64 bit
#windows {
    #Not used, so commented for now:
    #LIBS += User32.lib
#}


#--------------------------------------------------------------------------
#Realsense camera support
#--------------------------------------------------------------------------
#Comment this line to exclude Realsense from build
##CONFIG += REALSENSE
#--------------------------------------------------------------------------
#REALSENSE {
#unix {
#    INCLUDEPATH += ~/librealsense/include
#    LIBS += -lrealsense2
#}
##
###windows 32 bit
###windows {
###    INCLUDEPATH += "C:/Program Files (x86)/Intel RealSense SDK 2.0/include"
###    LIBS += "C:\Program Files (x86)\Intel RealSense SDK 2.0\lib\x86\realsense2.lib"
###}
##
##windows 64 bit
#windows {
#    INCLUDEPATH += "C:/Program Files (x86)/Intel RealSense SDK 2.0/include"
#    LIBS += "C:\Program Files (x86)\Intel RealSense SDK 2.0\lib\x64\realsense2.lib"
#}
#
#SOURCES +=    \
#    $$PWD/builtin_modules/ImageSources/RealsenseCamera/xmodulerealsensecamera.cpp \
#    $$PWD/builtin_modules/ImageSources/RealsenseCamera/xmodulerealsensecamera_impl.cpp
#
#HEADERS +=    \
#    $$PWD/builtin_modules/ImageSources/RealsenseCamera/xmodulerealsensecamera.h \
#    $$PWD/builtin_modules/ImageSources/RealsenseCamera/xmodulerealsensecamera_impl.h


#--------------------------------------------------------------------------
#NDI
#--------------------------------------------------------------------------
#Comment this line to exclude NDI from build
#CONFIG += NDI - not works...
#--------------------------------------------------------------------------
#windows {
#    INCLUDEPATH += $$PWD/libs/NDI/Include
#    LIBS += $$PWD/libs/NDI/Lib/x64/Processing.NDI.Lib.x64.lib
#
#SOURCES +=    \
#    $$PWD/builtin_modules/Communication/Ndi/xmodulendi.cpp
#
#HEADERS +=    \
#    $$PWD/builtin_modules/Communication/Ndi/auto.h \
#    $$PWD/builtin_modules/Communication/Ndi/xmodulendi.h
#
#}

#--------------------------------------------------------------------------

