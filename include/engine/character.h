
#ifndef CHARACTER_H
#define CHARACTER_H

#include <utility>
#include <string>

#include <config/types.h>

/*!
 * \brief Class meant to hold information about a character
 */
class Character {

public:

    struct Attributes;

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
    UIntegerType experienceNeeded() const { return (level()*level())*25; }

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

            _attr.stats[stat]++;
            _free_points--;
        }
    }

    /*!
     * \brief Save the information of this character
     */
    void save() const;

    /*!
     * \brief Struct that represents the attributes of a character
     */
    struct Attributes {

        enum class Stat : UIntegerType { strength, vitality, dexterity, agility };

        /*!
         * \brief Return the quantity of stats
         * \return The quantity of stats
         */
        static constexpr UIntegerType statsCount() { return sizeof(stats)/sizeof(stats[0]); }

        bool operator<(const Attributes& other) const {

            for(UIntegerType i = 0; i < statsCount(); i++) {

                if(this->stats[i] != other.stats[i]) return this->stats[i] < other.stats[i];
            }

            return false;
        }

        UIntegerType& strength() { return stats[0]; }
        const UIntegerType& strength() const { return stats[0]; }

        UIntegerType& vitality() { return stats[1]; }
        const UIntegerType& vitality() const { return stats[1]; }

        UIntegerType& dexterity() { return stats[2]; }
        const UIntegerType& dexterity() const { return stats[2]; }

        UIntegerType& agility() { return stats[3]; }
        const UIntegerType& agility() const { return stats[3]; }

        UIntegerType stats[4];
    };

private:

    void _calculate_free_points_and_experience();

    void _calculate_level() {

        _level = _attr.strength() + _attr.vitality() + _attr.agility() + _attr.dexterity() + _free_points;
    }

    std::string _name;
    std::string _char_class;

    UIntegerType _level;
    UIntegerType _free_points;
    UIntegerType _experience;
    Attributes _attr;
};

#endif // CHARACTER_H
