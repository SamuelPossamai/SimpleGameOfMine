
#ifndef GAMEINFO_PROJECTILES_H
#define GAMEINFO_PROJECTILES_H

#include <map>
#include <tuple>
#include <optional>

#include <config/types.h>
#include <engine/projectile.h>

namespace gameinfo {

class Projectiles {

public:

    using Info = std::tuple<ProjectileFactory *, ProjectileAnimationItemFactory *>;

    struct ProjectileInfo  {

        virtual ~ProjectileInfo() = default;

        UIntegerType durability;
        Projectile::SizeType size;
        Projectile::SpeedType speed;
        Projectile::DamageType damage;
    };

    static std::optional<Info> get(std::string name, const ProjectileInfo& p_info);

private:

    using GetProjectileFunctionType = Info (*)(const ProjectileInfo&);

    static void _init();

    static std::map<std::string, GetProjectileFunctionType> _projectiles;
};

} /* namespace gameinfo */

#endif // GAMEINFO_PROJECTILES_H
