
#ifndef REDSLIMEANIMATIONFACTORY_H
#define REDSLIMEANIMATIONFACTORY_H

#include "unitanimationfactories/slimeanimationfactory.h"

namespace unitanimationfactory {

class RedSlimeAnimationFactory : public SlimeAnimationFactory {

    RedSlimeAnimationFactory();

public:

    virtual UnitAnimationItem *create(Unit *) override;

    static RedSlimeAnimationFactory *getFactory();

private:

    static RedSlimeAnimationFactory *_factory;
};

} /* namespace unitanimationfactory */

#endif // REDSLIMEANIMATIONFACTORY_H
