
#include "unitinfo.h"

UIntegerType UnitInfo::callSkill(UIntegerType n, Unit *u, Map *m,
                                 UnitSkill::ProjectileCreationInterface& pci, const UnitSkill::Info& info) const {

    return const_cast<UnitSkill *>(_skills[n].first)->action(u, m, pci, info);
}
