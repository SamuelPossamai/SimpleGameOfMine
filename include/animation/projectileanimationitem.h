
#ifndef PROJECTILEANIMATIONITEM_H
#define PROJECTILEANIMATIONITEM_H

#include "config/types.h"

#include "projectile.h"
#include "animationitembase.h"

class ProjectileAnimationItem : public AnimationItemBase {

public:

    ProjectileAnimationItem(Projectile *p) : AnimationItemBase(p) {}

    virtual ~ProjectileAnimationItem() override {}

protected:

    const Projectile *projectile() const { return static_cast<const Projectile *>(object()); }
};

#endif // PROJECTILEANIMATIONITEM_H
