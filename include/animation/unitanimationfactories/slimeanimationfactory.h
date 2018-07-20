
#ifndef SLIMEANIMATIONFACTORY_H
#define SLIMEANIMATIONFACTORY_H

#include "unitanimationitemfactory.h"

namespace unitanimationfactory {

class SlimeAnimationFactory : public UnitAnimationItemFactory {

public:

    virtual ~SlimeAnimationFactory() {}

    virtual UnitAnimationItem *create(Unit *) override;

    static SlimeAnimationFactory *getFactory();

protected:

    SlimeAnimationFactory();

    Animation slimeNormalAnimation;
    Animation slimeAttackAnimation;

private:

    static SlimeAnimationFactory *_factory;
};

} /* namespace unitanimationfactory */

#endif // SLIMEANIMATIONFACTORY_H
