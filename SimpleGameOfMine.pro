
QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_CXXFLAGS += -std=c++17
LIBS += -lstdc++fs

INCLUDEPATH += include include/animation include/config include/interface include/engine include/utils include/utility include/memory

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
    src/engine/controllers/human.cpp \
    src/engine/unit.cpp \
    src/engine/skills/walk.cpp \
    src/interface/menu.cpp \
    src/animation/animationhandler.cpp \
    src/engine/skills/evade.cpp \
    src/engine/skills/thrust.cpp \
    src/engine/controllers/ai/slime.cpp \
    src/engine/unitsinfo/slime.cpp \
    src/interface/helpwidget.cpp \
    src/engine/unitsinfo/fighter.cpp \
    src/engine/skills/basicattack.cpp \
    src/animation/progressbaritem.cpp \
    src/animation/unitanimations/basicunitgraphicitem.cpp \
    src/interface/graphicsview.cpp \
    src/animation/unitanimationfactories/slimeanimationfactory.cpp \
    src/animation/unitanimationfactories/fighteranimationfactory.cpp \
    src/engine/effects/regeneration.cpp \
    src/animation/unitanimationfactories/redslimeanimationfactory.cpp \
    src/engine/unitsinfo/rslime.cpp \
    src/utility/random.cpp \
    src/memory/memorymanager.cpp \
    src/unittypes/creatures.cpp \
    src/unittypes/jobs.cpp \
    src/interface/battlewidget_inputmanager.cpp \
    src/config/sgomfiles.cpp \
    src/interface/selectuserinterface.cpp \
    src/engine/character.cpp

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
    include/engine/controllers/human.h \
    include/interface/idbutton.h \
    include/engine/skills/walk.h \
    include/interface/menu.h \
    include/config/engine_traits.h \
    include/config/interface_traits.h \
    include/animation/animationhandler.h \
    include/engine/skills/evade.h \
    include/engine/skills/thrust.h \
    include/engine/controllers/ai/slime.h \
    include/engine/unitsinfo/slime.h \
    include/interface/helpwidget.h \
    include/engine/unitsinfo/fighter.h \
    include/engine/skills/basicattack.h \
    include/animation/unitanimationitem.h \
    include/animation/progressbaritem.h \
    include/animation/unitanimations/basicunitgraphicitem.h \
    include/interface/graphicsview.h \
    include/animation/unitanimationitemfactory.h \
    include/animation/unitanimations/basicunitgraphicitem.h \
    include/animation/animatedobject.h \
    include/animation/animation.h \
    include/animation/animationhandler.h \
    include/animation/progressbaritem.h \
    include/animation/unitanimationitem.h \
    include/animation/unitanimationitemfactory.h \
    include/animation/unitanimations/basicunitgraphicitem.h \
    include/animation/animatedobject.h \
    include/animation/animation.h \
    include/animation/animationhandler.h \
    include/animation/progressbaritem.h \
    include/animation/unitanimationitem.h \
    include/animation/unitanimationitemfactory.h \
    include/animation/unitanimationfactories/slimeanimationfactory.h \
    include/animation/unitanimationfactories/fighteranimationfactory.h \
    include/engine/uniteffect.h \
    include/engine/effects/regeneration.h \
    include/utility/interval.h \
    include/utility/imagecolorchange.h \
    include/animation/unitanimationfactories/redslimeanimationfactory.h \
    include/engine/unitsinfo/rslime.h \
    include/utility/random.h \
    include/memory/onecopymemorymanager.h \
    include/engine/unitsinfo/unitclassinfo.h \
    include/memory/memorymanager.h \
    include/memory/onecopymemorymanagerbasic.h \
    include/unittypes/creatures.h \
    include/unittypes/jobs.h \
    include/interface/mainwidget.h \
    include/interface/battlewidget_inputmanager.h \
    include/interface/gamedefaultscreen.h \
    include/interface/selectuserinterface.h \
    include/config/sgomfiles.h \
    include/engine/character.h

run.depends = $$TARGET
run.commands = ./$$TARGET

QMAKE_EXTRA_TARGETS = run

RESOURCES += img/images.qrc
