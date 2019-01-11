
#ifndef MAGICMISSILE_H
#define MAGICMISSILE_H

#include <animation/animation.h>

#include "projectileanimationitemfactory.h"

namespace projectileanimationfactory {

class MagicMissileFactory : public ProjectileAnimationItemFactory {

public:

    virtual ~MagicMissileFactory() override {}

    virtual ProjectileAnimationItem *create(Projectile *) override;

    static MagicMissileFactory *getFactory();

protected:

    MagicMissileFactory();

    Animation missileAnimation;

private:

    static MagicMissileFactory *_factory;
};

} /* namespace projectileanimationfactory */

#endif // MAGICMISSILE_H
