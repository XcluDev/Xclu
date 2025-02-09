#---------------------------------------------------
#Xclu
#---------------------------------------------------
#Про режим сборки Release-Deploy
#Это режим сборки для публикации программы.
#При нем для интерфейса модулей будет использоваться xclu.qrc
#и поэтому требуется добавить все в xclu.qrc
#ф в остальных режимах - это путь на диске, чтобы можно было оперативно
#менять структуру папко модулей и все бы работало
#
#При сборке "с нуля" - нужно создать этот режим, нажав слева "Проекты",
#Скопировать из Release,
#и добавить в строку вызова qmake: DEFINES+=XCLU_DEPLOY
#ВАЖНО: Установить каталог сборки D:\perevalovds.com\_2020\Xclu\temp-build
#тогда все промежуточные файлы будут в папке temp-build, а результат в Xclu-bin

# Qt:
#    5.9.5:  https://download.qt.io/archive/qt/5.9/5.9.5/
#    5.14.2: https://download.qt.io/archive/qt/5.14/5.14.2/

# Notes: 
# - On "old" Qt 5.9 please call "Run qmake" after adding or renaming files.
#    Also sometimes it's required to delete Build folders and recompile the project.
# - SSL on Windows:
#    If you get "QSslSocket::connectToHostEncrypted: TLS initialization failed" error,
#    please enable "OpenSSL" at Qt installer at Developer Tools section, 
#    and copy libcrypto-1_1-x64.dll, libssl-1_1-x64.dll to Xclu bin folder
#    https://ru.stackoverflow.com/questions/952577/qt-network-ssl-qsslsocketconnecttohostencrypted-tls-initialization-failed
# - Collect plugins on Windows:
#    D:\Qt\Qt5_14\5.14.2\msvc2017_64\bin\windeployqt.exe --release ./
#    (set path to your Qt here)

#--------------------------------------------------------------------------
#General app settings
#--------------------------------------------------------------------------

#Uncomment for deploying mode, that is all modules definitions will be put inside EXE
DEFINES+=XCLU_DEPLOY



Release:TARGET=Xclu
Release:DESTDIR = ../Xclu-bin
Release:OBJECTS_DIR = release/.obj
Release:MOC_DIR = release/.moc
Release:RCC_DIR = release/.rcc
Release:UI_DIR = release/.ui

Debug:TARGET=Xclu_debug
Debug:DESTDIR = ../Xclu-bin
Debug:OBJECTS_DIR = debug/.obj
Debug:MOC_DIR = debug/.moc
Debug:RCC_DIR = debug/.rcc
Debug:UI_DIR = debug/.ui

# Default rules for deployment.
#qnx: target.path = /tmp/$${TARGET}/bin
#else: unix:!android: target.path = /opt/$${TARGET}/bin
#!isEmpty(target.path): INSTALLS += target

#TODO enable all exceptions handling in VisualStudio, including division by zero:
#Project Properties -> C/C++ -> Code Generation -> Modify the Enable C++ Exceptions to "Yes With SEH Exceptions". 

QT += core gui
QT += multimedia multimediawidgets
QT += serialport network websockets
QT += 3dcore 3drender 3dinput 3dextras
QT += qml
QT += core-private

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

RESOURCES += \
    xclu.qrc

# Про иконки: https://doc.qt.io/qt-5/appicon.html
RC_ICONS = builtin_resources/images/appicon.ico

#define to know which OS
windows {
    DEFINES += XCLU_WINDOWS
}
unix {
    DEFINES += XCLU_LINUX
}


#--------------------------------------------------------------------------
#Compiler optimizations
#--------------------------------------------------------------------------
#https://stackoverflow.com/questions/409300/how-to-vectorize-with-gcc
unix {
    QMAKE_CFLAGS += -O3 -ftree-vectorize -msse2 -mfpmath=sse -ftree-vectorizer-verbose=5
    QMAKE_CXXFLAGS += -O3 -ftree-vectorize -msse2 -mfpmath=sse -ftree-vectorizer-verbose=5

    # Флаги для компиляции для архитектуры текущего процессора:
    # QMAKE_CFLAGS += -march=native
    # QMAKE_CXXFLAGS += -march=native

    # Support OpenMP - comment it if not required to use many threads
    # QMAKE_CFLAGS += -fopenmp
    # QMAKE_CXXFLAGS += -fopenmp
    # LIBS += /usr/lib/x86_64-linux-gnu/libgomp.so.1
}


