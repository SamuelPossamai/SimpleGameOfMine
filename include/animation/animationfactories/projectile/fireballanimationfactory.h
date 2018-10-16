
#ifndef FIREBALLANIMATIONFACTORY_H
#define FIREBALLANIMATIONFACTORY_H

#include <animation/animation.h>

#include "projectileanimationitemfactory.h"

namespace projectileanimationfactory {

class FireballAnimationFactory : public ProjectileAnimationItemFactory {

public:

    virtual ~FireballAnimationFactory() {}

    virtual ProjectileAnimationItem *create(Projectile *) override;

    static FireballAnimationFactory *getFactory();

protected:

    FireballAnimationFactory();

    Animation fireballAnimation;

private:

    static FireballAnimationFactory *_factory;
};

} /* namespace projectileanimationfactory */

#endif // FIREBALLANIMATIONFACTORY_H
