
#include <gameinfo/skills.h>

#include "engine/skillfactories/genericskillfactory.h"
#include "engine/skills/basicattack.h"

using namespace gameinfo;

std::map<std::string, Skills::GetSkillFunctionType> Skills::_skills;

std::optional<Skills::Info> Skills::get(const std::string& name) {

    if(_skills.empty()) _init();

    auto func_it = _skills.find(name);

    if(func_it == _skills.end()) return std::nullopt;

    return (func_it->second)();
}

static Skills::Info _get_basic_attack() {

    static skillfactory::GenericSkillFactory<skill::BasicAttack> factory;

    return Skills::Info(&factory, QPixmap(":/sword_image.png"));
}

void Skills::_init() {

    _skills["basic attack"] = _get_basic_attack;
}
