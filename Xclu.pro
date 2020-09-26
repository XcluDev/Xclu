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


QT += core gui
QT += multimedia multimediawidgets
QT += serialport

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
    host/dialogs/DialogPreferences1.ui \
    host/dialogs/dialog.ui \
    host/dialogs/dialogmodulename.ui \
    host/dialogs/dialogpreferences.ui \
    host/mainwindow.ui

INCLUDEPATH += project sdk/math modules components components/gui
INCLUDEPATH += host host/dialogs sdk sdk/types sdk/utility

# GLM
INCLUDEPATH += ./ libs/glm libs/glm/gtx

SOURCES += \
    components/gui/xgui.cpp \
    components/gui/xguibutton.cpp \
    components/gui/xguicheckbox.cpp \
    components/gui/xguienum.cpp \
    components/gui/xguifloat.cpp \
    components/gui/xguiint.cpp \
    components/gui/xguiobject.cpp \
    components/gui/xguipage.cpp \
    components/gui/xguiseparator.cpp \
    components/gui/xguistring.cpp \
    components/gui/xguitext.cpp \
    components/registrarxitem.cpp \
    components/xitem.cpp \
    components/xitembutton.cpp \
    components/xitemcheckbox.cpp \
    components/xitemenum.cpp \
    components/xitemfloat.cpp \
    components/xitemgroup.cpp \
    components/xitemint.cpp \
    components/xitemobject.cpp \
    components/xitempage.cpp \
    components/xitemseparator.cpp \
    components/xitemstring.cpp \
    components/xitemtext.cpp \
    host/mainwindow.cpp \
    host/recentfiles.cpp \
    host/xclu_paths.cpp \
    host/xclu_settings.cpp \
    host/xclu_theme.cpp \
    modules/registrarxmodule.cpp \
    project/project.cpp \
    project/projectproperties.cpp \
    project/projectruntime.cpp \
    sdk/math/math_types.cpp \
    sdk/math/math_utils.cpp \
    sdk/math/raster.cpp \
    sdk/math/slowbit.cpp \
    modules/exportinterface.cpp \
    modules/moduledescription.cpp \
    modules/moduleseed.cpp \
    sdk/types/xarray.cpp \
    sdk/types/xarray_multi.cpp \
    sdk/types/xstruct.cpp \
    sdk/utility/console.cpp \
    sdk/utility/incl_cpp.cpp \
    sdk/utility/incl_h.cpp \
    sdk/utility/jsonutils.cpp \
    sdk/utility/xclu_parse_tree.cpp \
    sdk/utility/xclu_types.cpp \
    sdk/utility/xclu_utils.cpp \
    sdk/xmodule.cpp \
    components/visibilitygroups.cpp \
    components/gui/xclucombobox.cpp \
    components/gui/xcludoublespinbox.cpp \
    components/gui/xcluscrollarea.cpp \
    components/gui/xcluspinbox.cpp \
    modules/module.cpp \
    modules/moduleinterface.cpp \
    modules/modulesfactory.cpp \
    main.cpp \
    sdk/types/xcluobjectimage.cpp \
    sdk/types/xcluobjectsoundformat.cpp \
    sdk/types/xcluobjectwrapper.cpp \
    sdk/types/xcluprotecteddata.cpp \
    host/consoleview.cpp \
    host/dialogs/dialogmodulename.cpp \
    host/dialogs/dialogpreferences.cpp \
    host/dialogs/dialogrenamemodule.cpp \
    host/dialogs/dialogtestmoduleinterface.cpp \
    host/editormodule.cpp \
    host/editormodules.cpp \
    host/dialogs/dialogaddmodule.cpp \
    host/projectgui.cpp \
    python/pythoncore.cpp \
    sdk/xclass.cpp

HEADERS += \
    components/gui/xgui.h \
    components/gui/xguibutton.h \
    components/gui/xguicheckbox.h \
    components/gui/xguienum.h \
    components/gui/xguifloat.h \
    components/gui/xguiint.h \
    components/gui/xguiobject.h \
    components/gui/xguipage.h \
    components/gui/xguiseparator.h \
    components/gui/xguistring.h \
    components/gui/xguitext.h \
    components/registrarxitem.h \
    components/xitem.h \
    components/xitembutton.h \
    components/xitemcheckbox.h \
    components/xitemenum.h \
    components/xitemfloat.h \
    components/xitemgroup.h \
    components/xitemint.h \
    components/xitemobject.h \
    components/xitempage.h \
    components/xitemseparator.h \
    components/xitemstring.h \
    components/xitemtext.h \
    host/mainwindow.h \
    host/recentfiles.h \
    host/xclu_paths.h \
    host/xclu_settings.h \
    host/xclu_theme.h \
    modules/registrarxmodule.h \
    project/project.h \
    project/projectproperties.h \
    project/projectruntime.h \
    sdk/math/int2.h \
    sdk/math/math_types.h \
    sdk/math/math_utils.h \
    sdk/math/raster.h \
    sdk/math/slowbit.h \
    modules/exportinterface.h \
    modules/moduledescription.h \
    modules/moduleseed.h \
    sdk/types/xarray.h \
    sdk/types/xarray_multi.h \
    sdk/types/xstruct.h \
    sdk/utility/console.h \
    sdk/utility/incl_cpp.h \
    sdk/utility/incl_h.h \
    sdk/utility/jsonutils.h \
    sdk/utility/qt_widgets.h \
    sdk/utility/xclu_parse_tree.h \
    sdk/utility/xclu_types.h \
    sdk/utility/xclu_utils.h \
    sdk/xmodule.h \
    components/visibilitygroups.h \
    components/gui/xclucombobox.h \
    components/gui/xcludoublespinbox.h \
    components/gui/xcluscrollarea.h \
    components/gui/xcluspinbox.h \
    modules/module.h \
    modules/moduleinterface.h \
    modules/modulesfactory.h \
    sdk/types/xcluobjectimage.h \
    sdk/types/xcluobjectsoundformat.h \
    sdk/types/xcluobjectwrapper.h \
    sdk/types/xcluprotecteddata.h \
    host/consoleview.h \
    host/dialogs/dialogmodulename.h \
    host/dialogs/dialogpreferences.h \
    host/dialogs/dialogrenamemodule.h \
    host/dialogs/dialogtestmoduleinterface.h \
    host/editormodule.h \
    host/editormodules.h \
    host/dialogs/dialogaddmodule.h \
    host/projectgui.h \
    python/pythoncore.h \
    sdk/xclass.h

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
#Built-in and custom modules
#https://wiki.qt.io/Including_.pro_Files
#--------------------------------------------------------------------------
include(Xclu_builtin.pri)

#Custom modules of Xclu, used for private user's projects.
#If you don't have them, just comment!
include(Xclu_custom.pri)

#--------------------------------------------------------------------------

