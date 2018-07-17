#ifndef UNITBASE_H
#define UNITBASE_H

#include "unitinfo.h"

/*!
 * \brief Class for the basic info that an unit engine have
 * \sa UnitInfo, Unit
 */
class UnitBase {

public:

    using PointType = Traits<Unit>::PointType;

    using HealthType = Traits<Unit>::HealthType;
    using AttackType = Traits<Unit>::AttackType;
    using DefenseType = Traits<Unit>::DefenseType;

    using PositionType = Traits<Unit>::PositionType;
    using AngleType = Traits<Unit>::AngleType;
    using SizeType = Traits<Unit>::SizeType;
    using SpeedType = Traits<Unit>::SpeedType;

    /*!
     * \brief Construct an UnitBase passing UnitInfo, UnitInfo must be valid
     * \param info UnitInfo with the basic information of the type of this unit
     */
    explicit UnitBase(const UnitInfo *info);

    /*!
     * \brief Return the UnitInfo associated with this object
     * \return The UnitInfo of this unit type
     */
    const UnitInfo *unitInfo() const { return _info; }

    /*!
     * \brief Set the 'x' position of this unit
     * \param x The value the 'x' position of this unit will be
     * \sa x(), setPos(PointType), setPos(PositionType, PositionType), setY(PositionType)
     */
    void setX(PositionType x) { _x = x; }

    /*!
     * \brief Return the 'x' position of this unit
     * \return The 'x' position of this unit
     * \sa y(), pos(), setY(PositionType)
     */
    PositionType x() const { return _x; }

    /*!
     * \brief Set the 'y' position of this unit
     * \param y The value the 'y' position of this unit will be
     * \sa y(), setPos(PointType), setPos(PositionType, PositionType), setX(PositionType)
     */
    void setY(PositionType y) { _y = y; }

    /*!
     * \brief Return the 'y' position of this unit
     * \return The 'y' position of this unit
     * \sa x(), pos(), setY(PositionType)
     */
    PositionType y() const { return _y; }

    /*!
     * \brief Set the position of the unit
     * \param x The 'x' position
     * \param y The 'y' position
     * \sa pos(), setPos(PointType), setX(PositionType), setY(PositionType)
     */
    void setPos(PositionType x, PositionType y) { _x = x; _y = y;  }

    /*!
     * \brief Set the position of the unit
     * \sa pos(), setPos(PositionType, PositionType), setX(PositionType), setY(PositionType)
     * \param p The new position of the unit
     */
    void setPos(PointType p) { setPos(p.x, p.y); }

    /*!
     * \brief Return the current position of this unit
     * \sa setPos(PointType), setPos(PositionType, PositionType), setX(PositionType), setY(PositionType)
     * \return The position of the unit
     */
    PointType pos() const { return { x(), y() }; }

    /*!
     * \brief Set the angle of this unit
     * \sa angle()
     * \param angle Angle in radians that this unit will have, 0 is faced right and rotate in clockwise diretion
     */
    void setAngle(AngleType angle);

    /*!
     * \brief Return the current angle of the unit
     * \sa setAngle(AngleType)
     * \return The current angle of the unit
     */
    AngleType angle() const;

    /*!
     * \brief Return the size of the unit in the engine
     * \return The unit's size, it does not represent it's graphical size, but the size in the engine
     */
    SizeType size() const { return _info->size(); }

    /*!
     * \brief Set a value to the health of the unit
     * \param health The health the unit will have
     * \sa health()
     */
    void setHealth(HealthType health);

    /*!
     * \brief Return the amount of health the unit have
     * \return The value of health of the unit
     */
    HealthType health() const { return _health; }

    /*!
     * \brief Return the max amount of healht the unit can have
     * \return The max value for health this unit can have
     */
    HealthType maxHealth() const { return _info->health(); }

private:

    static constexpr bool _using_radians();

    const UnitInfo *_info;
    SizeType _size;

    HealthType _health;

    PositionType _x, _y;
    AngleType _angle;
};

#endif // UNITBASE_H
