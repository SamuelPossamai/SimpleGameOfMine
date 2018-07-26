
#include <animation/unitanimationfactories/coloredslimeanimationfactory.h>
#include <animation/unitanimationfactories/slimeanimationfactory.h>
#include <engine/controllers/ai/slime.h>
#include <engine/unitsinfo/slime.h>
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


void Creatures::_init() {

    _creatures["slime"] = _get_slime_info;
    _creatures["blue slime"] = _get_blue_slime_info;
    _creatures["purple slime"] = _get_purple_slime_info;
}
