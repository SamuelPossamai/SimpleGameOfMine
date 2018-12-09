
#ifndef MAGEANIMATIONFACTORY_H
#define MAGEANIMATIONFACTORY_H

#include "unitanimationitemfactory.h"
#include "animation.h"

namespace unitanimationfactory {

class MageAnimationFactory : public UnitAnimationItemFactory {

    MageAnimationFactory();

public:

    virtual UnitAnimationItem *create(Unit *) override;

    static MageAnimationFactory *getFactory();

private:

    Animation _walking_animation;
    Animation _idle_animation;

    static MageAnimationFactory *_factory;
};

} /* namespace unitanimationfactory */

#endif // MAGEANIMATIONFACTORY_H
