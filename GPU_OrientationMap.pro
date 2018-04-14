#-------------------------------------------------
#
# Project created by QtCreator 2018-04-12T18:49:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GPU_OrientationMap
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    omap.cpp \
    omap_gpu.cpp

HEADERS += \
        mainwindow.h \
    omap.h \
    omap_gpu.h \
    config.h

FORMS += \
        mainwindow.ui

RC_FILE = icon.rc

# afcuda
unix|win32: LIBS += -L'C:/Program Files/ArrayFire/v3/lib/' -lafcuda

INCLUDEPATH += 'C:/Program Files/ArrayFire/v3/include'
DEPENDPATH += 'C:/Program Files/ArrayFire/v3/include'

#opencv
win32:CONFIG(release, debug|release): LIBS += -LC:/opencv/build/x64/vc15/lib/ -lopencv_world341
else:win32:CONFIG(debug, debug|release): LIBS += -LC:/opencv/build/x64/vc15/lib/ -lopencv_world341d
else:unix: LIBS += -LC:/opencv/build/x64/vc15/lib/ -lopencv_world341

INCLUDEPATH += C:/opencv/build/include
DEPENDPATH += C:/opencv/build/include

#qcustomplot
win32:CONFIG(release, debug|release): LIBS += -LC:/qcustomplot/ -lqcustomplot2
else:win32:CONFIG(debug, debug|release): LIBS += -LC:/qcustomplot/ -lqcustomplotd2
else:unix: LIBS += -LC:/qcustomplot/ -lqcustomplot2

INCLUDEPATH += C:/qcustomplot
DEPENDPATH += C:/qcustomplot
