
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_CXXFLAGS += -std=c++17
LIBS += -lstdc++fs

INCLUDEPATH += include include/animation include/config include/interface include/engine include/utils include/utility include/memory

TARGET = SGOM
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += object_parallel_to_source
OBJECTS_DIR = .

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
    src/utility/random.cpp \
    src/memory/memorymanager.cpp \
    src/unittypes/creatures.cpp \
    src/unittypes/jobs.cpp \
    src/interface/battlewidget_inputmanager.cpp \
    src/config/sgomfiles.cpp \
    src/interface/selectuserinterface.cpp \
    src/engine/character.cpp \
    src/interface/gamedefaultscreen.cpp \
    src/unittypes/maps/greenvalley.cpp \
    src/animation/unitanimationfactories/coloredslimeanimationfactory.cpp \
    src/interface/characterinfodialog.cpp \
    src/engine/skills/teleport.cpp \
    src/animation/unitanimationfactories/ninjaanimationfactory.cpp \
    src/engine/unitsinfo/ninja.cpp \
    src/engine/effects/lastescape.cpp \
    src/engine/skills/onofflastescape.cpp \
    src/interface/selectjobdialog.cpp \
    src/utility/imagecolorchange.cpp \
    src/engine/controllers/ai/crazy.cpp \
    src/engine/controllers/ai/timidslime.cpp \
    src/unittypes/maps/trainingground.cpp \
    src/engine/controllers/ai/pacifistslime.cpp \
    src/animation/unitanimationfactories/knightanimationfactory.cpp \
    src/engine/unitsinfo/knight.cpp \
    src/interface/librarywidget.cpp \
    src/animation/partialimageitem.cpp \
    src/engine/effects/adrenaline.cpp \
    src/engine/skills/rage.cpp

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
    include/engine/character.h \
    include/unittypes/creaturemap.h \
    include/utility/randomvalues.h \
    include/unittypes/maps/greenvalley.h \
    include/animation/unitanimationfactories/coloredslimeanimationfactory.h \
    include/interface/characterinfodialog.h \
    include/engine/skills/teleport.h \
    include/animation/unitanimationfactories/ninjaanimationfactory.h \
    include/engine/unitsinfo/ninja.h \
    include/engine/effects/lastescape.h \
    include/engine/skills/onofflastescape.h \
    include/interface/selectjobdialog.h \
    include/engine/controllers/ai/crazy.h \
    include/engine/controllers/ai/timidslime.h \
    include/unittypes/maps/trainingground.h \
    include/engine/controllers/ai/pacifistslime.h \
    include/animation/unitanimationfactories/knightanimationfactory.h \
    include/engine/unitsinfo/knight.h \
    include/interface/librarywidget.h \
    include/animation/partialimageitem.h \
    include/engine/effects/adrenaline.h \
    include/engine/skills/rage.h

RESOURCES += img/images.qrc

FORMS += forms/gamedefaultscreen.ui \
    forms/menu.ui \
    forms/selectuserinterface.ui \
    forms/characterinfodialog.ui \
    forms/selectjobdialog.ui \
    forms/battlewidget.ui \
    forms/helpwidget.ui \
    forms/librarywidget.ui

run.depends = $$TARGET
run.commands = ./$$TARGET

QMAKE_EXTRA_TARGETS = run

target.path = /usr/bin

INSTALLS += target

