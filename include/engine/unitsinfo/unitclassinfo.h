
#ifndef UNITCLASSINFO_H
#define UNITCLASSINFO_H

#include <engine/character.h>

#include "unitinfo.h"

namespace unitsinfo {

class UnitClassInfo : public UnitInfo {

public:

    using Attributes = typename Character::Attributes;

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

private:

    Attributes _attributes;
};

} /* namespace unitsinfo */

#endif // UNITCLASSINFO_H
