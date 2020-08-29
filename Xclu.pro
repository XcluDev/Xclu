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

#--------------------------------------------------------------------------
#General app settings
#--------------------------------------------------------------------------

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


QT       += core gui
QT       += multimedia multimediawidgets

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
#Common source, headers and forms files
#--------------------------------------------------------------------------

FORMS += \
    project/dialogs/DialogPreferences1.ui \
    project/dialogs/dialog.ui \
    project/dialogs/dialogmodulename.ui \
    project/dialogs/dialogpreferences.ui

INCLUDEPATH += core modules builtin_modules_impl/System/ interface interfacegui 
INCLUDEPATH += project project/dialogs objects

# GLM
INCLUDEPATH += ./ glm glm/ glm/gtx

SOURCES += \
    core/raster.cpp \
    core/types.cpp \
    core/utils.cpp \
    builtin_modules_impl/Screen/rtmodulewimage.cpp \
    core/xclu_parse_tree.cpp \
    core/xclu_paths.cpp \
    core/xclu_settings.cpp \
    core/xclu_theme.cpp \
    core/xclu_types.cpp \
    core/xclu_utils.cpp \
    builtin_modules_impl/Screen/rtmodulefbo.cpp \
    builtin_modules_impl/Screen/rtmodulefragmentshader.cpp \
    builtin_modules_impl/Sound/rtmodulesynthfromimage.cpp \
    modules/moduledescription.cpp \
    objects/xcluarray.cpp \
    interface/interfaceitemobject.cpp \
    interface/visibilitygroups.cpp \
    objects/xcluobject.cpp \
    interfacegui/interfaceguiobject.cpp \
    interfacegui/xclucombobox.cpp \
    interfacegui/xcludoublespinbox.cpp \
    interfacegui/xcluscrollarea.cpp \
    interfacegui/xcluspinbox.cpp \
    builtin_modules_impl/Images/rtmodulewebcamera.cpp \
    builtin_modules_impl/Sound/rtmodulesoundout.cpp \
    builtin_modules_impl/System/rtmoduleexecute.cpp \
    core/incl_qt.cpp \
    core/incl_qtcpp.cpp \
    core/incl_std.cpp \
    core/console.cpp \
    interface/interfaceitembutton.cpp \
    interface/interfaceitemtext.cpp \
    interfacegui/interfacegui.cpp \
    interfacegui/interfaceguibutton.cpp \
    interfacegui/interfaceguicheckbox.cpp \
    interfacegui/interfaceguifloat.cpp \
    interfacegui/interfaceguiint.cpp \
    interfacegui/interfaceguiseparator.cpp \
    interfacegui/interfaceguistring.cpp \
    interface/interfaceitemcheckbox.cpp \
    interface/interfaceitemfloat.cpp \
    interface/interfaceitemgroup.cpp \
    interface/interfaceitemint.cpp \
    interface/interfaceitempage.cpp \
    interface/interfaceitemseparator.cpp \
    interface/interfaceitemstring.cpp \
    interfacegui/interfaceguipage.cpp \
    interfacegui/interfaceguitext.cpp \
    builtin_modules_impl/Utils/rtmoduletest.cpp \
    modules/module.cpp \
    modules/moduleinfo.cpp \
    modules/moduleinterface.cpp \
    modules/modulesfactory.cpp \
    main.cpp \
    interface/interfaceitem.cpp \
    modules/rtmodule.cpp \
    modules/rtmoduleregistrar.cpp \
    objects/xcluobjectdatabase.cpp \
    objects/xcluobjectimage.cpp \
    objects/xcluobjectsoundformat.cpp \
    objects/xcluobjectwrapper.cpp \
    objects/xcluprotecteddata.cpp \
    project/consoleview.cpp \
    project/dialogs/dialogmodulename.cpp \
    project/dialogs/dialogpreferences.cpp \
    project/dialogs/dialogrenamemodule.cpp \
    project/dialogs/dialogtestmoduleinterface.cpp \
    project/editormodule.cpp \
    project/editormodules.cpp \
    project/project.cpp \
    project/dialogs/dialogaddmodule.cpp \
    mainwindow.cpp  \
    project/projectgui.cpp \
    project/projectproperties.cpp \
    project/projectruntime.cpp \
    python/pythoncore.cpp \
    builtin_modules_impl/Core/rtmodulescalar.cpp \
    builtin_modules_impl/Screen/rtmodulewindow.cpp \
    interface/interfaceitemenum.cpp \
    interfacegui/interfaceguienum.cpp \
    builtin_modules_impl/Sound/rtmodulesoundosc.cpp \
    builtin_modules_impl/Communication/rtmoduleserial.cpp \
    core/slowbit.cpp

