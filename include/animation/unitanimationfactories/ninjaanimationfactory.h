
#ifndef NINJAANIMATIONFACTORY_H
#define NINJAANIMATIONFACTORY_H

#include "unitanimationitemfactory.h"
#include "animation.h"

namespace unitanimationfactory {

class NinjaAnimationFactory : public UnitAnimationItemFactory {

    NinjaAnimationFactory();

public:

    virtual UnitAnimationItem *create(Unit *) override;

    static NinjaAnimationFactory *getFactory();

private:

    Animation _walking_animation;
    Animation _idle_animation;
    Animation _attacking_animation;
    static NinjaAnimationFactory *_factory;
};

} /* namespace unitanimationfactory */

#endif // NINJAANIMATIONFACTORY_H
