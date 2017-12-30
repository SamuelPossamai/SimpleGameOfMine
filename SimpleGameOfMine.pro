
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_CXXFLAGS += -std=c++17

INCLUDEPATH += include include/animation include/config include/interface include/engine include/utils

TARGET = SGOM
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += src/main.cpp \
    src/interface/mainwindow.cpp \
    src/engine/unitbase.cpp \
    src/animation/animation.cpp \
    src/interface/battlewidget.cpp \
    src/animation/animatedobject.cpp \
    src/engine/map.cpp \
    src/engine/battleengine.cpp

HEADERS += include/interface/mainwindow.h \
    include/engine/unitbase.h \
    include/engine/unitinfo.h \
    include/config/types.h \
    include/config/traits.h \
    include/animation/animation.h \
    include/engine/unit.h \
    include/interface/battlewidget.h \
    include/animation/animatedobject.h \
    include/engine/map.h \
    include/engine/battleengine.h

run.depends = $$TARGET
run.commands = ./$$TARGET

QMAKE_EXTRA_TARGETS = run

RESOURCES += \
    img/images.qrc
