
#ifndef ENGINEOBJECTBASE_H
#define ENGINEOBJECTBASE_H

#include <engine_traits.h>

/*!
 * \brief Class with the basic information about an engine object
 * \sa EngineObject
 */
class EngineObjectBase {

public:

    using PointType = Traits<Unit>::PointType;

    using PositionType = Traits<Unit>::PositionType;
    using AngleType = Traits<Unit>::AngleType;
    using SizeType = Traits<Unit>::SizeType;
    using SpeedType = Traits<Unit>::SpeedType;

    EngineObjectBase(SizeType s, SpeedType sp, PointType pos = {0, 0}, AngleType angle = 0) :
        _x(pos.x), _y(pos.y), _angle(angle), _size(s), _speed(sp) {}

    virtual ~EngineObjectBase();

    /*!
     * \brief Set the 'x' position of this object
     * \param x The value the 'x' position of this object will be
     * \sa x(), setPos(PointType), setPos(PositionType, PositionType), setY(PositionType)
     */
    void setX(PositionType x) { _x = x; }

    /*!
     * \brief Return the 'x' position of this object
     * \return The 'x' position of this object
     * \sa y(), pos(), setY(PositionType)
     */
    PositionType x() const { return _x; }

    /*!
     * \brief Set the 'y' position of this object
     * \param y The value the 'y' position of this object will be
     * \sa y(), setPos(PointType), setPos(PositionType, PositionType), setX(PositionType)
     */
    void setY(PositionType y) { _y = y; }

    /*!
     * \brief Return the 'y' position of this object
     * \return The 'y' position of this object
     * \sa x(), pos(), setY(PositionType)
     */
    PositionType y() const { return _y; }

    /*!
     * \brief Set the position of the object
     * \param x The 'x' position
     * \param y The 'y' position
     * \sa pos(), setPos(PointType), setX(PositionType), setY(PositionType)
     */
    void setPos(PositionType x, PositionType y) { _x = x; _y = y;  }

    /*!
     * \brief Set the position of the object
     * \sa pos(), setPos(PositionType, PositionType), setX(PositionType), setY(PositionType)
     * \param p The new position of the object
     */
    void setPos(PointType p) { setPos(p.x, p.y); }

    /*!
     * \brief Return the current position of this object
     * \sa setPos(PointType), setPos(PositionType, PositionType), setX(PositionType), setY(PositionType)
     * \return The position of the object
     */
    PointType pos() const { return { x(), y() }; }

    /*!
     * \brief Set the angle of this object
     * \sa angle()
     * \param angle Angle in radians that this object will have, 0 is faced right and rotate in clockwise diretion
     */
    void setAngle(AngleType angle);

    /*!
     * \brief Return the current angle of the object
     * \sa setAngle(AngleType)
     * \return The current angle of the object
     */
    AngleType angle() const { return _angle; }

    /*!
     * \brief Return the size of the object in the engine
     * \return The object's size, it does not represent it's graphical size, but the size in the engine
     */
    SizeType size() const { return _size; }

    /*!
     * \brief Return the speed of the object in the engine
     * \return The object's speed, it will determine how often the object acts
     */
    SpeedType speed() const { return _speed; }

protected:

    void setSize(SizeType size) { _size = size; }
    void setSpeed(SpeedType speed) { _speed = speed; }

private:

    PositionType _x, _y;
    AngleType _angle;

    SizeType _size;
    SpeedType _speed;
};

#endif // ENGINEOBJECTBASE_H
