
#ifndef PROJECTILEANIMATIONITEMFACTORY_H
#define PROJECTILEANIMATIONITEMFACTORY_H

#include <config/types.h>

/*!
 * \brief Abstract class to create ProjectileAnimationItem objects
 * \sa ProjectileAnimationItem
 */
class ProjectileAnimationItemFactory {

public:

    virtual ~ProjectileAnimationItemFactory() {}

    /*!
     * \brief Create an UnitAnimationItem, the item cerated will depend on the derived implementation of this method
     * \param u Unit that will be observed by the UnitAnimationItem
     * \sa UnitAnimationItem, Unit
     * \return The UnitAnimationItem object that was created
     */
    virtual ProjectileAnimationItem *create(Projectile *u) = 0;
};

#endif // PROJECTILEANIMATIONITEMFACTORY_H
