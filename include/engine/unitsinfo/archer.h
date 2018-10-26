
#ifndef UNITSINFO_ARCHER_H
#define UNITSINFO_ARCHER_H

#include <QPixmap>

#include <memory/genericmemorymanager.h>

#include "skills/shoot.h"
#include "unitsinfo/fighter.h"

namespace unitsinfo {

class Archer : public Fighter, public GenericMemoryManager::ManagedObject {

    Archer() {

        addSkill(skill::Shoot::getSkill(), QPixmap(":/arrow_projectile_image.png"));
    }

public:

    static Archer *getInfo() { return static_cast<Archer *>(getObjCopy(Archer())); }

    virtual ~Archer() override = default;

protected:

    virtual HealthType healthCalculate(const Attributes& attr, UIntegerType) const override { return 150 + 11*attr.vitality(); }

    virtual GenericMemoryManager::ManagedObject *manObjClone() const override { return new Archer(); }
};

} /* namespace unitsinfo */

#endif // UNITSINFO_ARCHER_H
