
#ifndef UNITSINFO_MAGE_H
#define UNITSINFO_MAGE_H

#include <QPixmap>

#include <memory/genericmemorymanager.h>

#include "skills/mageonoffmagicshield.h"
#include "skills/walk.h"
#include "skills/magicmissile.h"
#include "skills/teleport.h"
#include "skills/fireball.h"
#include "skills/explosion.h"
#include "unitsinfo/unitclassinfo.h"

namespace unitsinfo {

class Mage : public UnitClassInfo, public GenericMemoryManager::ManagedObject {

    Mage(const Attributes& attr) : UnitClassInfo(attr) {

        addSkill(skill::Walk::MemoryInterface::dependentGet(10, 100), QPixmap(":/wing_boot.png").scaled(50, 50));
        addSkill(skill::MagicMissile::getSkill(), QPixmap(":/magic_missile_3.png").scaled(50, 50));
        addSkill(skill::Teleport::getSkill(), QPixmap(":/teleport_mage_icon.png").scaled(50, 50));
        addSkill(skill::Fireball::getSkill(), QPixmap(":/fireball_image.png").scaled(50, 50));
        addSkill(skill::Explosion::getSkill(), QPixmap(":/explosion_icon.png").scaled(50, 50));
        addSkill(skill::MageOnOffMagicShield::getSkill(), QPixmap(":/magic_shield.png").scaled(50, 50));

        calculateInfo();
    }

public:

    static Mage *getInfo(Attributes attr) { return static_cast<Mage *>(getObjCopy(Mage(attr))); }

    virtual ~Mage() override { skill::Walk::MemoryInterface::noLongerDepend(10, 100); }

protected:

    virtual HealthType healthCalculate() const override { return 100 + 6*attributes().vitality(); }
    virtual EnergyType energyCalculate() const override { return 200 + 12*attributes().wisdom(); }
    virtual AttackType attackCalculate() const override { return 2 + 0.2*attributes().strength(); }
    virtual SpeedType speedCalculate() const override { return 55 + 0.5*attributes().agility() + 0.2*attributes().dexterity(); }
    virtual SizeType sizeCalculate() const override { return 24; }

    virtual bool manObjLessCompare(const GenericMemoryManager::ManagedObject *obj) const override {

        return *this < *static_cast<const Mage *>(obj);
    }

    virtual GenericMemoryManager::ManagedObject *manObjClone() const override { return new Mage(attributes()); }
};

} /* namespace unitsinfo */

#endif // UNITSINFO_MAGE_H
