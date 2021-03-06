
#ifndef UNITEFFECT_H
#define UNITEFFECT_H

#include <QtGlobal>

#include <config/engine_traits.h>

/*!
 * \brief Class used to represent effects in units during a battle
 */
class UnitEffect {

public:

    using HealthType = Traits<Unit>::HealthType;
    using AttackType = Traits<Unit>::AttackType;
    using SpeedType = Traits<Unit>::SpeedType;

    virtual ~UnitEffect();

    /*!
     * \brief Virtual method that is called each time a unit turn ends
     * \param u Unit that will be affected by the effect
     * \param duration_left Turns remaining until the effect wears off
     */
    virtual void doTurnEffect(Unit *u, UIntegerType duration_left) const { Q_UNUSED(u); Q_UNUSED(duration_left); }

    /*!
     * \brief Virtual method that is called each time the unit with this effect attack other
     * \param att The unit attacking(The one with the effect)
     * \param def The unit defending
     * \param a The damage amount
     * \return The damage amount after this effect is applied
     */
    virtual AttackType doAttackEffect(Unit *att, Unit *def, AttackType a) const { Q_UNUSED(att); Q_UNUSED(def); return a; }

    /*!
     * \brief Virtual method taht is called each time the unit with the effect is attacked
     * \param def The unit defending(The one with the effect)
     * \param att The object attacking
     * \param a The damage amount
     * \return The damage amount after this effect is applied
     */
    virtual AttackType doDefenseEffect(Unit *def, EngineObject *att, AttackType a) const {

        Q_UNUSED(def); Q_UNUSED(att); return a;
    }

    virtual SpeedType doSpeedEffect(const Unit *u, SpeedType speed) const { Q_UNUSED(u); return speed; }
};

#endif // UNITEFFECT_H
