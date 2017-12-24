
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_CXXFLAGS += -std=c++17

INCLUDEPATH += include

TARGET = SGOM
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += src/main.cpp \
    src/mainwindow.cpp \
    src/unitbase.cpp \
    src/animation.cpp

HEADERS += include/mainwindow.h \
    include/unitbase.h \
    include/unitinfo.h \
    include/types.h \
    include/traits.h \
    include/animation.h

run.depends = $$TARGET
run.commands = ./$$TARGET

QMAKE_EXTRA_TARGETS = run

RESOURCES += \
    img/images.qrc
