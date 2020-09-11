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
    project/dialogs/DialogPreferences1.ui \
    project/dialogs/dialog.ui \
    project/dialogs/dialogmodulename.ui \
    project/dialogs/dialogpreferences.ui

INCLUDEPATH += core sdk/math modules components components/gui
INCLUDEPATH += project project/dialogs objects sdk

# GLM
INCLUDEPATH += ./ glm glm/ glm/gtx

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
    modules/moduleregistrar.cpp \
    sdk/math/math_types.cpp \
    sdk/math/math_utils.cpp \
    sdk/math/raster.cpp \
    sdk/math/slowbit.cpp \
    sdk/math/xclu_parse_tree.cpp \
    sdk/math/xclu_utils.cpp \
    core/xclu_paths.cpp \
    core/xclu_settings.cpp \
    core/xclu_theme.cpp \
    core/xclu_types.cpp \
    modules/exportinterface.cpp \
    modules/moduledescription.cpp \
    modules/moduleseed.cpp \
    objects/xarray.cpp \
    sdk/xmodule.cpp \
    components/visibilitygroups.cpp \
    components/gui/xclucombobox.cpp \
    components/gui/xcludoublespinbox.cpp \
    components/gui/xcluscrollarea.cpp \
    components/gui/xcluspinbox.cpp \
    core/console.cpp \
    modules/module.cpp \
    modules/moduleinterface.cpp \
    modules/modulesfactory.cpp \
    main.cpp \
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
    core/incl_cpp.cpp \
    core/incl_h.cpp \
    sdk/xclass.cpp \
    objects/xdict.cpp

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
    core/incl_h.h \
    core/incl_cpp.h \
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
    modules/moduleregistrar.h \
    sdk/math/int2.h \
    sdk/math/math_types.h \
    sdk/math/math_utils.h \
    sdk/math/raster.h \
    sdk/math/slowbit.h \
    sdk/math/xclu_parse_tree.h \
    sdk/math/xclu_utils.h \
    core/xclu_paths.h \
    core/xclu_settings.h \
    core/xclu_theme.h \
    core/xclu_types.h \
    modules/exportinterface.h \
    modules/moduledescription.h \
    modules/moduleseed.h \
    objects/xarray.h \
    sdk/xmodule.h \
    components/visibilitygroups.h \
    components/gui/xclucombobox.h \
    components/gui/xcludoublespinbox.h \
    components/gui/xcluscrollarea.h \
    components/gui/xcluspinbox.h \
    core/console.h \
    modules/module.h \
    modules/moduleinterface.h \
    modules/modulesfactory.h \
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
    sdk/xclass.h \
    objects/xdict.h

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

