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

#ВНИМАНИЕ: На "старом" Qt 5.9 при переименовании или добавлении файлов
#требуется выполнять команду меню "Запустить qmake", иначе выдает ошибки или не видит файл


#SSL on Windows:
#If you get "QSslSocket::connectToHostEncrypted: TLS initialization failed" error on Windows:
#please check OpenSSL at Qt installer at Developer Tools section, 
#and copy libcrypto-1_1-x64.dll, libssl-1_1-x64.dll to Xclu bin folder
#https://ru.stackoverflow.com/questions/952577/qt-network-ssl-qsslsocketconnecttohostencrypted-tls-initialization-failed

#For windows, to collect all required plugins, use:
#D:\Qt\Qt5_14\5.14.2\msvc2017_64\bin\windeployqt.exe --release ./
#(set path to your Qt here)



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
QT += serialport network
QT += 3dcore 3drender 3dinput 3dextras

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
    DEFINES += XCLU_WIN
}
unix {
    DEFINES += XCLU_LINUX
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

# SDK
INCLUDEPATH += project \
               modules

INCLUDEPATH += host \
               host/dialogs

INCLUDEPATH += sdk \
               sdk/audio \
               sdk/math \
               sdk/ml \
               sdk/types \
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

#--------------------------------------------------------------------------
#Common source, headers and forms files
#--------------------------------------------------------------------------
FORMS += \
    host/dialogs/dialogeditlink.ui \
    host/dialogs/dialogeditlinks.ui \
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
    components/raster/xguiraster.cpp \
    components/raster/xitemraster.cpp \
    components/registrarxitem.cpp \
    components/separator/xguiseparator.cpp \
    components/separator/xitemseparator.cpp \
    components/string/xguistring.cpp \
    components/string/xitemstring.cpp \
    components/text/xguitext.cpp \
    components/text/xitemtext.cpp \
    components/visibilitygroups.cpp \
    components/xgui.cpp \
    components/xguieditor.cpp \
    components/xitem.cpp \
    components/xitemscalar.cpp \
    host/dialogs/dialogeditlink.cpp \
    host/dialogs/dialogeditlinks.cpp \
    host/mainwindow.cpp \
    host/recentfiles.cpp \
    host/xc_paths.cpp \
    host/xclu_settings.cpp \
    host/xclu_theme.cpp \
    libs/tsne/sptree.cpp \
    libs/tsne/tsne.cpp \
    modules/registrarxmodule.cpp \
    project/projectcore.cpp \
    project/projectproperties.cpp \
    modules/exportinterface.cpp \
    modules/moduledescription.cpp \
    modules/moduleseed.cpp \
    project/xc_project.cpp \
    sdk/audio/xc_audio.cpp \
    sdk/audio/xc_audio_wavfile.cpp \
    sdk/math/xmath.cpp \
    sdk/math/xnoise.cpp \
    sdk/math/xslowbit.cpp \
    sdk/ml/xc_tsne.cpp \
    sdk/types.cpp \
    sdk/types/xarray.cpp \
    sdk/types/xarray_multi.cpp \
    sdk/types/xlink.cpp \
    sdk/types/xobject.cpp \
    sdk/types/xobjectimage.cpp \
    sdk/types/xobjectsoundformat.cpp \
    sdk/types/xobjectwrapper.cpp \
    sdk/types/xpointer.cpp \
    sdk/types/xprotecteddata.cpp \
    sdk/types/xrange.cpp \
    sdk/types/xraster.cpp \
    sdk/types/xtypes.cpp \
    sdk/types/xwaschanged.cpp \
    sdk/utility/console.cpp \
    sdk/utility/incl_cpp.cpp \
    sdk/utility/incl_h.cpp \
    sdk/utility/jsonutils.cpp \
    sdk/utility/xc_exec_batch.cpp \
    sdk/utility/xc_files.cpp \
    sdk/utility/xclu_parse_tree.cpp \
    sdk/utility/xclu_types.cpp \
    sdk/utility/ximageeffect.cpp \
    sdk/utility/xparser.cpp \
    sdk/utility/xtimemeasure.cpp \
    sdk/xmodule.cpp \
    sdk/xintermodulecalls.cpp \
    components/gui/xclucombobox.cpp \
    components/gui/xcludoublespinbox.cpp \
    components/gui/xcluscrollarea.cpp \
    components/gui/xcluspinbox.cpp \
    modules/module.cpp \
    modules/moduleinterface.cpp \
    modules/modulesfactory.cpp \
    main.cpp \
    host/consoleview.cpp \
    host/dialogs/dialogmodulename.cpp \
    host/dialogs/dialogrenamemodule.cpp \
    host/dialogs/dialogtestmoduleinterface.cpp \
    host/editormodules.cpp \
    host/dialogs/dialogaddmodule.cpp \
    host/projectgui.cpp \
    python/pythoncore.cpp \
    sdk/xclass.cpp \
    sdk/xmodulevisual.cpp \
    sdk/xmodulevisualwidget.cpp

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
    components/raster/xguiraster.h \
    components/raster/xitemraster.h \
    components/registrarxitem.h \
    components/separator/xguiseparator.h \
    components/separator/xitemseparator.h \
    components/string/xguistring.h \
    components/string/xitemstring.h \
    components/text/xguitext.h \
    components/text/xitemtext.h \
    components/visibilitygroups.h \
    components/xgui.h \
    components/xguieditor.h \
    components/xitem.h \
    components/xitemscalar.h \
    host/dialogs/dialogeditlink.h \
    host/dialogs/dialogeditlinks.h \
    host/mainwindow.h \
    host/recentfiles.h \
    host/xc_paths.h \
    host/xclu_settings.h \
    host/xclu_theme.h \
    libs/of/ofNoise.h \
    libs/tsne/sptree.h \
    libs/tsne/tsne.h \
    libs/tsne/vptree.h \
    modules/registrarxmodule.h \
    project/projectcore.h \
    project/projectproperties.h \
    project/xc_project.h \
    sdk/audio/xc_audio.h \
    sdk/audio/xc_audio_wavfile.h \
    sdk/math/int2.h \
    modules/exportinterface.h \
    modules/moduledescription.h \
    modules/moduleseed.h \
    sdk/math/xmath.h \
    sdk/math/xnoise.h \
    sdk/math/xslowbit.h \
    sdk/ml/xc_tsne.h \
    sdk/sdk_cpp.h \
    sdk/sdk_h.h \
    sdk/types.h \
    sdk/types/xarray.h \
    sdk/types/xarray_multi.h \
    sdk/types/xlink.h \
    sdk/types/xobject.h \
    sdk/types/xobjectimage.h \
    sdk/types/xobjectsoundformat.h \
    sdk/types/xobjectwrapper.h \
    sdk/types/xpointer.h \
    sdk/types/xprotecteddata.h \
    sdk/types/xrange.h \
    sdk/types/xraster.h \
    sdk/types/xtypes.h \
    sdk/types/xwaschanged.h \
    sdk/utility/console.h \
    sdk/utility/incl_cpp.h \
    sdk/utility/incl_h.h \
    sdk/utility/jsonutils.h \
    sdk/utility/qt_widgets.h \
    sdk/utility/xc_exec_batch.h \
    sdk/utility/xc_files.h \
    sdk/utility/xclu_parse_tree.h \
    sdk/utility/xclu_types.h \
    sdk/utility/ximageeffect.h \
    sdk/utility/xparser.h \
    sdk/utility/xtimemeasure.h \
    sdk/xmodule.h \
    sdk/xintermodulecalls.h \
    components/gui/xclucombobox.h \
    components/gui/xcludoublespinbox.h \
    components/gui/xcluscrollarea.h \
    components/gui/xcluspinbox.h \
    modules/module.h \
    modules/moduleinterface.h \
    modules/modulesfactory.h \
    host/consoleview.h \
    host/dialogs/dialogmodulename.h \
    host/dialogs/dialogrenamemodule.h \
    host/dialogs/dialogtestmoduleinterface.h \
    host/editormodules.h \
    host/dialogs/dialogaddmodule.h \
    host/projectgui.h \
    python/pythoncore.h \
    sdk/xclass.h \
    sdk/xmodulevisual.h \
    sdk/xmodulevisualwidget.h

#--------------------------------------------------------------------------
#Python
#Currently not used
#--------------------------------------------------------------------------
INCLUDEPATH += python

#windows64
windows {
    #INCLUDEPATH += ../Xclu-bin/Python38/include
    #release: LIBS += ../Xclu-bin/Python38/libs/python38.lib
    #debug: LIBS += ../Xclu-bin/Python38/libs/python38_d.lib
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

DISTFILES += \
    builtin_modules/Window/WRenderArea/description.xgui

