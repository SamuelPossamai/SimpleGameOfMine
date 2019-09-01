
#ifndef UNITSINFO_ARCHER_H
#define UNITSINFO_ARCHER_H

#include "memory/genericmemorymanager.h"

#include "unitsinfo/fighter.h"

namespace unitsinfo {

class Archer : public Fighter, public GenericMemoryManager::ManagedObject {

    Archer() = default;

    virtual Skills getSkills(const Unit *u) const override;

public:

    static Archer *getInfo() { return static_cast<Archer *>(getObjCopy(Archer())); }

    virtual ~Archer() override = default;

protected:

    virtual HealthType healthCalculate(const Attributes& attr, UIntegerType level) const override {

        return HealthType(150 + 11*attr.vitality() + level);
    }
    virtual AccuracyType accuracyCalculate(const Attributes& attr, UIntegerType) const override {

        return AccuracyType(35 + 1.8*attr.dexterity());
    }

    virtual GenericMemoryManager::ManagedObject *manObjClone() const override { return new Archer(); }
};

} /* namespace unitsinfo */

#endif // UNITSINFO_ARCHER_H
