
#ifndef PROJECTILEANIMATIONITEM_H
#define PROJECTILEANIMATIONITEM_H

#include "config/types.h"

#include "animationitembase.h"

class ProjectileAnimationItem : public AnimationItemBase {

public:

    ProjectileAnimationItem(Projectile *p) : _projectile(p) {}

    virtual ~ProjectileAnimationItem() override {}

protected:

    const Projectile *projectile() const { return _projectile; }

private:

    Projectile *_projectile;
};

#endif // PROJECTILEANIMATIONITEM_H
