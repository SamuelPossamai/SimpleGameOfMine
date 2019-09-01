
#ifndef ARROWANIMATIONFACTORY_H
#define ARROWANIMATIONFACTORY_H

#include <animation/animation.h>

#include "projectileanimationitemfactory.h"

namespace projectileanimationfactory {

class ArrowAnimationFactory : public ProjectileAnimationItemFactory {

public:

    virtual ~ArrowAnimationFactory() override {}

    virtual ProjectileAnimationItem *create(Projectile *) override;

    static ArrowAnimationFactory *getFactory();

protected:

    ArrowAnimationFactory();

    Animation arrowAnimation;

private:

    static ArrowAnimationFactory *_factory;
};

} /* namespace projectileanimationfactory */

#endif // ARROWANIMATIONFACTORY_H
