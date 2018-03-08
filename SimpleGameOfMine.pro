
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_CXXFLAGS += -std=c++17

INCLUDEPATH += include include/animation include/config include/interface include/engine include/utils

TARGET = SGOM
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += object_parallel_to_source

SOURCES += src/main.cpp \
    src/interface/mainwindow.cpp \
    src/engine/unitbase.cpp \
    src/animation/animation.cpp \
    src/interface/battlewidget.cpp \
    src/animation/animatedobject.cpp \
    src/engine/map.cpp \
    src/engine/battleengine.cpp \
    src/engine/unitinfo.cpp \
    src/engine/skills/testskill.cpp \
    src/engine/controllers/human.cpp \
    src/engine/unit.cpp \
    src/engine/skills/walk.cpp \
    src/interface/menu.cpp \
    src/animation/animationhandler.cpp \
    src/engine/skills/evade.cpp \
    src/engine/skills/thrust.cpp \
    src/interface/battleview.cpp \
    src/engine/controllers/ai/slime.cpp \
    src/engine/creatures/slime.cpp \
    src/interface/helpwidget.cpp \
    src/engine/unitcontroller.cpp

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
    include/engine/battleengine.h \
    include/engine/unitskill.h \
    include/engine/unitcontroller.h \
    include/engine/skills/testskill.h \
    include/engine/controllers/human.h \
    include/interface/idbutton.h \
    include/interface/battleview.h \
    include/engine/skills/walk.h \
    include/interface/menu.h \
    include/config/engine_traits.h \
    include/config/interface_traits.h \
    include/animation/animationhandler.h \
    include/engine/skills/evade.h \
    include/engine/skills/thrust.h \
    include/engine/controllers/ai/slime.h \
    include/engine/creatures/slime.h \
    include/interface/helpwidget.h

run.depends = $$TARGET
run.commands = ./$$TARGET

QMAKE_EXTRA_TARGETS = run

RESOURCES += \
    img/images.qrc
