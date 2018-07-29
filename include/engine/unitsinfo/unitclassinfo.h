
#ifndef UNITCLASSINFO_H
#define UNITCLASSINFO_H

#include <engine/character.h>

#include "unitinfo.h"

namespace unitsinfo {

class UnitClassInfo : public UnitInfo {

public:

    using Attributes = typename Character::Attributes;

    UnitClassInfo(const Attributes& attr) : _attributes(attr) {}

    virtual ~UnitClassInfo() {}

    void calculateInfo() {

        setHealth(this->healthCalculate());
        setEnergy(this->energyCalculate());
        setBaseAttack(this->attackCalculate());
        setSpeed(this->speedCalculate());
        setSize(this->sizeCalculate());
    }

    virtual HealthType healthCalculate() const = 0;
    virtual EnergyType energyCalculate() const = 0;
    virtual AttackType attackCalculate() const = 0;
    virtual SpeedType speedCalculate() const = 0;
    virtual SizeType sizeCalculate() const = 0;

    const Attributes& attributes() const { return _attributes; }

    bool operator<(const UnitClassInfo& other) const {

        if(size() != other.size()) return size() < other.size();

        return _attributes < other._attributes;
    }

private:

    Attributes _attributes;
};

} /* namespace unitsinfo */

#endif // UNITCLASSINFO_H
