
#ifndef ARCHERANIMATIONFACTORY_H
#define ARCHERANIMATIONFACTORY_H

#include "unitanimationitemfactory.h"
#include "animation.h"

namespace unitanimationfactory {

class ArcherAnimationFactory : public UnitAnimationItemFactory {

    ArcherAnimationFactory();

public:

    virtual UnitAnimationItem *create(Unit *) override;

    static ArcherAnimationFactory *getFactory();

private:

    Animation _walking_animation;
    Animation _idle_animation;
    Animation _attacking_animation;
    Animation _shoot_animation;
    static ArcherAnimationFactory *_factory;
};

} /* namespace unitanimationfactory */

#endif // ARCHERANIMATIONFACTORY_H
