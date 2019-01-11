
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_CXXFLAGS += -std=c++17
LIBS += -lstdc++fs

INCLUDEPATH += include include/animation include/config include/interface \
    include/engine include/utils include/utility include/memory include/gameinfo

TARGET = SGOM
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += object_parallel_to_source c++1z
OBJECTS_DIR = .

SOURCES += src/main.cpp \
    src/interface/mainwindow.cpp \
    src/engine/unitbase.cpp \
    src/animation/animation.cpp \
    src/interface/battlewidget.cpp \
    src/animation/animatedobject.cpp \
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
    src/interface/graphicsview.cpp \
    src/engine/effects/regeneration.cpp \
    src/utility/random.cpp \
    src/memory/memorymanager.cpp \
    src/gameinfo/creatures.cpp \
    src/gameinfo/jobs.cpp \
    src/interface/battlewidget_inputmanager.cpp \
    src/config/sgomfiles.cpp \
    src/interface/selectuserinterface.cpp \
    src/engine/character.cpp \
    src/interface/gamedefaultscreen.cpp \
    src/gameinfo/maps/greenvalley.cpp \
    src/interface/characterinfodialog.cpp \
    src/engine/skills/teleport.cpp \
    src/engine/unitsinfo/ninja.cpp \
    src/engine/effects/lastescape.cpp \
    src/engine/skills/onofflastescape.cpp \
    src/interface/selectjobdialog.cpp \
    src/utility/imagecolorchange.cpp \
    src/engine/controllers/ai/crazy.cpp \
    src/engine/controllers/ai/timidslime.cpp \
    src/gameinfo/maps/trainingground.cpp \
    src/engine/controllers/ai/pacifistslime.cpp \
    src/engine/unitsinfo/knight.cpp \
    src/interface/librarywidget.cpp \
    src/animation/partialimageitem.cpp \
    src/engine/effects/adrenaline.cpp \
    src/engine/skills/rage.cpp \
    src/engine/unitsinfo/monsterplant.cpp \
    src/engine/skills/plantareaattack.cpp \
    src/engine/controllers/ai/monsterplant.cpp \
    src/engine/unitskill.cpp \
    src/engine/uniteffect.cpp \
    src/engine/unitcontroller.cpp \
    src/memory/genericmemorymanager.cpp \
    src/engine/engineobjectbase.cpp \
    src/engine/engineobject.cpp \
    src/engine/projectile.cpp \
    src/engine/projectiles/basicprojectile.cpp \
    src/animation/animationfactories/unit/coloredslimeanimationfactory.cpp \
    src/animation/animationfactories/unit/fighteranimationfactory.cpp \
    src/animation/animationfactories/unit/knightanimationfactory.cpp \
    src/animation/animationfactories/unit/monsterfloweranimationfactory.cpp \
    src/animation/animationfactories/unit/ninjaanimationfactory.cpp \
    src/animation/animationfactories/unit/slimeanimationfactory.cpp \
    src/animation/animationitens/unit/basicunitgraphicitem.cpp \
    src/interface/characterselectionscreen.cpp \
    src/interface/imagewidget.cpp \
    src/animation/animationfactories/projectile/arrowanimationfactory.cpp \
    src/gameinfo/projectiles.cpp \
    src/animation/animationfactories/unit/archeranimationfactory.cpp \
    src/engine/skills/shoot.cpp \
    src/engine/enginemap.cpp \
    src/animation/animationfactories/projectile/magicmissilefactory.cpp \
    src/animation/animationfactories/unit/mageanimationfactory.cpp \
    src/engine/skills/magicmissile.cpp \
    src/animation/animationfactories/projectile/fireballanimationfactory.cpp \
    src/engine/skills/fireball.cpp \
    src/engine/skills/explosion.cpp \
    src/engine/skills/mageonoffmagicshield.cpp \
    src/interface/librarywidgetinfotab.cpp \
    src/interface/configurationscreen.cpp \
    src/interface/selectuserinterfacebase.cpp \
    src/engine/projectiles/missile.cpp \
    src/engine/skills/knightblock.cpp \
    src/animation/animationfactories/unit/zuanimationfactory.cpp \
    src/engine/unitattributes.cpp \
    src/engine/unitsinfo/zu.cpp \
    src/engine/controllers/ai/zucontroller.cpp \
    src/gameinfo/maps/cave.cpp \
    src/animation/animationfactories/projectile/shurikenanimationfactory.cpp \
    src/gameinfo/items.cpp \
    src/interface/itemsview.cpp \
    src/interface/itemimagewidget.cpp

