
#include "animation/animationfactories/projectile/arrowanimationfactory.h"
#include "engine/projectilefactories/basicprojectilefactory.h"
#include "gameinfo/projectiles.h"

using namespace gameinfo;

std::map<std::string, Projectiles::GetProjectileFunctionType> Projectiles::_projectiles;

std::optional<Projectiles::Info> Projectiles::get(std::string name, const ProjectileInfo& p_info) {

    if(_projectiles.empty()) _init();

    auto func_it = _projectiles.find(name);

    if(func_it == _projectiles.end()) return std::nullopt;

    return (func_it->second)(p_info);
}

static Projectiles::Info _get_arrow(const Projectiles::ProjectileInfo& p_info) {

    return Projectiles::Info(projectilefactory::BasicProjectileFactory::getFactory(
                                 p_info.durability, p_info.size, p_info.speed, p_info.damage),
                             projectileanimationfactory::ArrowAnimationFactory::getFactory());
}

void Projectiles::_init() {

    _projectiles["arrow"] = _get_arrow;
}
