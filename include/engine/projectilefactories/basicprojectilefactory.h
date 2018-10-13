
#ifndef BASICPROJECTILEFACTORY_H
#define BASICPROJECTILEFACTORY_H

#include <memory/genericmemorymanager.h>

#include "projectiles/basicprojectile.h"
#include "projectilefactory.h"

namespace projectilefactory {

class BasicProjectileFactory : public ProjectileFactory, public GenericMemoryManager::ManagedObject {

    BasicProjectileFactory(UIntegerType dur, Projectile::SizeType size, Projectile::SpeedType speed,
                           Projectile::DamageType damage) : _dur(dur), _size(size), _speed(speed), _damage(damage) {}

public:

    static BasicProjectileFactory *getFactory(UIntegerType dur, Projectile::SizeType size,
                                              Projectile::SpeedType speed, Projectile::DamageType damage) {

        return static_cast<BasicProjectileFactory *>(getObjCopy(BasicProjectileFactory(dur, size, speed, damage)));
    }

    virtual ~BasicProjectileFactory() = default;

    virtual Projectile *create(Map *m, Projectile::AngleType dir, Projectile::PointType pos, Projectile::AngleType angle) {

        return new projectile::BasicProjectile(m, dir, _dur, _size, _speed, _damage, pos, angle);
    }

protected:

    virtual bool manObjLessCompare(const GenericMemoryManagerManagedObject *m) const {

        auto *other = static_cast<const BasicProjectileFactory *>(m);

        if(this->_dur < other->_dur) return true;
        if(this->_size < other->_size) return true;
        if(this->_speed < other->_speed) return true;

        return this->_damage < other->_damage;
    };

    virtual GenericMemoryManagerManagedObject *manObjClone() const {

        return new BasicProjectileFactory(_dur, _size, _speed, _damage);
    }

private:

    UIntegerType _dur;
    Projectile::SizeType _size;
    Projectile::SpeedType _speed;
    Projectile::DamageType _damage;
};

} /* namespace projectilefactory */

#endif // BASICPROJECTILEFACTORY_H
