
#include "unitinfo.h"

UIntegerType UnitInfo::callSkill(UIntegerType n, Unit *u, Map *m, const UnitSkill::Info& info) const {

    return const_cast<UnitSkill *>(std::get<0>(_skills[n]))->action(u, m, info);
}
