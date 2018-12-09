
#ifndef ZUANIMATIONFACTORY_H
#define ZUANIMATIONFACTORY_H

#include "animation.h"

#include "unitanimationitemfactory.h"

namespace unitanimationfactory {

class ZuAnimationFactory : public UnitAnimationItemFactory {

    ZuAnimationFactory();

public:

    virtual UnitAnimationItem *create(Unit *) override;

    static ZuAnimationFactory *getFactory() {

        if(!_factory) _factory = new ZuAnimationFactory;
        return _factory;
    }

private:

    Animation _idle_animation;
    Animation _walking_animation;
    static ZuAnimationFactory *_factory;
};

} /* namespace unitanimationfactory */

#endif // ZUANIMATIONFACTORY_H