HEADERS += \
    core/incl_h.h \
    core/incl_cpp.h \
    core/raster.h \
    core/types.h \
    core/utils.h \
    builtin_modules_impl/Screen/rtmodulewimage.h \
    core/int2.h \
    core/xclu_parse_tree.h \
    core/xclu_paths.h \
    core/xclu_settings.h \
    core/xclu_theme.h \
    core/xclu_types.h \
    core/xclu_utils.h \
    builtin_modules_impl/Screen/rtmodulefbo.h \
    builtin_modules_impl/Screen/rtmodulefragmentshader.h \
    builtin_modules_impl/Sound/rtmodulesynthfromimage.h \
    modules/moduledescription.h \
    objects/xcluarray.h \
    interface/interfaceitemobject.h \
    interface/visibilitygroups.h \
    objects/xcluobject.h \
    interfacegui/interfaceguiobject.h \
    interfacegui/xclucombobox.h \
    interfacegui/xcludoublespinbox.h \
    interfacegui/xcluscrollarea.h \
    interfacegui/xcluspinbox.h \
    builtin_modules_impl/Images/rtmodulewebcamera.h \
    builtin_modules_impl/Sound/rtmodulesoundout.h \
    builtin_modules_impl/System/rtmoduleexecute.h \
    core/incl_std.h \
    core/console.h \
    interface/interfaceitembutton.h \
    interface/interfaceitemtext.h \
   interfacegui/interfacegui.h \
    interfacegui/interfaceguibutton.h \
    interfacegui/interfaceguicheckbox.h \
    interfacegui/interfaceguifloat.h \
    interfacegui/interfaceguiint.h \
    interfacegui/interfaceguiseparator.h \
    interfacegui/interfaceguistring.h \
   interface/interfaceitemcheckbox.h \
   interface/interfaceitemfloat.h \
   interface/interfaceitemgroup.h \
   interface/interfaceitemint.h \
   interface/interfaceitempage.h \
    interface/interfaceitemseparator.h \
   interface/interfaceitemstring.h \
   interfacegui/interfaceguipage.h \
    interfacegui/interfaceguitext.h \
    builtin_modules_impl/Utils/rtmoduletest.h \
    modules/module.h \
    modules/moduleinfo.h \
    modules/moduleinterface.h \
    modules/modulesfactory.h \
    interface/interfaceitem.h \
    modules/rtmodule.h \
    modules/rtmoduleregistrar.h \
    objects/xcluobjectdatabase.h \
    objects/xcluobjectimage.h \
    objects/xcluobjectsoundformat.h \
    objects/xcluobjectwrapper.h \
    objects/xcluprotecteddata.h \
    project/consoleview.h \
    project/dialogs/dialogmodulename.h \
    project/dialogs/dialogpreferences.h \
    project/dialogs/dialogrenamemodule.h \
    project/dialogs/dialogtestmoduleinterface.h \
    project/editormodule.h \
    project/editormodules.h \
    project/project.h \
    project/dialogs/dialogaddmodule.h \
    mainwindow.h   \
    project/projectgui.h \
    project/projectproperties.h \
    project/projectruntime.h \
    python/pythoncore.h \
    core/qt_widgets.h \
    builtin_modules_impl/Core/rtmodulescalar.h \
    builtin_modules_impl/Screen/rtmodulewindow.h \
    interface/interfaceitemenum.h \
    interfacegui/interfaceguienum.h \
    builtin_modules_impl/Sound/rtmodulesoundosc.h \
    builtin_modules_impl/Communication/rtmoduleserial.h \
    core/slowbit.h

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
#Custom modules
#Comment if not required or you don't have them
#--------------------------------------------------------------------------
unix {
    INCLUDEPATH += "../../Cosmo/Cosmovibro/CosmovibroRt"

    SOURCES += \
        ../Cosmo/Cosmovibro/CosmovibroRt/rtmodulecosmovibro.cpp
        ../Cosmo/Cosmovibro/CosmovibroRt/rtmodulecosmoimage.cpp

    HEADERS += \
        ../Cosmo/Cosmovibro/CosmovibroRt/rtmodulecosmovibro.h
        ../Cosmo/Cosmovibro/CosmovibroRt/rtmodulecosmoimage.h
}

#windows 64 bit
windows {
    INCLUDEPATH += "../../../../eamuseum/Projects/2020-08-CosmoVibro/Cosmo/Cosmovibro/CosmovibroRt"

    SOURCES += \
        ../../../../eamuseum/Projects/2020-08-CosmoVibro/Cosmo/Cosmovibro/CosmovibroRt/rtmodulecosmovibro.cpp \
        ../../../../eamuseum/Projects/2020-08-CosmoVibro/Cosmo/Cosmovibro/CosmovibroRt/rtmodulecosmoimage.cpp \
        ../../../../eamuseum/Projects/2020-08-CosmoVibro/Cosmo/Cosmovibro/CosmovibroRt/rtmodulecosmodrawing.cpp


    HEADERS += \
        ../../../../eamuseum/Projects/2020-08-CosmoVibro/Cosmo/Cosmovibro/CosmovibroRt/rtmodulecosmovibro.h \
        ../../../../eamuseum/Projects/2020-08-CosmoVibro/Cosmo/Cosmovibro/CosmovibroRt/rtmodulecosmoimage.h \
        ../../../../eamuseum/Projects/2020-08-CosmoVibro/Cosmo/Cosmovibro/CosmovibroRt/rtmodulecosmodrawing.h
}

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
}
#--------------------------------------------------------------------------
