#-------------------------------------------------
#
# Project created by QtCreator 2020-09-29T12:15:12
#
#-------------------------------------------------

QT       += core gui charts sql datavisualization uitools

TARGET = Donut_GuiSetup
TEMPLATE = lib

#PRECOMPILED_HEADER = /home/rklasky/workspaceQtCreator/Donut_GuiSetup/precompiled_header.h
#CONFIG += precompile_header

DEFINES += DONUT_GUISETUP_LIBRARY
CONFIG += c++14

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
    nmfSetupTab01.cpp \
    nmfSetupTab02.cpp \
    nmfSetupTab03.cpp \
    nmfSetupTab04.cpp

HEADERS += \
    nmfSetupTab01.h \
    nmfSetupTab02.h \
    nmfSetupTab03.h \
    nmfSetupTab04.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../build-nmfUtilities-Qt_5_12_3_gcc64-Release/release/ -lnmfUtilities
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../build-nmfUtilities-Qt_5_12_3_gcc64-Release/debug/ -lnmfUtilities
else:unix: LIBS += -L$$PWD/../../build-nmfUtilities-Qt_5_12_3_gcc64-Release/ -lnmfUtilities

INCLUDEPATH += $$PWD/../../nmfSharedUtilities/nmfUtilities
DEPENDPATH += $$PWD/../../nmfSharedUtilities/nmfUtilities

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../build-Donut_ModelAPI-Qt_5_12_3_gcc64-Release/release/ -lDonut_ModelAPI
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../build-Donut_ModelAPI-Qt_5_12_3_gcc64-Release/debug/ -lDonut_ModelAPI
else:unix: LIBS += -L$$PWD/../../build-Donut_ModelAPI-Qt_5_12_3_gcc64-Release/ -lDonut_ModelAPI

INCLUDEPATH += $$PWD/../Donut_ModelAPI
DEPENDPATH += $$PWD/../Donut_ModelAPI
