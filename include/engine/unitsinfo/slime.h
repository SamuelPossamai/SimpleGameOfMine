
#ifndef UNITSINFO_SLIME_H
#define UNITSINFO_SLIME_H

#include "memory/onecopymemorymanager.h"

#include "unitinfo.h"

namespace unitsinfo {

class Slime : public UnitInfo {

public:

    enum class Type : UIntegerType { Normal, Fast, Immortal, Crazy, Ghost };

    virtual ~Slime() override = default;

    static Slime *getInfo(const Type& type = Type::Normal) { return _memmanager.get(Slime(type)); }

    bool operator <(const Slime& other) const { return _type < other._type; }

    virtual void init(Unit *u) const override;

    virtual Skills getSkills(const Unit *) const override;

protected:

    virtual HealthType healthCalculate(const Attributes&, UIntegerType level) const override;
    virtual EnergyType energyCalculate(const Attributes&, UIntegerType) const override { return 0; }
    virtual AttackType attackCalculate(const Attributes&, UIntegerType level) const override;
    virtual AccuracyType accuracyCalculate(const Attributes& attr, UIntegerType) const override {

        return 20 + attr.dexterity();
    }
    virtual MagicPowerType magicPowerCalculate(const Attributes&, UIntegerType) const override { return 0; }
    virtual MagicControlType magicControlCalculate(const Attributes&, UIntegerType) const override { return 0; }
    virtual SpeedType speedCalculate(const Attributes&, UIntegerType level) const override;
    virtual SizeType sizeCalculate(const Attributes&, UIntegerType) const override { return 22; }

private:

    Slime(const Type& type) : _type(type) {}

    Type _type;

    static OneCopyMemoryManager<Slime> _memmanager;
};

} /* namespace creature */

#endif // UNITSINFO_SLIME_H
