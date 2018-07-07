
#include "unitinfo.h"

UIntegerType UnitInfo::callSkill(UIntegerType n, Unit *u, Map *m, const UnitSkill::Info& info) const {

    return const_cast<UnitSkill *>(_skills[n].first)->action(u, m, info);
}
