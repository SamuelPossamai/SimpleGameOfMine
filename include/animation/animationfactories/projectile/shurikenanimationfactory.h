
#ifndef SHURIKENANIMATIONFACTORY_H
#define SHURIKENANIMATIONFACTORY_H

#include <animation/animation.h>

#include "projectileanimationitemfactory.h"

namespace projectileanimationfactory {

class ShurikenAnimationFactory : public ProjectileAnimationItemFactory {

public:

    virtual ~ShurikenAnimationFactory() override {}

    virtual ProjectileAnimationItem *create(Projectile *) override;

    static ShurikenAnimationFactory *getFactory();

protected:

    ShurikenAnimationFactory();

    Animation shurikenAnimation;

private:

    static ShurikenAnimationFactory *_factory;
};

} /* namespace projectileanimationfactory */

#endif // SHURIKENANIMATIONFACTORY_H
