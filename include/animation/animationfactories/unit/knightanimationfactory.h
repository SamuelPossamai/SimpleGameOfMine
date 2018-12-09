
#ifndef KNIGHTANIMATIONFACTORY_H
#define KNIGHTANIMATIONFACTORY_H

#include "unitanimationitemfactory.h"
#include "animation.h"

namespace unitanimationfactory {

class KnightAnimationFactory : public UnitAnimationItemFactory {

    KnightAnimationFactory();

public:

    virtual UnitAnimationItem *create(Unit *) override;

    static KnightAnimationFactory *getFactory();

private:

    Animation _walking_animation;
    Animation _idle_animation;
    Animation _attacking_animation;
    Animation _blocking_animation;
    static KnightAnimationFactory *_factory;
};

} /* namespace unitanimationitemfactory */

#endif // KNIGHTANIMATIONFACTORY_H
