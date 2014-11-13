
QT       += core gui widgets
TEMPLATE = app
#CONFIG += console
CONFIG += qt gui
#CONFIG -= app_bundle


SOURCES += \
    src/compilador.cpp \
    src/Arvore.cpp \
    src/simbolo.cpp \
    src/simbolotipo.cpp \
    src/simbolofuncao.cpp \
    src/simboloconst.cpp \
    src/simboloparam.cpp

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
    src/simbolo.h \
    src/simbolotipo.h \
    src/simbolofuncao.h \
    src/simboloconst.h \
    src/simboloparam.h

FORMS    +=
