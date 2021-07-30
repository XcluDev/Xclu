#---------------------------------------------------
#List of modules for this project for using in Xclu
#--------------------------------------------------------------------------

#windows 64 bit
windows {
    INCLUDEPATH += "D:/ML/EmoSound/EmoXclu/xclucpp"

    SOURCES += \
    $$PWD/xmoduleemoai.cpp

    HEADERS += \
    $$PWD/xmoduleemoai.h
   
}


#unix {
#    INCLUDEPATH += "../../Cosmo/Cosmovibro/CosmovibroRt"
# ...
#}


#--------------------------------------------------------------------------

HEADERS += \
    $$PWD/auto.h

#RESOURCES += \
#    $$PWD/shaders.qrc
