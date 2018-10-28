
#include <iostream>

#include "animation/animationfactories/projectile/arrowanimationfactory.h"
#include "animation/animationfactories/projectile/magicmissilefactory.h"
#include "animation/animationfactories/projectile/fireballanimationfactory.h"
#include "animation/animationfactories/projectile/shurikenanimationfactory.h"
#include "engine/projectilefactories/missilefactory.h"
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

static Projectiles::Info _get_magic_missile(const Projectiles::ProjectileInfo& p_info_generic) {

    auto p_info = dynamic_cast<const projectilefactory::MissileFactory::MissileInfo *>(&p_info_generic);

    if(p_info == nullptr) {

        std::cout << "Error: Tried to create 'missile' unsuccessfully" << std::endl;

        return { nullptr, nullptr };
    }

    return Projectiles::Info(projectilefactory::MissileFactory::getFactory(
                                 p_info->durability, p_info->size, p_info->speed, p_info->damage, p_info->angular_speed),
                             projectileanimationfactory::MagicMissileFactory::getFactory());
}

static Projectiles::Info _get_fireball(const Projectiles::ProjectileInfo& p_info) {

    return Projectiles::Info(projectilefactory::BasicProjectileFactory::getFactory(
                                 p_info.durability, p_info.size, p_info.speed, p_info.damage),
                             projectileanimationfactory::FireballAnimationFactory::getFactory());
}

static Projectiles::Info _get_shuriken(const Projectiles::ProjectileInfo& p_info) {

    return Projectiles::Info(projectilefactory::BasicProjectileFactory::getFactory(
                                 p_info.durability, p_info.size, p_info.speed, p_info.damage),
                             projectileanimationfactory::ShurikenAnimationFactory::getFactory());
}

void Projectiles::_init() {

    _projectiles["arrow"] = _get_arrow;
    _projectiles["magic missile"] = _get_magic_missile;
    _projectiles["fireball"] = _get_fireball;
    _projectiles["shuriken"] = _get_shuriken;
}
