
#ifndef CHARACTER_H
#define CHARACTER_H

#include <optional>
#include <string>

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

private:

    void _calculate_free_points_and_experience();
    std::optional<UIntegerType> _get_int(const std::string&);

    std::string _name;
    std::string _char_class;

    UIntegerType _level;
    UIntegerType _free_points;
    UIntegerType _experience;
    Attributes _attr;
};

#endif // CHARACTER_H
