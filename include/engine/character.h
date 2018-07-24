
#ifndef CHARACTER_H
#define CHARACTER_H

#include <utility>
#include <string>

#include <config/types.h>

class Character {

public:

    struct Attributes;

    Character(std::string char_name);

    static Character newChar(std::string name, std::string job);

    const Attributes& attributes() const { return _attr; }

    const UIntegerType& level() const { return _level; }

    const std::string& name() const { return _name; }

    const std::string& className() const { return _char_class; }

    void receiveExperience(UIntegerType xp) { _experience += xp; _calculate_free_points_and_experience(); }

    UIntegerType freePoints() const { return _free_points; }

    UIntegerType experienceNeeded() const { return (level()*level())*25; }
    UIntegerType experience() const { return _experience; }

    void assignPoint(UIntegerType stat) {

        if(stat < _attr.statsCount() && _free_points) {

            _attr.stats[stat]++;
            _free_points--;
        }
    }

    void save() const;

    struct Attributes {

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
