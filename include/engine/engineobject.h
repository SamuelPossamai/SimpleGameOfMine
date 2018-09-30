
#ifndef ENGINEOBJECT_H
#define ENGINEOBJECT_H

#include "map.h"
#include "engineobjectbase.h"

class EngineObject : public EngineObjectBase {

    using Base = EngineObjectBase;

public:

    EngineObject(const EngineObject&) = delete;

    EngineObject& operator=(const EngineObject&) = delete;

    virtual ~EngineObject() override { _map->removeObject(this); }

    virtual bool act() = 0;

    virtual bool needThreadToAct() { return false; }

    /*!
     * \brief Set the x position of the object if it's possible
     * \param x The new value for x position
     * \return true if it was able to change the position, false otherwise
     */
    bool setX(PositionType x) { return setPos(x, Base::y()); }

    /*!
     * \brief Set the y position of the object if it's possible
     * \param y The new value for y position
     * \return true if it was able to change the position, false otherwise
     */
    bool setY(PositionType y) { return setPos(Base::x(), y); }

    /*!
     * \brief Set the position of the object if it's possible
     * \param x The new value for x position
     * \param y The new value for y position
     * \return true if it was able to change the position, false otherwise
     */
    bool setPos(PositionType x, PositionType y) { return setPos({x, y}); }

    /*!
     * \brief Set the position of the object if it's possible
     * \param p The new position of the object
     * \return true if it was able to change the position, false otherwise
     */
    bool setPos(PointType p);

    /*!
     * \brief Set the object's angle
     * \param angle New angle value, in radians
     * \return Always true
     */
    bool setAngle(AngleType angle);

    SpeedType speed() const = delete;
    SpeedType baseSpeed() const { return Base::speed(); }
    virtual SpeedType effectiveSpeed() const { return Base::speed(); }

protected:

    EngineObject(Map *m, SizeType s, SpeedType sp, PointType pos = {0, 0}, AngleType angle = 0) :
        EngineObjectBase(s, sp, pos, angle), _map(m) {

        m->addObjectPending(this);
    }

    Map *map() const { return _map; }

private:

    Map * const _map;
};

#endif // ENGINEOBJECT_H
