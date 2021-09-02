QT += gui

TEMPLATE = lib
DEFINES += UNTITLED_LIBRARY

CONFIG += c++11

INCLUDEPATH += <your_boost_path>/boost_1_76_0/
INCLUDEPATH += <your_dicomlib_path>/dicomlib/include
INCLUDEPATH += include \
               include/dicom \
               include/jpg \
               include/bmp \
               include/png \
               include/krl


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    artemis.cpp

HEADERS += \
    artemis_global.h \
    artemis.h

#Artemis headers
HEADERS += include/Pixel.h \
           include/ImageBase.h \
           include/dicom/DcmLib.h \
           include/jpg/JpgLib.h \
           include/bmp/BmpLib.h \
           include/png/PngLib.h \
           include/krl/KrlFileHandler.h \
           include/krl/KrlLib.h

#Artemis sources
SOURCES += src/Pixel.cpp \
           src/ImageBase.cpp \
           src/dicom/DcmLib.cpp \
           src/jpg/JpgLib.cpp \
           src/bmp/BmpLib.cpp \
           src/png/PngLib.cpp \
           src/krl/KrlFileHandler.cpp \
           src/krl/KrlLib.cpp

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
