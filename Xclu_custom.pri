#--------------------------------------------------------------------------
#Custom modules of Xclu, used for private user's projects.
#Comment them if not required or you don't have them
#Here are included normally only "pri" files
#the typical pri file contains the following:
#
#windows {
#    INCLUDEPATH += "../../../../eamuseum/Projects/2020-08-CosmoVibro/Cosmo/Cosmovibro/CosmovibroRt"
#    SOURCES += \
#        ../../../../eamuseum/Projects/2020-08-CosmoVibro/Cosmo/Cosmovibro/CosmovibroRt/rtmodulecosmovibro.cpp \
#        ../../../../eamuseum/Projects/2020-08-CosmoVibro/Cosmo/Cosmovibro/CosmovibroRt/rtmodulecosmoimage.cpp
#    HEADERS += \
#        ../../../../eamuseum/Projects/2020-08-CosmoVibro/Cosmo/Cosmovibro/CosmovibroRt/rtmodulecosmovibro.h \
#        ../../../../eamuseum/Projects/2020-08-CosmoVibro/Cosmo/Cosmovibro/CosmovibroRt/rtmodulecosmoimage.h
#}
#unix {
#    INCLUDEPATH += "../../Cosmo/Cosmovibro/CosmovibroRt"
#    SOURCES += \
#        ../Cosmo/Cosmovibro/CosmovibroRt/rtmodulecosmovibro.cpp \
#        ../Cosmo/Cosmovibro/CosmovibroRt/rtmodulecosmoimage.cpp
#    HEADERS += \
#        ../Cosmo/Cosmovibro/CosmovibroRt/rtmodulecosmovibro.h \
#        ../Cosmo/Cosmovibro/CosmovibroRt/rtmodulecosmoimage.h
#}
#--------------------------------------------------------------------------



windows {
    include(../../../../eamuseum/Projects/2020/2020-08-CosmoVibro/Cosmo/Cosmovibro/CosmovibroRt/cosmovibro.pri)
    include(../../../../eamuseum/Projects/2020-10-ReaDiff/Readiff/ReadiffRt/readiff.pri)
    include(D:/ML/EmoSound/EmoXclu/xclucpp/emoai.pri)
    include(D:/perevalovds.com/_2021/2021-KatyaGlaza/Glaza_git/GlazaCpp/Glaza.pri)

}
unix {
    include(../../Cosmo/Cosmovibro/CosmovibroRt/cosmovibro.pri)
}


#--------------------------------------------------------------------------
