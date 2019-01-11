
#ifndef CHARACTER_H
#define CHARACTER_H

#include <optional>
#include <string>
#include <map>

#include <config/types.h>

#include "unitattributes.h"

/*!
 * \brief Class meant to hold information about a character
 */
class Character {

public:

    using Attributes = UnitAttributes;

    static constexpr UIntegerType freePointsPerLevel() { return UnitAttributes::freePointsPerLevel(); }

    /*!
     * \brief Contruct an invalid Character object
     */
    Character() : _name(), _char_class("jobless"), _level(0), _free_points(0),
        _experience(0), _attr({}) {}

    /*!
     * \brief Construct a Character object passing the character name
     * \param char_name Character name
     */
    Character(std::string char_name);

    /*!
     * \brief Create a new character, the information of the new character will be saved
     * \param name Name of the character that will be created
     * \param job Job of the character that will be added
     * \return The just created character
     */
    static Character newChar(std::string name, std::string job);

    /*!
     * \brief Return the attributes of this character
     * \return The attributes of this character
     */
    const Attributes& attributes() const { return _attr; }

    /*!
     * \brief Return the level of the character
     * \return The level of the character
     */
    const UIntegerType& level() const { return _level; }

    /*!
     * \brief Return the name of the character
     * \return The name of the character
     */
    const std::string& name() const { return _name; }

    /*!
     * \brief Change the class/job of the character
     * \param class_name The new class/job of the character
     */
    void setClass(const std::string& class_name) { _char_class = class_name; }

    /*!
     * \brief Return the name of the character's class/job
     * \return The name of the character's class/job
     */
    const std::string& className() const { return _char_class; }

    /*!
     * \brief Increase the amount of experience the character, it may increase the level
     * \param xp The experience amount
     */
    void receiveExperience(UIntegerType xp) { _experience += xp; _calculate_free_points_and_experience(); }

    /*!
     * \brief Return the number of free points the character has
     * \return The number of free points the character has
     */
    UIntegerType freePoints() const { return _free_points; }

    /*!
     * \brief Return the amount of experience needed to level up
     * \return The amount of experience needed to level up
     */
    UIntegerType experienceNeeded() const { return (level()*level())*12; }

    /*!
     * \brief Return the current experience
     * \return The current experience
     */
    UIntegerType experience() const { return _experience; }

    /*!
     * \brief Assign one free point, if there are free points left
     * \param stat The id of the stat that the point will be assing to
     */
    void assignPoint(UIntegerType stat) {

        if(stat < _attr.statsCount() && _free_points) {

            _attr.assignPoint(stat);
            _free_points--;
        }
    }

    /*!
     * \brief Save the information of this character
     */
    void save() const;

    /*!
     * \brief The amount of items of type 'type' will be increased by 'qtd'
     * \param type Name of the type of items that will be added
     * \param qtd Quantity of items added, by default 1
     */
    void addItem(const std::string& type, UIntegerType qtd = 1) { _items[type] += qtd; }

    /*!
     * \brief The amount of items of type 'type' will decreased by 'qtd'
     * \brief if the current amount is lower than 'qtd', the current amount will be set to zero
     * \param type Name of the type of items that will be added
     * \param qtd Quantity of items removed, by default 1
     * \return The number of items removed
     */
    UIntegerType remItem(const std::string& type, UIntegerType qtd = 1);

    /*!
     * \brief Verify if the character owns at least 'qtd' items of type 'type'
     * \param type Name of the type of items
     * \param qtd Quantity of items it need, by default 1
     * \return true if it does have enough items of type 'type', false otherwise
     */
    bool haveItem(const std::string& type, UIntegerType qtd = 1) {

        auto it = _items.find(type);
        if(it == _items.end()) return false;

        return it->second >= qtd;
    }

    /*!
     * \brief Return the amount of items of type 'type'
     * \param type Name of the type of items
     * \return The current amount of items of type 'type'
     */
    UIntegerType searchItem(const std::string& type) const {

        auto it = _items.find(type);
        if(it == _items.end()) return 0;
        return it->second;
    }

    /*!
     * \brief Access the items owned by the character
     * \return A map with the type of the item as key and the amount of items with this type as value
     */
    const std::map<std::string, UIntegerType>& items() const { return _items; }

private:

    void _load_items(const std::map<std::string, std::string>& items);
    void _calculate_free_points_and_experience();
    std::optional<UIntegerType> _get_int(const std::string&);

    std::string _name;
    std::string _char_class;

    UIntegerType _level;
    UIntegerType _free_points;
    UIntegerType _experience;
    Attributes _attr;

    std::map<std::string, UIntegerType> _items;
};

#endif // CHARACTER_H
