
#ifndef UNITSINFO_ARCHER_H
#define UNITSINFO_ARCHER_H

#include <QPixmap>

#include <memory/genericmemorymanager.h>

#include "skills/shoot.h"
#include "unitsinfo/fighter.h"

namespace unitsinfo {

class Archer : public Fighter, public GenericMemoryManager::ManagedObject {

    Archer() {

        addSkill((_shoot_skill = new skill::Shoot("arrow")), QPixmap(":/arrow_projectile_image.png"));
    }

public:

    static Archer *getInfo() { return static_cast<Archer *>(getObjCopy(Archer())); }

    virtual ~Archer() override {

        delete _shoot_skill;
    }

protected:

    virtual HealthType healthCalculate(const Attributes& attr, UIntegerType level) const override {

        return 150 + 11*attr.vitality() + level;
    }
    virtual AccuracyType accuracyCalculate(const Attributes& attr, UIntegerType) const override {

        return 35 + 1.8*attr.dexterity();
    }

    virtual GenericMemoryManager::ManagedObject *manObjClone() const override { return new Archer(); }

private:

    UnitSkill *_shoot_skill;
};

} /* namespace unitsinfo */

#endif // UNITSINFO_ARCHER_H
