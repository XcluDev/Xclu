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
    host/dialogs/dialogeditlink.ui \
    host/dialogs/dialogmodulename.ui \
    host/dialogs/dialogpreferences.ui \
    host/mainwindow.ui

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

INCLUDEPATH += project sdk/math modules
INCLUDEPATH += host host/dialogs sdk sdk/types sdk/utility

# GLM
INCLUDEPATH += ./ libs/glm libs/glm/gtx

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
    components/group/xitemgroup.cpp \
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
    sdk/math/slowbit.cpp \
    modules/exportinterface.cpp \
    modules/moduledescription.cpp \
    modules/moduleseed.cpp \
    sdk/types/xarray.cpp \
    sdk/types/xarray_multi.cpp \
    sdk/types/xlink.cpp \
    sdk/types/xraster.cpp \
    sdk/types/xref.cpp \
    sdk/types/xstruct.cpp \
    sdk/types/xtypes.cpp \
    sdk/utility/console.cpp \
    sdk/utility/incl_cpp.cpp \
    sdk/utility/incl_h.cpp \
    sdk/utility/jsonutils.cpp \
    sdk/utility/xclu_parse_tree.cpp \
    sdk/utility/xclu_types.cpp \
    sdk/utility/xclu_utils.cpp \
    sdk/xmodule.cpp \
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
    host/editormodules.cpp \
    host/dialogs/dialogaddmodule.cpp \
    host/projectgui.cpp \
    python/pythoncore.cpp \
    sdk/xclass.cpp

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
    components/group/xitemgroup.h \
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
    sdk/math/slowbit.h \
    modules/exportinterface.h \
    modules/moduledescription.h \
    modules/moduleseed.h \
    sdk/sdk_cpp.h \
    sdk/sdk_h.h \
    sdk/types/xarray.h \
    sdk/types/xarray_multi.h \
    sdk/types/xlink.h \
    sdk/types/xraster.h \
    sdk/types/xref.h \
    sdk/types/xstruct.h \
    sdk/types/xtypes.h \
    sdk/utility/console.h \
    sdk/utility/incl_cpp.h \
    sdk/utility/incl_h.h \
    sdk/utility/jsonutils.h \
    sdk/utility/qt_widgets.h \
    sdk/utility/xclu_parse_tree.h \
    sdk/utility/xclu_types.h \
    sdk/utility/xclu_utils.h \
    sdk/xmodule.h \
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

