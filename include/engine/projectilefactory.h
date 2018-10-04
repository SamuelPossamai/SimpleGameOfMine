
#ifndef PROJECTILEFACTORY_H
#define PROJECTILEFACTORY_H

#include "projectile.h"

class ProjectileFactory {

public:

    virtual ~ProjectileFactory() {}

    virtual Projectile *create(Map *, Projectile::AngleType dir, Projectile::PointType pos, Projectile::AngleType angle) = 0;
};

#endif // PROJECTILEFACTORY_H
