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
#ВАЖНО: Установить каталог сборки D:\perevalovds.com\_2020\Xclu\temp
#тогда все промежуточные файлы будут в temp, а результат в Xclu-bin
#---------------------------------------------------

#---------------------------------------------------

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


QT       += core gui
QT       += multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11


# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

RESOURCES += \
    xclu.qrc

# Про иконки: https://doc.qt.io/qt-5/appicon.html
RC_ICONS = images/logo/appicon.ico

FORMS += \
    project/DialogPreferences1.ui \
    project/dialog.ui \
    project/dialogpreferences.ui

INCLUDEPATH += core modules builtin_modules_impl/System/ interface interfacegui 
INCLUDEPATH += project objects

# GLM
INCLUDEPATH += ./ glm glm/ glm/gtx

SOURCES += \
    builtin_modules_impl/Screen/rtmoduleguiimage.cpp \
    builtin_modules_impl/Screen/rtmoduleguinumber.cpp \
    builtin_modules_impl/Screen/rtmoduleguiwindow.cpp \
    core/xclu_parse_tree.cpp \
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
    interfacegui/interfaceguistringlist.cpp \
    interface/interfaceitemcheckbox.cpp \
    interface/interfaceitemfloat.cpp \
    interface/interfaceitemgroup.cpp \
    interface/interfaceitemint.cpp \
    interface/interfaceitempage.cpp \
    interface/interfaceitemseparator.cpp \
    interface/interfaceitemstring.cpp \
    interfacegui/interfaceguipage.cpp \
    interface/interfaceitemstringlist.cpp \
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
    project/dialogpreferences.cpp \
    project/dialogrenamemodule.cpp \
    project/dialogtestmoduleinterface.cpp \
    project/editormodule.cpp \
    project/editormodules.cpp \
    project/project.cpp \
    project/dialogaddmodule.cpp \
    mainwindow.cpp  \
    project/projectgui.cpp \
    project/projectproperties.cpp \
    project/projectruntime.cpp \
    project/settingskeys.cpp

HEADERS += \
    builtin_modules_impl/Screen/rtmoduleguiimage.h \
    builtin_modules_impl/Screen/rtmoduleguinumber.h \
    builtin_modules_impl/Screen/rtmoduleguiwindow.h \
    core/xclu_parse_tree.h \
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
    core/incl_qt.h \
    core/incl_qtcpp.h \
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
    interfacegui/interfaceguistringlist.h \
   interface/interfaceitemcheckbox.h \
   interface/interfaceitemfloat.h \
   interface/interfaceitemgroup.h \
   interface/interfaceitemint.h \
   interface/interfaceitempage.h \
    interface/interfaceitemseparator.h \
   interface/interfaceitemstring.h \
   interfacegui/interfaceguipage.h \
    interface/interfaceitemstringlist.h \
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
    project/dialogpreferences.h \
    project/dialogrenamemodule.h \
    project/dialogtestmoduleinterface.h \
    project/editormodule.h \
    project/editormodules.h \
    project/project.h \
    project/dialogaddmodule.h \
    mainwindow.h   \
    project/projectgui.h \
    project/projectproperties.h \
    project/projectruntime.h \
    project/settingskeys.h


