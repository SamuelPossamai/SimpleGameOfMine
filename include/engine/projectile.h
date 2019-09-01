
#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <limits>

#include <QtGlobal>

#include "engineobject.h"

class Projectile : public EngineObject {

public:

    using DamageType = Traits<Unit>::AttackType;

    Projectile(Map *m, const Unit *creator, AngleType dir, UIntegerType dur,
               SizeType s, SpeedType sp, PointType pos = {0, 0}, AngleType angle = 0) :
        EngineObject(m, s, sp, pos, angle), _to_next_action(1), _dir(dir), _durability(dur), _creator(creator) {}

    virtual ~Projectile() override {}

    /*!
     * \brief This method will do the action for projectile
     * The 'act()' method for an object of 'Projectile' class will move the projectile for a small amount
     * and will verify the engine map, if it detects any colision will call collideAction
     * \return true if the projectile is not destroyed in the action, false otherwise
     */
    bool act() final;

    /*!
     * \brief Set the angle of the projectile velocity
     * \param angle The projectile will now go to this angle
     */
    void setDirection(AngleType angle) { _dir = angle; }

    /*!
     * \brief Destroy the projectile and remove it from the map
     */
    void destroy() { _durability = 0; map()->removeObject(this); }

    /*!
     * \brief Decrease the durability value of the projectile, if it reaches zero the projectile will be destroyed
     * \param v The amount of durability that will be reduced
     * \sa destroy(), durability()
     * \return false if it's destroyed, true otherwise
     */
    bool decreaseDurability(UIntegerType v) {

        if(v >= _durability){

            destroy();
            return false;
        }

        _durability -= v;
        return true;
    }

    /*!
     * \brief Return the value of the durability of the projectile, if it reaches zero, the projectile is destroyed
     * \return Durability of the projectile
     */
    UIntegerType durability() const { return _durability; }

    /*!
     * \brief Return the unit that created the projectile, if no unit created it, return null pointer
     * \return Unit that created this projectile or null pointer
     */
    const Unit *creator() const { return _creator; }

    /*!
     * \brief Method to be implemented if the projectile should do something after some time
     * \return After how many acts this method must be called again, by default a very big value
     */
    virtual UIntegerType stepAction() { return std::numeric_limits<UIntegerType>::max(); }

    /*!
     * \brief Method called when the projectile collides with something, by default does nothing
     * \param m EngineMap where the collision occurs
     * \param obj The object that is colliding with the projectile
     */
    virtual void collideAction(EngineMap *m, EngineObject *obj) { Q_UNUSED(m); Q_UNUSED(obj); }

private:

    UIntegerType _to_next_action;
    AngleType _dir;

    UIntegerType _durability;
    const Unit * const _creator;
};

#endif // PROJECTILE_H
