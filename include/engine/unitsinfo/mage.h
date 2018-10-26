
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
#include "unitinfo.h"

namespace unitsinfo {

class Mage : public UnitInfo, public GenericMemoryManager::ManagedObject {

    Mage() {

        addSkill(skill::Walk::MemoryInterface::dependentGet(10, 100), QPixmap(":/wing_boot.png").scaled(50, 50));
        addSkill(skill::MagicMissile::getSkill(), QPixmap(":/magic_missile_3.png").scaled(50, 50));
        addSkill(skill::Teleport::getSkill(), QPixmap(":/teleport_mage_icon.png").scaled(50, 50));
        addSkill(skill::Fireball::getSkill(), QPixmap(":/fireball_image.png").scaled(50, 50));
        addSkill(skill::Explosion::getSkill(), QPixmap(":/explosion_icon.png").scaled(50, 50));
        addSkill(skill::MageOnOffMagicShield::getSkill(), QPixmap(":/magic_shield.png").scaled(50, 50));
    }

public:

    static Mage *getInfo() { return static_cast<Mage *>(getObjCopy(Mage())); }

    virtual ~Mage() override { skill::Walk::MemoryInterface::noLongerDepend(10, 100); }

protected:

    virtual HealthType healthCalculate(const Attributes& attr, UIntegerType) const override { return 100 + 6*attr.vitality(); }
    virtual EnergyType energyCalculate(const Attributes& attr, UIntegerType) const override { return 200 + 12*attr.wisdom(); }
    virtual AttackType attackCalculate(const Attributes& attr, UIntegerType) const override { return 2 + 0.2*attr.strength(); }
    virtual SpeedType speedCalculate(const Attributes& attr, UIntegerType) const override {

        return 55 + 0.5*attr.agility() + 0.2*attr.dexterity();
    }
    virtual SizeType sizeCalculate(const Attributes&, UIntegerType) const override { return 24; }

    virtual GenericMemoryManager::ManagedObject *manObjClone() const override { return new Mage; }
};

} /* namespace unitsinfo */

#endif // UNITSINFO_MAGE_H
