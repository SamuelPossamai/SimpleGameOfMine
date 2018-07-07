
#ifndef FIGHTERANIMATIONFACTORY_H
#define FIGHTERANIMATIONFACTORY_H

#include <unitanimationitemfactory.h>

namespace unitanimationfactory {

class FighterAnimationFactory : public UnitAnimationItemFactory {

public:

    virtual UnitAnimationItem *create(Unit *) override;

    static FighterAnimationFactory *getFactory();

private:

    static Animation _walking_animation;
    static Animation _idle_animation;
    static Animation _attacking_animation;
    static FighterAnimationFactory *_factory;
};

} /* namespace unitanimationfactory */

#endif // FIGHTERANIMATIONFACTORY_H
