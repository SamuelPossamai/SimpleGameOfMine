
#include <gameinfo/jobs.h>

#include "unitsinfo/fighter.h"
#include "unitsinfo/ninja.h"
#include "unitsinfo/knight.h"
#include "unitsinfo/archer.h"
#include "unitsinfo/mage.h"
#include "animationfactories/unit/archeranimationfactory.h"
#include "animationfactories/unit/fighteranimationfactory.h"
#include "animationfactories/unit/ninjaanimationfactory.h"
#include "animationfactories/unit/knightanimationfactory.h"
#include "animationfactories/unit/mageanimationfactory.h"

using namespace gameinfo;

std::map<std::string, Jobs::GetJobFunctionType> Jobs::_jobs;

std::optional<Jobs::Info> Jobs::get(const std::string& name) {

    if(_jobs.empty()) _init();

    auto func_it = _jobs.find(name);

    if(func_it == _jobs.end()) return std::nullopt;

    return (func_it->second)();
}

static Jobs::Info _get_fighter_info() {

    return Jobs::Info(unitsinfo::Fighter::getInfo(),
                      unitanimationfactory::FighterAnimationFactory::getFactory());
}

static Jobs::Info _get_ninja_info() {

    return Jobs::Info(unitsinfo::Ninja::getInfo(),
                      unitanimationfactory::NinjaAnimationFactory::getFactory());
}

static Jobs::Info _get_knight_info() {

    return Jobs::Info(unitsinfo::Knight::getInfo(),
                      unitanimationfactory::KnightAnimationFactory::getFactory());
}

static Jobs::Info _get_archer_info() {

    return Jobs::Info(unitsinfo::Archer::getInfo(),
                      unitanimationfactory::ArcherAnimationFactory::getFactory());
}

static Jobs::Info _get_mage_info() {

    return Jobs::Info(unitsinfo::Mage::getInfo(),
                      unitanimationfactory::MageAnimationFactory::getFactory());
}

void Jobs::_init() {

    _jobs["fighter"] = _get_fighter_info;
    _jobs["ninja"] = _get_ninja_info;
    _jobs["knight"] = _get_knight_info;
    _jobs["archer"] = _get_archer_info;
    _jobs["mage"] = _get_mage_info;
}
