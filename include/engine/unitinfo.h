#ifndef UNITINFO_H
#define UNITINFO_H

#include "engine_traits.h"
#include "unitskill.h"

class UnitInfo {

public:

    using HealthType = Traits<Unit>::HealthType;
    using AttackType = Traits<Unit>::AttackType;
    using DefenseType = Traits<Unit>::DefenseType;
    using SizeType = Traits<Unit>::SizeType;

    UnitInfo() {}

    virtual ~UnitInfo() {}

    void setHealth(HealthType health) { _max_health = health; }
    HealthType health() const { return _max_health; }

    void setBaseAttack(AttackType attack) { _base_attack = attack; }
    AttackType baseAttack() { return _base_attack; }

    void setSize(SizeType size) { _size = size; }
    SizeType size() const { return _size; }

    void addSkill(UnitSkill *skill, const QPixmap& icon) { _skills.emplace_back(skill, icon); }
    const QPixmap& skillIcon(UIntegerType n) const { return _skills[n].second; }
    UIntegerType callSkill(UIntegerType n, Unit *u, Map *m, const UnitSkill::Info&) const;
    bool skillNeedAngle(UIntegerType n) const { return _skills[n].first->needAngle(); }

    UIntegerType skills() const { return _skills.size(); }

    virtual void init(Unit *u) const { Q_UNUSED(u); }

    void copy(UnitInfo *i) { copySkills(i); copyStatus(i); }
    void copySkills(UnitInfo *i) { _skills = i->_skills; }
    void copyStatus(UnitInfo *i);

private:

    using SkillVector = std::vector<std::pair<UnitSkill *, QPixmap> >;

    HealthType _max_health;
    AttackType _base_attack;
    DefenseType _base_defense;

    SizeType _size;

    SkillVector _skills;
};

#endif // UNITINFO_H