HEADERS += include/interface/mainwindow.h \
    include/engine/unitbase.h \
    include/engine/unitinfo.h \
    include/config/types.h \
    include/config/traits.h \
    include/animation/animation.h \
    include/engine/unit.h \
    include/interface/battlewidget.h \
    include/animation/animatedobject.h \
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
    include/interface/graphicsview.h \
    include/animation/unitanimationitemfactory.h \
    include/animation/animatedobject.h \
    include/animation/animation.h \
    include/animation/animationhandler.h \
    include/animation/progressbaritem.h \
    include/animation/unitanimationitem.h \
    include/animation/unitanimationitemfactory.h \
    include/animation/animatedobject.h \
    include/animation/animation.h \
    include/animation/animationhandler.h \
    include/animation/progressbaritem.h \
    include/animation/unitanimationitem.h \
    include/animation/unitanimationitemfactory.h \
    include/engine/uniteffect.h \
    include/engine/effects/regeneration.h \
    include/utility/interval.h \
    include/utility/imagecolorchange.h \
    include/utility/random.h \
    include/memory/onecopymemorymanager.h \
    include/memory/memorymanager.h \
    include/memory/onecopymemorymanagerbasic.h \
    include/gameinfo/creatures.h \
    include/gameinfo/jobs.h \
    include/interface/mainwidget.h \
    include/interface/battlewidget_inputmanager.h \
    include/interface/gamedefaultscreen.h \
    include/interface/selectuserinterface.h \
    include/config/sgomfiles.h \
    include/engine/character.h \
    include/gameinfo/creaturemap.h \
    include/utility/randomvalues.h \
    include/gameinfo/maps/greenvalley.h \
    include/interface/characterinfodialog.h \
    include/engine/skills/teleport.h \
    include/engine/unitsinfo/ninja.h \
    include/engine/effects/lastescape.h \
    include/engine/skills/onofflastescape.h \
    include/interface/selectjobdialog.h \
    include/engine/controllers/ai/crazy.h \
    include/engine/controllers/ai/timidslime.h \
    include/gameinfo/maps/trainingground.h \
    include/engine/controllers/ai/pacifistslime.h \
    include/engine/unitsinfo/knight.h \
    include/interface/librarywidget.h \
    include/animation/partialimageitem.h \
    include/engine/effects/adrenaline.h \
    include/engine/skills/rage.h \
    include/engine/unitsinfo/monsterplant.h \
    include/engine/skills/plantareaattack.h \
    include/engine/controllers/ai/monsterplant.h \
    include/memory/singleobject.h \
    include/memory/genericmemorymanager.h \
    include/memory/simplememorymanager.h \
    include/engine/engineobjectbase.h \
    include/engine/engineobject.h \
    include/engine/projectile.h \
    include/engine/projectilefactory.h \
    include/engine/projectiles/basicprojectile.h \
    include/animation/projectileanimationitem.h \
    include/animation/animationitembase.h \
    include/animation/projectileanimationitemfactory.h \
    include/animation/animationfactories/unit/fighteranimationfactory.h \
    include/animation/animationfactories/unit/coloredslimeanimationfactory.h \
    include/animation/animationfactories/unit/knightanimationfactory.h \
    include/animation/animationfactories/unit/monsterfloweranimationfactory.h \
    include/animation/animationfactories/unit/slimeanimationfactory.h \
    include/animation/animationfactories/unit/ninjaanimationfactory.h \
    include/animation/animationitens/unit/basicunitgraphicitem.h \
    include/animation/animationitens/projectile/basicprojectilegraphicitem.h \
    include/interface/selectuserinterfacebase.h \
    include/interface/characterselectionscreen.h \
    include/interface/imagewidget.h \
    include/animation/animationfactories/projectile/arrowanimationfactory.h \
    include/engine/projectilefactories/basicprojectilefactory.h \
    include/gameinfo/projectiles.h \
    include/engine/unitsinfo/archer.h \
    include/animation/animationfactories/unit/archeranimationfactory.h \
    include/engine/skills/shoot.h \
    include/engine/projectiles/missile.h \
    include/engine/enginemap.h \
    include/engine/projectilefactories/missilefactory.h \
    include/animation/animationfactories/projectile/magicmissilefactory.h \
    include/engine/unitsinfo/mage.h \
    include/animation/animationfactories/unit/mageanimationfactory.h \
    include/engine/skills/magicmissile.h \
    include/animation/animationfactories/projectile/fireballanimationfactory.h \
    include/engine/skills/fireball.h \
    include/engine/skills/explosion.h \
    include/engine/effects/magicshield.h \
    include/engine/skills/mageonoffmagicshield.h \
    include/interface/librarywidgetinfotab.h \
    include/interface/configurationscreen.h \
    include/engine/effects/shield.h \
    include/engine/skills/knightblock.h \
    include/animation/animationfactories/unit/zuanimationfactory.h \
    include/engine/unitsinfo/zu.h \
    include/engine/unitattributes.h \
    include/engine/controllers/ai/zucontroller.h \
    include/gameinfo/maps/cave.h \
    include/animation/animationfactories/projectile/shurikenanimationfactory.h \
    include/gameinfo/items.h \
    include/interface/itemsview.h \
    include/interface/itemimagewidget.h \
    include/utility/iteratorwrapper.h

RESOURCES += img/images.qrc \
    data/data.qrc

FORMS += forms/gamedefaultscreen.ui \
    forms/menu.ui \
    forms/selectuserinterface.ui \
    forms/characterinfodialog.ui \
    forms/selectjobdialog.ui \
    forms/battlewidget.ui \
    forms/helpwidget.ui \
    forms/librarywidget.ui \
    forms/characterselectionscreen.ui \
    forms/librarywidgetinfotab.ui \
    forms/configurationscreen.ui \
    forms/itemsview.ui

run.depends = $$TARGET
run.commands = ./$$TARGET

QMAKE_EXTRA_TARGETS = run

target.path = /usr/local/bin

desktop.path = /usr/share/applications
desktop.files += SGOM.desktop

desktopicon.path = /usr/share/icons/
desktopicon.files += SGOM-icon.png

INSTALLS += target desktop desktopicon

