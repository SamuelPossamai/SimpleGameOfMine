
#ifndef UNITSINFO_NINJA_H
#define UNITSINFO_NINJA_H

#include "unitsinfo/fighter.h"

namespace unitsinfo {

class Ninja : public Fighter {

    Ninja();

    virtual HealthType healthCalculate(const Attributes& attr, UIntegerType) const override {

        return 150 + 8*attr.vitality() + 0.2*attr.dexterity();
    }
    virtual EnergyType energyCalculate(const Attributes& attr, UIntegerType level) const override {

        return 100 + 5*attr.wisdom() + attr.dexterity() + level;
    }
    virtual AttackType attackCalculate(const Attributes& attr, UIntegerType) const override {

        return 12 + 0.7*attr.strength() + 0.35*attr.dexterity() + 0.05*attr.agility() + 0.1*attr.wisdom();
    }
    virtual AccuracyType accuracyCalculate(const Attributes& attr, UIntegerType) const override {

        return 40 + 1.2*attr.dexterity();
    }
    virtual MagicPowerType magicPowerCalculate(const Attributes&, UIntegerType) const override { return 0; }
    virtual MagicControlType magicControlCalculate(const Attributes&, UIntegerType) const override { return 0; }
    virtual SpeedType speedCalculate(const Attributes& attr, UIntegerType) const override {

        return 65 + 0.85*attr.agility() + 0.35*attr.dexterity();
    }
    virtual SizeType sizeCalculate(const Attributes& attr, UIntegerType level) const override {

        SizeType size = Fighter::sizeCalculate(attr, level) - 0.005*(attr.dexterity() + attr.agility() + level);
        return size > 15 ? size : 15;
    }

public:

    virtual ~Ninja() { delete _shoot_skill; }

    static Ninja *getInfo() {

        if(_info) return _info;

        _info = new Ninja;

        return _info;
    }

private:

    static Ninja *_info;

    UnitSkill *_shoot_skill;
};

} /* namespace creature */

#endif // UNITSINFO_NINJA_H
