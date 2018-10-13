
#include "unitinfo.h"

UnitInfo::~UnitInfo() {
}

UIntegerType UnitInfo::callSkill(UIntegerType n, Unit *u, Map *m,
                                 UnitSkill::ProjectileCreationInterface& pci, const UnitSkill::Info& info) const {

    return const_cast<UnitSkill *>(_skills[n].first)->action(u, m, pci, info);
}

void UnitInfo::copyStats(const UnitInfo *i) {

    _max_health = i->_max_health;
    _max_energy = i->_max_energy;
    _base_attack = i->_base_attack;
    _base_defense = i->_base_defense;
    _size = i->_size;
    _speed = i->_speed;
}