#--------------------------------------------------------------------------
#Paths
#--------------------------------------------------------------------------
# Components
INCLUDEPATH += \
    components \
    components/gui \
    components/hosting \
    components/button \
    components/checkbox \
    components/enum \
    components/float \
    components/group \
    components/int \
    components/object \
    components/page \
    components/raster \
    components/separator \
    components/string \
    components/text

# Xclu host
INCLUDEPATH += project \
               modules

INCLUDEPATH += host \
               host/dialogs

# SDK
INCLUDEPATH += sdk \
               sdk/audio \
               sdk/cv \
               sdk/draw \
               sdk/geom \
               sdk/math \
               sdk/ml \
               sdk/networking \
               sdk/types \
               sdk/types/xobjectvis \
               sdk/utility

# Compute shaders
# TODO Jetson Nano gives compiling errors with compute shaders - resolve
windows {
    INCLUDEPATH += sdk/compshaders
    SOURCES += sdk/compshaders/xcomputeshader.cpp
    HEADERS += sdk/compshaders/xcomputeshader.h
}

# Libs
INCLUDEPATH += libs/glm libs/glm/gtx
INCLUDEPATH += libs/of
INCLUDEPATH += libs/tsne
INCLUDEPATH += libs/QOsc/qosc/src libs/QOsc/qosc/include


#--------------------------------------------------------------------------
#Common source, headers and forms files
#--------------------------------------------------------------------------
FORMS += \
    host/dialogs/dialogeditlink.ui \
    host/dialogs/dialogeditlinks.ui \
    host/dialogs/dialogeditui.ui \
    host/dialogs/dialogmodulename.ui \
    host/mainwindow.ui



SOURCES += \
    components/button/xguibutton.cpp \
    components/button/xitembutton.cpp \
    components/checkbox/xguicheckbox.cpp \
    components/checkbox/xitemcheckbox.cpp \
    components/componentcontextmenu.cpp \
    components/enum/xguienum.cpp \
    components/enum/xitemenum.cpp \
    components/float/xguifloat.cpp \
    components/float/xitemfloat.cpp \
    components/gui/xcluclickablelabel.cpp \
    components/int/xguiint.cpp \
    components/int/xitemint.cpp \
    components/object/xguiobject.cpp \
    components/object/xitemobject.cpp \
    components/page/xguipage.cpp \
    components/page/xitempage.cpp \
    components/registrarxitem.cpp \
    components/separator/xguiseparator.cpp \
    components/separator/xitemseparator.cpp \
    components/string/xguistring.cpp \
    components/string/xitemstring.cpp \
    components/text/xguitext.cpp \
    components/text/xitemtext.cpp \
    components/visibilitygroups.cpp \
    components/xguicomp.cpp \
    components/xguieditor.cpp \
    components/xitem.cpp \
    components/xitemscalar.cpp \
    host/dialogs/dialogeditlink.cpp \
    host/dialogs/dialogeditlinks.cpp \
    host/dialogs/dialogeditui.cpp \
    host/mainwindow.cpp \
    host/recentfiles.cpp \
    host/xc_paths.cpp \
    host/xclu_settings.cpp \
    host/xclu_theme.cpp \
    host/xclu_types.cpp \
    libs/QOsc/qosc/src/qosc_global.cpp \
    libs/QOsc/qosc/src/qoscbundle.cpp \
    libs/QOsc/qosc/src/qoscinterface.cpp \
    libs/QOsc/qosc/src/qoscmessage.cpp \
    libs/QOsc/qosc/src/qoscmethod.cpp \
    libs/QOsc/qosc/src/qoscvalue.cpp \
    libs/tsne/sptree.cpp \
    libs/tsne/tsne.cpp \
    modules/exportinterface.cpp \
    modules/registrarxclass.cpp \
    modules/xclass.cpp \
    modules/xclassbase.cpp \
    modules/xclassvisualwidget.cpp \
    modules/xclasswidget.cpp \
    modules/xmodule.cpp \
    modules/xmoduledescription.cpp \
    modules/xmoduleinterface.cpp \
    modules/xmoduleprototype.cpp \
    modules/xmodulesfactory.cpp \
    sdk/audio/xc_audio.cpp \
    sdk/audio/xc_audio_wavfile.cpp \
    sdk/cv/xcvhelper.cpp \
    sdk/draw/xdrawhelper.cpp \
    sdk/geom/XGeomExportVectorField.cpp \
    sdk/geom/XGeomMath.cpp \
    sdk/geom/XGeomMesh.cpp \
    sdk/geom/XGeomMeshUtils.cpp \
    sdk/math/xmath.cpp \
    sdk/math/xnoise.cpp \
    sdk/math/xslowbit.cpp \
    sdk/math/xtimebuffer.cpp \
    sdk/ml/xc_tsne.cpp \
    sdk/networking/xnetworkaddr.cpp \
    sdk/networking/xosc.cpp \
    sdk/types/xarray.cpp \
    sdk/types/xbasictypes.cpp \
    sdk/types/xcall.cpp \
    sdk/types/xcallerror.cpp \
    sdk/types/xcalltype.cpp \
    sdk/types/xlink.cpp \
    sdk/types/xobject.cpp \
    sdk/types/xobjectvis/xobjectvis.cpp \
    sdk/types/xobjectvis/xobjectvisimage.cpp \
    sdk/types/xobjectvis/xobjectvissoundbuffer.cpp \
    sdk/types/xobjectvis/xobjectvissoundformat.cpp \
    sdk/types/xpointer.cpp \
    sdk/types/xprotecteddata.cpp \
    sdk/types/xrange.cpp \
    sdk/types/xraster.cpp \
    sdk/types/xsoundtypes.cpp \
    sdk/types/xtype.cpp \
    sdk/types/xtypeconvertor.cpp \
    sdk/types/xtypes.cpp \
    sdk/types/xwaschanged.cpp \
    sdk/utility/jsonutils.cpp \
    sdk/utility/xexecbatch.cpp \
    sdk/utility/xfiles.cpp \
    sdk/utility/xhandlingerrors.cpp \
    sdk/utility/ximageeffect.cpp \
    sdk/utility/xmoduleutils.cpp \
    sdk/utility/xparse_tree.cpp \
    sdk/utility/xparser.cpp \
    sdk/utility/xrasterutils.cpp \
    sdk/utility/xsysutils.cpp \
    sdk/utility/xtimemeasure.cpp \
    components/gui/xclucombobox.cpp \
    components/gui/xcludoublespinbox.cpp \
    components/gui/xcluscrollarea.cpp \
    components/gui/xcluspinbox.cpp \
    main.cpp \
    host/consoleview.cpp \
    host/dialogs/dialogmodulename.cpp \
    host/dialogs/dialogrenamemodule.cpp \
    host/dialogs/dialogtestmoduleinterface.cpp \
    host/editormodules.cpp \
    host/dialogs/dialogaddmodule.cpp \
    host/projectgui.cpp \
    python/pythoncore.cpp \
    project/project_props.cpp \
    project/project.cpp \
    project/projecteditorprops.cpp \
    sdk/utility/xtypeutils.cpp \
    sdk/utility/xutils.cpp

