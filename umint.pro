#-------------------------------------------------
#
# Project created by QtCreator 2015-03-25T00:28:13
#
#-------------------------------------------------

QT       += core gui opengl

@
INCLUDEPATH += -F$(HOME)/Library/Frameworks
LIBS += -F$(HOME)/Library/Frameworks -framework OpenGL
LIBS += -F$(HOME)/Library/Frameworks -framework GLUT
LIBS += -L/usr/local/lib -lSOIL
LIBS += -lSOIL
@

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = umint
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    color.cpp \
    point.cpp \
    utilities.cpp \
    locality.cpp \
    EasyBMP/EasyBMP.cpp

HEADERS  += mainwindow.h \
    color.h \
    point.h \
    utilities.h \
    locality.h \
    ../Simple OpenGL Image Library/src/SOIL.h \
    EasyBMP/EasyBMP.h \
    EasyBMP/EasyBMP_BMP.h \
    EasyBMP/EasyBMP_DataStructures.h \
    EasyBMP/EasyBMP_VariousBMPutilities.h \
    SOIL.h


FORMS    += mainwindow.ui

