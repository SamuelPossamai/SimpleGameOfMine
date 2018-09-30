
#ifndef MAP_H
#define MAP_H

#include <vector>

#include "engine_traits.h"

/*!
 * \brief This class is used to manage the position of the objects in the engine
 */
class Map {

public:

    using PointType = Traits<Map>::PointType;
    using PositionType = Traits<Map>::PositionType;
    using AngleType = Traits<Map>::AngleType;
    using UnitsVector = std::vector<Unit *>;
    using ConstUnitsVector = std::vector<const Unit *>;
    using EngineObjectsVector = std::vector<EngineObject *>;
    using ConstEngineObjectsVector = std::vector<const EngineObject *>;

    /*!
     * \brief Creates a map passing it's the size as parameter
     * \param width Width of the region where the objects can be
     * \param height Height of the region where the objects can be
     */
    Map(PositionType width, PositionType height) : _width(width), _height(height), _pending(nullptr) {}

    /*!
     * \brief Verify if there is only objects from one team, if so this team won
     * \return true if a team won and the game is over, false otherwise
     */
    bool gameEndVerify() const;

    /*!
     * \brief Add an object to the map, if it's an Unit it will call addUnit(Unit *)
     * \param object object that will be added to the map
     * \sa removeObject(EngineObject *), objectsNumber(), objectAccess(UIntegerType)
     */
    void addObject(EngineObject *object);

    void addObjectPending(EngineObject *object) { _pending = object; }

    void resolvePendings() {

        if(_pending) {

            addObject(_pending);
            _pending = nullptr;
        }
    }

    /*!
     * \brief Add an object to the map
     * \param object object that will be added to the map
     * \sa addObject(EngineObject *), removeObject(EngineObject *), objectsNumber(), objectAccess(UIntegerType)
     */
    void addObjectNotUnit(EngineObject *object) { _objects.push_back(object); }

    /*!
     * \brief Add an unit to the map
     * \param unit unit that will be added to the map
     * \sa removeObject(Unit *), objectsNumber(), objectAccess(UIntegerType)
     */
    void addUnit(Unit *unit);

    /*!
     * \brief Remove an object from the map
     * \param object EngineObject that will be removed from the map
     * \sa addObject(EngineObject *), objectsNumber(), unitAccess(UIntegerType)
     */
    void removeObject(EngineObject *object);

    EngineObjectsVector objectsInRange(PointType p, PositionType range);
    UnitsVector unitsInRange(PointType p, PositionType range);

    EngineObjectsVector objectsInRange(PointType p, PositionType range, AngleType angle, AngleType region_angle);

    /// \todo This method was not implemented
    EngineObjectsVector objectsInLine(PointType p, PositionType range, AngleType angle);

    void objectsInRange(EngineObjectsVector& vector, PointType p, PositionType range);
    void unitsInRange(UnitsVector& vector, PointType p, PositionType range);

    void objectsInRange(EngineObjectsVector& vector, PointType p, PositionType range, AngleType angle, AngleType region_angle);

    /// \todo This method was not implemented
    void objectsInLine(EngineObjectsVector& vector, PointType p, PositionType range, AngleType angle);

    /*!
     * \brief This method returns the enemy closer to an especific object
     * \param u This mehtod will find the closer enemy to this unit
     * \return if there is an enemy return the close one otherwise return nullptr
     */
    Unit *closerEnemy(const Unit *u);
    const Unit *closerEnemy(const Unit *u) const { return const_cast<Map *>(this)->closerEnemy(u); }

    /*!
     * \brief Access an object with the id 'n', the id is not fixed, it can be changed by a removal
     * \param n Number of the object that will be accessed
     * \sa removeObject(EngineObject *), addObject(EngineObject *), objectsNumber()
     * \return EngineObject with the id 'n'
     */
    EngineObject *objectAccess(UIntegerType n) { return _objects[n]; }
    const EngineObject *objectAccess(UIntegerType n) const { return _objects[n]; }

    /*!
     * \brief Returns how many number of objects there are in the map
     * \return The number of objects in the map
     */
    UIntegerType objectsNumber() const { return _objects.size(); }

    /*!
     * \brief Access an unit with the id 'n', the id is not fixed, it can be changed by a removal
     * \param n Number of the unit that will be accessed
     * \sa removeUnit(Unit *), addUnit(Unit *), unitsNumber()
     * \return Unit with the id 'n'
     */
    Unit *unitAccess(UIntegerType n) { return _units[n]; }
    const Unit *unitAccess(UIntegerType n) const { return _units[n]; }

    /*!
     * \brief Returns how many number of units there are in the map
     * \return The number of units in the map
     */
    UIntegerType unitsNumber() const { return _units.size(); }

    /*!
     * \brief This method verify if 'p' is a valid position for an unit 'u'
     * \param obj EngineObject that want to move
     * \param p Position where the object want to move to
     * \return true if it's a valid position, false otherwise
     */
    bool engineObjectMoveVerify(EngineObject *obj, const PointType& p);

    /*!
     * \brief Change the position of all the units so it will start in valid places that can be basedon the team
     */
    void placeUnits();

    /*!
     * \brief Calculate the distance between two objects
     * \return The distance between two objects
     */
    static RealType objectsDistance(const EngineObject *, const EngineObject *);

    const PositionType& width() const { return _width; }
    const PositionType& height() const { return _height; }

private:

    static RealType _objects_squared_distance(const EngineObject *, const EngineObject *);

    static bool _inside_region(AngleType a1, AngleType r1, AngleType a2, AngleType r2);

    template<typename T>
    void _in_range_base(std::vector<T *>& src, std::vector<T *>& dest, PointType p, PositionType range);

    template<typename T>
    static bool _remove_from_vector(std::vector<T *>& v, T *obj);

    PositionType _width, _height;

    EngineObject *_pending;
    EngineObjectsVector _objects;
    UnitsVector _units;
};

#endif // MAP_H
