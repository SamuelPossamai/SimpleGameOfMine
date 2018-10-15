
#ifndef UNITSINFO_ARCHER_H
#define UNITSINFO_ARCHER_H

#include <QPixmap>

#include <memory/genericmemorymanager.h>

#include "skills/shoot.h"
#include "unitsinfo/fighter.h"

namespace unitsinfo {

class Archer : public Fighter, public GenericMemoryManager::ManagedObject {

    Archer(const Attributes& attr) : Fighter(attr) {

        addSkill(skill::Shoot::getSkill(), QPixmap(":/arrow_projectile_image.png"));
    }

public:

    static Archer *getInfo(Attributes attr) { return static_cast<Archer *>(getObjCopy(Archer(attr))); }

    virtual ~Archer() override = default;

protected:

    virtual HealthType healthCalculate() const override { return 150 + 11*attributes().vitality(); }

    virtual bool manObjLessCompare(const GenericMemoryManager::ManagedObject *obj) const override {

        return *this < *static_cast<const Archer *>(obj);
    }

    virtual GenericMemoryManager::ManagedObject *manObjClone() const override { return new Archer(attributes()); }
};

} /* namespace unitsinfo */

#endif // UNITSINFO_ARCHER_H