HEADERS += \
    components/button/xguibutton.h \
    components/button/xitembutton.h \
    components/checkbox/xguicheckbox.h \
    components/checkbox/xitemcheckbox.h \
    components/componentcontextmenu.h \
    components/enum/xguienum.h \
    components/enum/xitemenum.h \
    components/float/xguifloat.h \
    components/float/xitemfloat.h \
    components/gui/xcluclickablelabel.h \
    components/int/xguiint.h \
    components/int/xitemint.h \
    components/object/xguiobject.h \
    components/object/xitemobject.h \
    components/page/xguipage.h \
    components/page/xitempage.h \
    components/registrarxitem.h \
    components/separator/xguiseparator.h \
    components/separator/xitemseparator.h \
    components/string/xguistring.h \
    components/string/xitemstring.h \
    components/text/xguitext.h \
    components/text/xitemtext.h \
    components/visibilitygroups.h \
    components/xguicomp.h \
    components/xguieditor.h \
    components/xitem.h \
    components/xitemscalar.h \
    host/dialogs/dialogeditlink.h \
    host/dialogs/dialogeditlinks.h \
    host/dialogs/dialogeditui.h \
    host/mainwindow.h \
    host/recentfiles.h \
    host/xc_paths.h \
    host/xclu_settings.h \
    host/xclu_theme.h \
    host/xclu_types.h \
    libs/QOsc/qosc/include/qosc.h \
    libs/QOsc/qosc/include/qosc_global.h \
    libs/QOsc/qosc/include/qoscbundle.h \
    libs/QOsc/qosc/include/qoscinterface.h \
    libs/QOsc/qosc/include/qoscmessage.h \
    libs/QOsc/qosc/include/qoscmethod.h \
    libs/QOsc/qosc/include/qoscvalue.h \
    libs/QOsc/qosc/src/qoscbundle_p.h \
    libs/QOsc/qosc/src/qoscmessage_p.h \
    libs/QOsc/qosc/src/qoscvalue_p.h \
    libs/of/ofNoise.h \
    libs/tsne/sptree.h \
    libs/tsne/tsne.h \
    libs/tsne/vptree.h \
    modules/registrarxclass.h \
    modules/xclass.h \
    modules/xclassbase.h \
    modules/xclassvisualwidget.h \
    modules/xclasswidget.h \
    modules/xmodule.h \
    modules/xmoduledescription.h \
    modules/xmoduleinterface.h \
    modules/xmoduleprototype.h \
    modules/xmodulesfactory.h \
    sdk/audio/xc_audio.h \
    sdk/audio/xc_audio_wavfile.h \
    sdk/cv/xcvhelper.h \
    sdk/draw/xdrawhelper.h \
    sdk/geom/XGeomExportVectorField.h \
    sdk/geom/XGeomMath.h \
    sdk/geom/XGeomMesh.h \
    sdk/geom/XGeomMeshUtils.h \
    sdk/incl_cpp.h \
    sdk/incl_h.h \
    sdk/math/int2.h \
    modules/exportinterface.h \
    sdk/math/xmath.h \
    sdk/math/xmath_glm.h \
    sdk/math/xnoise.h \
    sdk/math/xslowbit.h \
    sdk/math/xtimebuffer.h \
    sdk/ml/xc_tsne.h \
    sdk/networking/xnetworkaddr.h \
    sdk/networking/xosc.h \
    sdk/sdk_cpp.h \
    sdk/sdk_h.h \
    sdk/types/xarray.h \
    sdk/types/xbasictypes.h \
    sdk/types/xcall.h \
    sdk/types/xcalldatatypes.h \
    sdk/types/xcallerror.h \
    sdk/types/xcalltype.h \
    sdk/types/xlink.h \
    sdk/types/xobject.h \
    sdk/types/xobjectvis/xobjectvis.h \
    sdk/types/xobjectvis/xobjectvisimage.h \
    sdk/types/xobjectvis/xobjectvissoundbuffer.h \
    sdk/types/xobjectvis/xobjectvissoundformat.h \
    sdk/types/xpointer.h \
    sdk/types/xprotecteddata.h \
    sdk/types/xrange.h \
    sdk/types/xraster.h \
    sdk/types/xsoundtypes.h \
    sdk/types/xtype.h \
    sdk/types/xtypeconvertor.h \
    sdk/types/xtypes.h \
    sdk/types/xwaschanged.h \
    sdk/utility/jsonutils.h \
    sdk/utility/qt_widgets.h \
    sdk/utility/xexecbatch.h \
    sdk/utility/xfiles.h \
    sdk/utility/xhandlingerrors.h \
    sdk/utility/ximageeffect.h \
    sdk/utility/xmoduleutils.h \
    sdk/utility/xparse_tree.h \
    sdk/utility/xparser.h \
    sdk/utility/xrasterutils.h \
    sdk/utility/xsysutils.h \
    sdk/utility/xtimemeasure.h \
    components/gui/xclucombobox.h \
    components/gui/xcludoublespinbox.h \
    components/gui/xcluscrollarea.h \
    components/gui/xcluspinbox.h \
    host/consoleview.h \
    host/dialogs/dialogmodulename.h \
    host/dialogs/dialogrenamemodule.h \
    host/dialogs/dialogtestmoduleinterface.h \
    host/editormodules.h \
    host/dialogs/dialogaddmodule.h \
    host/projectgui.h \
    python/pythoncore.h \
    project/project_props.h \
    project/project.h \
    project/projecteditorprops.h \
    sdk/utility/xtypeutils.h \
    sdk/utility/xutils.h

#--------------------------------------------------------------------------
#Python
# 1. Add Python installation to Xclu-bin/Python/
# 2. Copy python312.dll, python312.pdb, python312_d.dll, python312_d.pdb to Xclu-bin
#--------------------------------------------------------------------------
INCLUDEPATH += python

#windows64
windows {
    INCLUDEPATH += ../Xclu-bin/Python/include
    release: LIBS += ../Xclu-bin/Python/libs/python312.lib
    debug: LIBS += ../Xclu-bin/Python/libs/python312_d.lib
}

unix {
  # resolves this problem: https://www.cyberforum.ru/ubuntu-linux/thread2262844.html
  # (and this problem is only in linux)
  QMAKE_LFLAGS += -no-pie
}
#--------------------------------------------------------------------------
#Built-in and custom modules
#https://wiki.qt.io/Including_.pro_Files
#--------------------------------------------------------------------------
include(Xclu_builtin.pri)

#Custom modules of Xclu, used for private user's projects.
#If you don't have them, just comment!
include(Xclu_custom.pri)

#--------------------------------------------------------------------------

DISTFILES +=

