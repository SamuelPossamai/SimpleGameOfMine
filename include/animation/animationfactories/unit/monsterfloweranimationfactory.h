
#ifndef MONSTERFLOWERANIMATIONFACTORY_H
#define MONSTERFLOWERANIMATIONFACTORY_H

#include "animation.h"

#include "unitanimationitemfactory.h"

namespace unitanimationfactory {

class MonsterFlowerAnimationFactory : public UnitAnimationItemFactory {

    MonsterFlowerAnimationFactory();

public:

    virtual UnitAnimationItem *create(Unit *) override;

    static MonsterFlowerAnimationFactory *getFactory() {

        if(!_factory) _factory = new MonsterFlowerAnimationFactory;
        return _factory;
    }

private:

    Animation _idle_animation;
    Animation _walking_animation;
    Animation _attacking_animation;
    static MonsterFlowerAnimationFactory *_factory;
};

} /* namespace unitanimationfactory */

#endif // MONSTERFLOWERANIMATIONFACTORY_H
