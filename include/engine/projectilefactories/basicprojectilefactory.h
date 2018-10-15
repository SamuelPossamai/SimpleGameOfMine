
#ifndef PROJECTILEFACTORY_BASICPROJECTILEFACTORY_H
#define PROJECTILEFACTORY_BASICPROJECTILEFACTORY_H

#include <memory/genericmemorymanager.h>

#include "projectiles/basicprojectile.h"
#include "projectilefactory.h"

namespace projectilefactory {

class BasicProjectileFactory : public ProjectileFactory, public GenericMemoryManager::ManagedObject {

public:

    static BasicProjectileFactory *getFactory(UIntegerType dur, Projectile::SizeType size,
                                              Projectile::SpeedType speed, Projectile::DamageType damage) {

        return static_cast<BasicProjectileFactory *>(getObjCopy(BasicProjectileFactory(dur, size, speed, damage)));
    }

    virtual ~BasicProjectileFactory() override = default;

    virtual Projectile *create(Map *m, const Unit *creator, Projectile::AngleType dir,
                               Projectile::PointType pos, Projectile::AngleType angle) override {

        return new projectile::BasicProjectile(m, creator, dir, _dur, _size, _speed, _damage, pos, angle);
    }

    UIntegerType projDurability() const { return _dur; }

    Projectile::SizeType projSize() const { return _size; }

    Projectile::SpeedType projSpeed() const { return _speed; }

    Projectile::DamageType projDamage() const { return _damage; }

protected:

    BasicProjectileFactory(UIntegerType dur, Projectile::SizeType size, Projectile::SpeedType speed,
                           Projectile::DamageType damage) : _dur(dur), _size(size), _speed(speed), _damage(damage) {}

    virtual bool manObjLessCompare(const GenericMemoryManagerManagedObject *m) const override {

        auto *other = static_cast<const BasicProjectileFactory *>(m);

        if(this->_dur != other->_dur) return this->_dur < other->_dur;
        if(this->_size != other->_size) return this->_size < other->_size;
        if(this->_speed != other->_speed) return this->_speed < other->_speed;

        return this->_damage < other->_damage;
    };

    virtual GenericMemoryManagerManagedObject *manObjClone() const override {

        return new BasicProjectileFactory(_dur, _size, _speed, _damage);
    }

private:

    const UIntegerType _dur;
    const Projectile::SizeType _size;
    const Projectile::SpeedType _speed;
    const Projectile::DamageType _damage;
};

} /* namespace projectilefactory */

#endif // PROJECTILEFACTORY_BASICPROJECTILEFACTORY_H
