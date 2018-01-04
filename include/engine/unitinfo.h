#ifndef UNITINFO_H
#define UNITINFO_H

#include "animation.h"
#include "unitskill.h"

class UnitInfo {

public:

    using HealthType = Traits<Unit>::HealthType;
    using AttackType = Traits<Unit>::AttackType;
    using DefenseType = Traits<Unit>::DefenseType;
    using SizeType = Traits<Unit>::SizeType;

    UnitInfo() {}

    void setHealth(HealthType health) { _max_health = health; }
    HealthType health() const { return _max_health; }

    void setBaseAttack(AttackType attack) { _base_attack = attack; }
    AttackType baseAttack() { return _base_attack; }

    void setSize(SizeType size) { _size = size; }
    SizeType size() const { return _size; }

    void setIdleAnimation(const Animation& animation) { _idle_animation = animation; }
    const Animation& idleAnimation() const { return _idle_animation; }

    void addSkill(UnitSkill *skill, const Animation& an, const QPixmap& icon) { _skills.emplace_back(skill, an, icon); }
    const Animation& skillAnimation(UIntegerType n) const { return std::get<1>(_skills[n]); }
    const QPixmap& skillIcon(UIntegerType n) const { return std::get<2>(_skills[n]); }
    UIntegerType callSkill(UIntegerType n, Unit *u, Map *m, UIntegerType step) const;

    UIntegerType skills() const { return _skills.size(); }

private:

    using SkillVector = std::vector<std::tuple<UnitSkill *, Animation, QPixmap> >;

    HealthType _max_health;
    AttackType _base_attack;
    DefenseType _base_defense;

    SizeType _size;
    Animation _idle_animation;

    SkillVector _skills;
};

#endif // UNITINFO_H
