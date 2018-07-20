
#ifndef UNITCLASSINFO_H
#define UNITCLASSINFO_H

#include "unitinfo.h"

namespace unitsinfo {

class UnitClassInfo : public UnitInfo {

public:

    struct Attributes;

    UnitClassInfo(const Attributes& attr, SizeType size) : _attributes(attr) { setSize(size); }

    virtual ~UnitClassInfo() {}

    void calculateInfo() {

        setHealth(this->healthCalculate());
        setBaseAttack(this->attackCalculate());
        setSpeed(this->speedCalculate());
    }

    virtual HealthType healthCalculate() const = 0;
    virtual AttackType attackCalculate() const = 0;
    virtual SpeedType speedCalculate() const = 0;

    const Attributes& attributes() const { return _attributes; }

    bool operator<(const UnitClassInfo& other) const {

        if(size() != other.size()) return size() < other.size();

        return _attributes < other._attributes;
    }

    struct Attributes {

        bool operator<(const Attributes& other) const {

            if(strength != other.strength) return strength < other.strength;
            if(vitality != other.vitality) return vitality < other.vitality;
            if(agility != other.agility) return agility < other.agility;

            return dexterity < other.dexterity;
        }

        UIntegerType strength;
        UIntegerType vitality;
        UIntegerType agility;
        UIntegerType dexterity;
    };

private:

    Attributes _attributes;
};

} /* namespace unitsinfo */

#endif // UNITCLASSINFO_H
