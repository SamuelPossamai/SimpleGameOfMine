
#ifndef SLIMEANIMATIONFACTORY_H
#define SLIMEANIMATIONFACTORY_H

#include <unitanimationitemfactory.h>

namespace unitanimationfactory {

class SlimeAnimationFactory : public UnitAnimationItemFactory {

public:

    virtual UnitAnimationItem *create(Unit *) override;

    static SlimeAnimationFactory *getFactory();

private:

    static Animation _slime_animation;
    static Animation _slime_attack_animation;
    static SlimeAnimationFactory *_factory;
};

} /* namespace unitanimationfactory */

#endif // SLIMEANIMATIONFACTORY_H
