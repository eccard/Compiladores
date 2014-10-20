
QT       += core gui widgets
TEMPLATE = app
#CONFIG += console
CONFIG += qt gui
#CONFIG -= app_bundle


SOURCES += \
    src/compilador.cpp \
    src/Arvore.cpp \
    src/simbolo.cpp

#include(deployment.pri)
#qtcAddDeployment()

OTHER_FILES += \
    src/file.lug \
    src/file2.lug \
    src/file3.lug
TARGET = Arvore_sintática
DESTDIR = $$PWD

HEADERS += \
    src/constants.h \
    src/Arvore.h \
    src/simbolo.h

FORMS    +=
