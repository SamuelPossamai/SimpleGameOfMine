
#include <animation/unitanimationfactories/monsterfloweranimationfactory.h>
#include <animation/unitanimationfactories/coloredslimeanimationfactory.h>
#include <animation/unitanimationfactories/slimeanimationfactory.h>
#include <engine/controllers/ai/slime.h>
#include <engine/controllers/ai/crazy.h>
#include <engine/controllers/ai/timidslime.h>
#include <engine/controllers/ai/pacifistslime.h>
#include <engine/controllers/ai/monsterplant.h>
#include <engine/unitsinfo/slime.h>
#include <engine/unitsinfo/monsterplant.h>
#include <unittypes/creatures.h>

std::map<std::string, Creatures::GetCreatureFunctionType> Creatures::_creatures;

std::optional<Creatures::Info> Creatures::get(std::string name, UIntegerType level) {

    if(_creatures.empty()) _init();

    auto func_it = _creatures.find(name);

    if(func_it == _creatures.end()) return std::nullopt;

    return (func_it->second)(level);
}

static Creatures::Info _get_slime_info(UIntegerType level) {

    return Creatures::Info(unitsinfo::Slime::getInfo(level),
                           unitanimationfactory::SlimeAnimationFactory::getFactory(),
                           controller::AI::Slime::getController());
}

static Creatures::Info _get_blue_slime_info(UIntegerType level) {

    return Creatures::Info(unitsinfo::Slime::getInfo(level, unitsinfo::Slime::Type::Fast),
                           unitanimationfactory::ColoredSlimeAnimationFactory::getFactory(Qt::cyan),
                           controller::AI::Slime::getController());
}

static Creatures::Info _get_purple_slime_info(UIntegerType level) {

    return Creatures::Info(unitsinfo::Slime::getInfo(level, unitsinfo::Slime::Type::Immortal),
                           unitanimationfactory::ColoredSlimeAnimationFactory::getFactory(Qt::magenta),
                           controller::AI::Slime::getController());
}

static Creatures::Info _get_orange_slime_info(UIntegerType level) {

    return Creatures::Info(unitsinfo::Slime::getInfo(level, unitsinfo::Slime::Type::Crazy),
                           unitanimationfactory::ColoredSlimeAnimationFactory::getFactory(QColor(255, 150, 0)),
                           controller::AI::Crazy::getController());
}

static Creatures::Info _get_white_slime_info(UIntegerType level) {

    return Creatures::Info(unitsinfo::Slime::getInfo(level, unitsinfo::Slime::Type::Ghost),
                           unitanimationfactory::ColoredSlimeAnimationFactory::getFactory(Qt::white),
                           controller::AI::Slime::getController());
}

static Creatures::Info _get_yellow_slime_info(UIntegerType level) {

    return Creatures::Info(unitsinfo::Slime::getInfo(level, unitsinfo::Slime::Type::Normal),
                           unitanimationfactory::ColoredSlimeAnimationFactory::getFactory(Qt::yellow),
                           controller::AI::TimidSlime::getController());
}

static Creatures::Info _get_pink_slime_info(UIntegerType level) {

    return Creatures::Info(unitsinfo::Slime::getInfo(level, unitsinfo::Slime::Type::Normal),
                           unitanimationfactory::ColoredSlimeAnimationFactory::getFactory(QColor(255, 153, 255)),
                           controller::AI::PacifistSlime::getController());
}

static Creatures::Info _get_monster_plant_info(UIntegerType level) {

    return Creatures::Info(unitsinfo::MonsterPlant::getInfo(level),
                           unitanimationfactory::MonsterFlowerAnimationFactory::getFactory(),
                           controller::AI::MonsterPlant::getController());
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
}
