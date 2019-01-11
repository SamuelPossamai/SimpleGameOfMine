
#include "unitinfo.h"

UnitInfo::~UnitInfo() {

    for(auto& skill_tuple : _skills) {

        if(std::get<2>(skill_tuple)) std::get<0>(skill_tuple)->destroy();
    }
}

UIntegerType UnitInfo::callSkill(UIntegerType n, Unit *u, Map *m,
                                 UnitSkill::ProjectileCreationInterface& pci, const UnitSkill::Info& info) const {

    return const_cast<UnitSkill *>(std::get<0>(_skills[n]))->action(u, m, pci, info);
}
