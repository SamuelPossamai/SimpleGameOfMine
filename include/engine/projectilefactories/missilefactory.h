
#ifndef PROJECTILEFACTORY_MISSILEFACTORY_H
#define PROJECTILEFACTORY_MISSILEFACTORY_H

#include <memory/genericmemorymanager.h>

#include "gameinfo/projectiles.h"
#include "projectiles/missile.h"
#include "basicprojectilefactory.h"

namespace projectilefactory {

class MissileFactory : public BasicProjectileFactory {

    MissileFactory(UIntegerType dur, Projectile::SizeType size, Projectile::SpeedType speed,
                   Projectile::DamageType damage, Projectile::AngleType ang_speed) :
        BasicProjectileFactory(dur, size, speed, damage), _ang_speed(ang_speed) {}

public:

    struct MissileInfo : gameinfo::Projectiles::ProjectileInfo {

        virtual ~MissileInfo() override = default;

        Projectile::AngleType angular_speed;
    };

    static MissileFactory *getFactory(UIntegerType dur, Projectile::SizeType size,
                                      Projectile::SpeedType speed, Projectile::DamageType damage,
                                      Projectile::AngleType ang_speed) {

        return static_cast<MissileFactory *>(getObjCopy(MissileFactory(dur, size, speed, damage, ang_speed)));
    }

    virtual ~MissileFactory() override = default;

    virtual Projectile *create(Map *m, const Unit *creator, Projectile::AngleType dir,
                               Projectile::PointType pos, Projectile::AngleType angle) override {

        return new projectile::Missile(m, creator, dir, projDurability(), projSize(), projSpeed(),
                                       projDamage(), _ang_speed, pos, angle);
    }

protected:

    virtual bool manObjLessCompare(const GenericMemoryManagerManagedObject *m) const override {

        auto *other = static_cast<const MissileFactory *>(m);

        if(this->_ang_speed != other->_ang_speed) return this->_ang_speed < other->_ang_speed;

        return BasicProjectileFactory::manObjLessCompare(m);
    };

    virtual GenericMemoryManagerManagedObject *manObjClone() const override {

        return new MissileFactory(projDurability(), projSize(), projSpeed(), projDamage(), _ang_speed);
    }

private:

    const Projectile::AngleType _ang_speed;
};

} /* namespace projectilefactory */

#endif // PROJECTILEFACTORY_MISSILEFACTORY_H
