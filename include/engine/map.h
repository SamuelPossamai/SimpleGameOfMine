
#ifndef MAP_H
#define MAP_H

#include <vector>

#include "engine_traits.h"

/*!
 * \brief This class is used to manage the position of the units in the engine
 */
class Map {

public:

    using PointType = Traits<Map>::PointType;
    using PositionType = Traits<Map>::PositionType;
    using AngleType = Traits<Map>::AngleType;
    using UnitsVector = std::vector<Unit *>;
    using ConstUnitsVector = std::vector<const Unit *>;

    /*!
     * \brief Creates a map passing it's the size as parameter
     * \param width Width of the region where the units can be
     * \param height Height of the region where the units can be
     */
    Map(PositionType width, PositionType height) : _width(width), _height(height) {}

    /*!
     * \brief Verify if there is only units from one team, if so this team won
     * \return true if a team won and the game is over, false otherwise
     */
    bool gameEndVerify() const;

    /*!
     * \brief Add an unit to the map
     * \param unit Unit that will be added to the map
     * \sa removeUnit(Unit *), units(), unitAccess(UIntegerType)
     */
    void addUnit(Unit *unit);

    /*!
     * \brief Remove an unit from the map and it's id will be taken by the last unit in the map
     * \param unit Unit that will be removed from the map
     * \sa addUnit(Unit *), units(), unitAccess(UIntegerType)
     */
    void removeUnit(Unit *unit);

    UnitsVector unitsInRange(PointType p, PositionType range);
    UnitsVector unitsInRange(PointType p, PositionType range, AngleType angle, AngleType region_angle);
    UnitsVector unitsInLine(PointType p, PositionType range, AngleType angle);

    void unitsInRange(UnitsVector& vector, PointType p, PositionType range);
    void unitsInRange(UnitsVector& vector, PointType p, PositionType range, AngleType angle, AngleType region_angle);
    void unitsInLine(UnitsVector& vector, PointType p, PositionType range, AngleType angle);

    /*!
     * \brief This method returns the enemy closer to an especific unit
     * \return if there is an enemy return the close one otherwise return nullptr
     */
    Unit *closerEnemy(const Unit *);
    const Unit *closerEnemy(const Unit *u) const { return const_cast<Map *>(this)->closerEnemy(u); }

    /*!
     * \brief Access an unit with the id 'n', the id is not fixed, it can be changed by a call to removeUnit(Unit *)
     * \param n Number of the unit that will be accessed
     * \sa removeUnit(Unit *), addUnit(Unit *), units()
     * \return Unit with the id 'n'
     */
    Unit *unitAccess(UIntegerType n) { return _units[n]; }
    const Unit *unitAccess(UIntegerType n) const { return _units[n]; }

    /*!
     * \brief Returns how many number of units there are in the map
     * \return The number of units in the map
     */
    UIntegerType units() const { return _units.size(); }

    /*!
     * \brief This method verify if 'p' is a valid position for an unit 'u'
     * \param u Unit that want to move
     * \param p Position where the unit want to move to
     * \return true if it's a valid position, false otherwise
     */
    bool unitMoveVerify(Unit *u, const PointType& p);

    /*!
     * \brief Change the position of all the units so it will start in valid places that can be basedon the team
     */
    void placeUnits();

    /*!
     * \brief Calculate the distance between two units
     * \return The distance between two units
     */
    static RealType unitsDistance(const Unit *, const Unit *);

    const PositionType& width() const { return _width; }
    const PositionType& height() const { return _height; }

private:

    static RealType _units_squared_distance(const Unit *, const Unit *);
    static constexpr bool _using_radians() { return Traits<Map>::angle_unit == Traits<Map>::AngleUnitType::radians; }

    static bool _inside_region(AngleType a1, AngleType r1, AngleType a2, AngleType r2);

    PositionType _width, _height;

    UnitsVector _units;
};

#endif // MAP_H
