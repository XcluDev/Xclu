Here we describe in details how to create custom module, dedicated for working in your project and which normally will not shared with other users publicly. The general overview about creating modules see here: https://forum.xclu.dev/t/creating-new-built-in-or-private-module/37.


For example, for project "Cosmovibrationum" we created custom module "CosmoVibro".
It was placed at `CosmovibroRt` folder and consists of the following files:
    
    cosmovibro.pri
    description.xgui
    xmodulecosmodrawing.cpp
    xmodulecosmodrawing.h
    xmodulecosmoimage.cpp
    xmodulecosmoimage.h
    xmodulecosmoosc.cpp
    xmodulecosmoosc.h
    xmodulecosmosound.cpp
    xmodulecosmosound.h
    xmodulecosmostars.cpp
    xmodulecosmostars.h
    xmodulecosmovibro.cpp
    xmodulecosmovibro.h


To add the custom module to Xclu, you need to perform the following steps:

#### 1. Create folder for module 
The folder normally is created outside Xclu folder. Also it's good idea to put this folder to Github's private folder (or any similar).

#### 2. Put module's description `description.xgui`
`description.xgui` file describes module's interface. You may copy it from other builti-in modules descriptions, and then modify it in NotePad++.

In current settings, you need to put this to folder **Xclu-bin/modules/YOURMODULE**.

It's good idea to enable highlighting `xgui` files in Notepad by using file `docs/NotePadPP_XGUI.xml`.

The edited interface can be testes with *Developer - Test module interface* dialog in Xclu.

#### 3. Put C++ files
Put to the folder C++ files. You may start with some built-in module, put its sources here and rename.

You will edit sources a bit later, now we just organizing this, so don't care is there is some inconsistency of the code.

#### 4. Create `pri`-file
Create some file with extenstion `pri`. In our example it's `cosmovibro.pri`, but you may use any other name, corresponding your module's name.

This is "subproject" Qt file. It contains list of C++ source files (and libraries) required for the project. 
The typical contents of the file is the following:

    windows {
        INCLUDEPATH += "../../../../eamuseum/Projects/2020-08-CosmoVibro/Cosmo/Cosmovibro/CosmovibroRt"
        SOURCES += \
            ../../../../eamuseum/Projects/2020-08-CosmoVibro/Cosmo/Cosmovibro/CosmovibroRt/xmodulecosmovibro.cpp \
            ../../../../eamuseum/Projects/2020-08-CosmoVibro/Cosmo/Cosmovibro/CosmovibroRt/xmodulecosmoimage.cpp

        HEADERS += \
            ../../../../eamuseum/Projects/2020-08-CosmoVibro/Cosmo/Cosmovibro/CosmovibroRt/xmodulecosmovibro.h \
            ../../../../eamuseum/Projects/2020-08-CosmoVibro/Cosmo/Cosmovibro/CosmovibroRt/xmodulecosmoimage.h 
    }
    unix {
        INCLUDEPATH += "../../Cosmo/Cosmovibro/CosmovibroRt"
        SOURCES += \
            ../Cosmo/Cosmovibro/CosmovibroRt/xmodulecosmovibro.cpp \
            ../Cosmo/Cosmovibro/CosmovibroRt/xmodulecosmoimage.cpp
        HEADERS += \
            ../Cosmo/Cosmovibro/CosmovibroRt/xmodulecosmovibro.h \
            ../Cosmo/Cosmovibro/CosmovibroRt/xmodulecosmoimage.h 
        }

Here is different folders for Windows and Linux builds. If you compiling only for one platform, you may omit this. Also, please note, you should to list all files, but in the example we omit several `cpp` and `h` files for shortening.


#### 3. Add module to Xclu modules list
Open at NodePad++ file `Xclu_custom.ini` and add there the module's name ad folder.
Windows and Linux folders are placed differently:

    [windows]
    module1=CosmoVibro
    module1_folder=D:/eamuseum/Projects/2020-08-CosmoVibro/Cosmo/Cosmovibro/CosmovibroRt
    module2=.....
    module2_folder=....

    [unix]
    module1=CosmoVibro
    module1_folder=../Cosmo/Cosmovibro/CosmovibroRt
    module2=.....
    module2_folder=....

On this stage, you may run Xclu and try to add the module to the project. You should see your module at "Custom" category. But, the module will have no implementation. Adding implementation will be discussed right now.

#### 4. Add module to Qt project file
Include to file `Xclu_custom.pri` your module's `pri` file to inform Qt about your C++ sources.
You may edit `Xclu_custom.pri` right in Qt's Xclu project, or using NotePad++. 

You should add the `pri` file by the foolowing way:

    windows {
        include(../../../../eamuseum/Projects/2020-08-CosmoVibro/Cosmo/Cosmovibro/CosmovibroRt/cosmovibro.pri)
    }
    unix {
        include(../../Cosmo/Cosmovibro/CosmovibroRt/cosmovibro.pri)
    }

After that, you may run Qt's menu command Build - Run qmake, and start editing your C++ sources.
After that, by running Xclu, the module will work!

#### 5. Deploying the module
To be able to run the module on the different machine, you must put module's description files - `description.xgui` and any others, such as help file, to Xclu binary folder `modules/[your module name]`

In our case, we need to put `decrtiption.xgui` to `modules/CosmoVibro`.

The next thing required is to set Xclu to deployment mode and recompile it, see https://forum.xclu.dev/t/building-xclu-in-deployment-mode/42