
#ifndef UNITSINFO_NINJA_H
#define UNITSINFO_NINJA_H

#include "unitsinfo/fighter.h"

namespace unitsinfo {

class Ninja : public Fighter {

    Ninja();

    virtual HealthType healthCalculate(const Attributes& attr, UIntegerType) const override {

        return 150 + 8*attr.vitality() + 0.2*attr.dexterity();
    }
    virtual EnergyType energyCalculate(const Attributes& attr, UIntegerType) const override {

        return 100 + 5*attr.wisdom() + attr.dexterity();
    }
    virtual AttackType attackCalculate(const Attributes& attr, UIntegerType) const override {

        return 12 + 0.8*attr.strength() + 0.3*attr.dexterity() + 0.1*attr.agility() + 0.1*attr.wisdom();
    }
    virtual SpeedType speedCalculate(const Attributes& attr, UIntegerType) const override {

        return 65 + 0.9*attr.agility() + 0.4*attr.dexterity();
    }
    virtual SizeType sizeCalculate(const Attributes& attr, UIntegerType level) const override {

        SizeType size = Fighter::sizeCalculate(attr, level) - 0.01*(attr.dexterity() + attr.agility());
        return size > 5 ? size : 5;
    }

public:

    virtual ~Ninja() {}

    static Ninja *getInfo() {

        if(_info) return _info;

        _info = new Ninja;

        return _info;
    }

private:

    static Ninja *_info;
};

} /* namespace creature */

#endif // UNITSINFO_NINJA_H
