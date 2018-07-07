
#ifndef UNITANIMATIONITEMFACTORY_H
#define UNITANIMATIONITEMFACTORY_H

#include <types.h>

/*!
 * \brief Abstract class to create UnitAnimationItem objects
 * \sa UnitAnimationItem
 */
class UnitAnimationItemFactory {

public:

    /*!
     * \brief Create an UnitAnimationItem, the item cerated will depend on the derived implementation of this method
     * \param u Unit that will be observed by the UnitAnimationItem
     * \sa UnitAnimationItem, Unit
     * \return The UnitAnimationItem object that was created
     */
    virtual UnitAnimationItem *create(Unit *u) = 0;
};

#endif // UNITANIMATIONITEMFACTORY_H
