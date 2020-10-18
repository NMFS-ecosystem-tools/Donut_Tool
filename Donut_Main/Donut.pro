#-------------------------------------------------
#
# Project created by QtCreator 2020-09-29T12:16:23
#
#-------------------------------------------------

QT       += core gui charts sql datavisualization uitools concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Donut
TEMPLATE = app

#PRECOMPILED_HEADER = /home/rklasky/workspaceQtCreator/Donut/precompiled_header.h
#CONFIG += precompile_header
pisc
# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
QMAKE_CXXFLAGS += -std=c++0x

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++14

LIBS += -lboost_system -lboost_filesystem

SOURCES += \
        main.cpp \
        nmfMainWindow.cpp

HEADERS += \
    mainpage.h \
    nmfMainWindow.h \
    precompiled_header.h

FORMS += \
    nmfMainWindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    qdarkstyle/style.qrc \
    resource.qrc


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../build-nmfUtilities-Qt_5_12_3_gcc64-Release/release/ -lnmfUtilities
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../build-nmfUtilities-Qt_5_12_3_gcc64-Release/debug/ -lnmfUtilities
else:unix: LIBS += -L$$PWD/../../build-nmfUtilities-Qt_5_12_3_gcc64-Release/ -lnmfUtilities

INCLUDEPATH += $$PWD/../../nmfSharedUtilities/nmfUtilities
DEPENDPATH += $$PWD/../../nmfSharedUtilities/nmfUtilities

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../build-nmfCharts-Qt_5_12_3_gcc64-Release/release/ -lnmfCharts
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../build-nmfCharts-Qt_5_12_3_gcc64-Release/debug/ -lnmfCharts
else:unix: LIBS += -L$$PWD/../../build-nmfCharts-Qt_5_12_3_gcc64-Release/ -lnmfCharts

INCLUDEPATH += $$PWD/../../nmfSharedUtilities/nmfCharts
DEPENDPATH += $$PWD/../../nmfSharedUtilities/nmfCharts

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../build-Donut_GuiSetup-Qt_5_12_3_gcc64-Release/release/ -lDonut_GuiSetup
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../build-Donut_GuiSetup-Qt_5_12_3_gcc64-Release/debug/ -lDonut_GuiSetup
else:unix: LIBS += -L$$PWD/../../build-Donut_GuiSetup-Qt_5_12_3_gcc64-Release/ -lDonut_GuiSetup

INCLUDEPATH += $$PWD/../Donut_GuiSetup
DEPENDPATH += $$PWD/../Donut_GuiSetup

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../build-Donut_ModelAPI-Qt_5_12_3_gcc64-Release/release/ -lDonut_ModelAPI
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../build-Donut_ModelAPI-Qt_5_12_3_gcc64-Release/debug/ -lDonut_ModelAPI
else:unix: LIBS += -L$$PWD/../../build-Donut_ModelAPI-Qt_5_12_3_gcc64-Release/ -lDonut_ModelAPI

INCLUDEPATH += $$PWD/../Donut_ModelAPI
DEPENDPATH += $$PWD/../Donut_ModelAPI
