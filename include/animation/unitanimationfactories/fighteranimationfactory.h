
#ifndef FIGHTERANIMATIONFACTORY_H
#define FIGHTERANIMATIONFACTORY_H

#include "unitanimationitemfactory.h"
#include "animation.h"

namespace unitanimationfactory {

class FighterAnimationFactory : public UnitAnimationItemFactory {

    FighterAnimationFactory();

public:

    virtual UnitAnimationItem *create(Unit *) override;

    static FighterAnimationFactory *getFactory();

private:

    Animation _walking_animation;
    Animation _idle_animation;
    Animation _attacking_animation;
    static FighterAnimationFactory *_factory;
};

} /* namespace unitanimationfactory */

#endif // FIGHTERANIMATIONFACTORY_H
