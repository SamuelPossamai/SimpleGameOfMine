
#include <unittypes/jobs.h>

#include "unitsinfo/fighter.h"
#include "unitsinfo/ninja.h"
#include "unitanimationfactories/fighteranimationfactory.h"
#include "unitanimationfactories/ninjaanimationfactory.h"

std::map<std::string, Jobs::GetJobFunctionType> Jobs::_jobs;

std::optional<Jobs::Info> Jobs::get(std::string name, const Attributes& attr) {

    if(_jobs.empty()) _init();

    auto func_it = _jobs.find(name);

    if(func_it == _jobs.end()) return std::nullopt;

    return (func_it->second)(attr);
}

static Jobs::Info _get_fighter_info(const Jobs::Attributes& attr) {

    return Jobs::Info(unitsinfo::Fighter::getInfo(attr),
                      unitanimationfactory::FighterAnimationFactory::getFactory());
}

static Jobs::Info _get_ninja_info(const Jobs::Attributes& attr) {

    return Jobs::Info(unitsinfo::Ninja::getInfo(attr),
                      unitanimationfactory::NinjaAnimationFactory::getFactory());
}

void Jobs::_init() {

    _jobs["fighter"] = _get_fighter_info;
    _jobs["ninja"] = _get_ninja_info;
}
