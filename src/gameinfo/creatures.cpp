
#include <animation/animationfactories/unit/monsterfloweranimationfactory.h>
#include <animation/animationfactories/unit/coloredslimeanimationfactory.h>
#include <animation/animationfactories/unit/slimeanimationfactory.h>
#include <engine/controllers/ai/slime.h>
#include <engine/controllers/ai/crazy.h>
#include <engine/controllers/ai/timidslime.h>
#include <engine/controllers/ai/pacifistslime.h>
#include <engine/controllers/ai/monsterplant.h>
#include <engine/unitsinfo/slime.h>
#include <engine/unitsinfo/monsterplant.h>
#include <gameinfo/creatures.h>

#include "animationfactories/unit/zuanimationfactory.h"
#include "engine/controllers/ai/zucontroller.h"
#include "engine/unitsinfo/zu.h"

using namespace gameinfo;

std::map<std::string, Creatures::GetCreatureFunctionType> Creatures::_creatures;

std::optional<Creatures::Info> Creatures::get(const std::string& name) {

    if(_creatures.empty()) _init();

    auto func_it = _creatures.find(name);

    if(func_it == _creatures.end()) return std::nullopt;

    return (func_it->second)();
}

static Creatures::Info _get_slime_info() {

    return Creatures::Info(unitsinfo::Slime::getInfo(),
                           unitanimationfactory::SlimeAnimationFactory::getFactory(),
                           controller::AI::Slime::getController(), {{"arrow", 70}});
}

static Creatures::Info _get_blue_slime_info() {

    return Creatures::Info(unitsinfo::Slime::getInfo(unitsinfo::Slime::Type::Fast),
                           unitanimationfactory::ColoredSlimeAnimationFactory::getFactory(Qt::cyan),
                           controller::AI::Slime::getController());
}

static Creatures::Info _get_purple_slime_info() {

    return Creatures::Info(unitsinfo::Slime::getInfo(unitsinfo::Slime::Type::Immortal),
                           unitanimationfactory::ColoredSlimeAnimationFactory::getFactory(Qt::magenta),
                           controller::AI::Slime::getController());
}

static Creatures::Info _get_orange_slime_info() {

    return Creatures::Info(unitsinfo::Slime::getInfo(unitsinfo::Slime::Type::Crazy),
                           unitanimationfactory::ColoredSlimeAnimationFactory::getFactory(QColor(255, 150, 0)),
                           controller::AI::Crazy::getController());
}

static Creatures::Info _get_white_slime_info() {

    return Creatures::Info(unitsinfo::Slime::getInfo(unitsinfo::Slime::Type::Ghost),
                           unitanimationfactory::ColoredSlimeAnimationFactory::getFactory(Qt::white),
                           controller::AI::Slime::getController());
}

static Creatures::Info _get_yellow_slime_info() {

    return Creatures::Info(unitsinfo::Slime::getInfo(unitsinfo::Slime::Type::Normal),
                           unitanimationfactory::ColoredSlimeAnimationFactory::getFactory(Qt::yellow),
                           controller::AI::TimidSlime::getController(), {{"sword", 70}});
}

static Creatures::Info _get_pink_slime_info() {

    return Creatures::Info(unitsinfo::Slime::getInfo(unitsinfo::Slime::Type::Normal),
                           unitanimationfactory::ColoredSlimeAnimationFactory::getFactory(QColor(255, 153, 255)),
                           controller::AI::PacifistSlime::getController());
}

static Creatures::Info _get_monster_plant_info() {

    return Creatures::Info(unitsinfo::MonsterPlant::getInfo(),
                           unitanimationfactory::MonsterFlowerAnimationFactory::getFactory(),
                           controller::AI::MonsterPlant::getController());
}

static Creatures::Info _get_zu_info() {

    return Creatures::Info(unitsinfo::Zu::getInfo(),
                           unitanimationfactory::ZuAnimationFactory::getFactory(),
                           controller::AI::ZuController::getController());
}

void Creatures::_init() {

    _creatures["slime"] = _get_slime_info;
    _creatures["blue slime"] = _get_blue_slime_info;
    _creatures["purple slime"] = _get_purple_slime_info;
    _creatures["orange slime"] = _get_orange_slime_info;
    _creatures["white slime"] = _get_white_slime_info;
    _creatures["yellow slime"] = _get_yellow_slime_info;
    _creatures["pink slime"] = _get_pink_slime_info;
    _creatures["monster plant"] = _get_monster_plant_info;
    _creatures["zu"] = _get_zu_info;
}
