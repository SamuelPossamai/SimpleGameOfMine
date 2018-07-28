
#ifndef UNITINFO_H
#define UNITINFO_H

#include <vector>

#include <QPixmap>

#include "engine_traits.h"
#include "unitskill.h"

class UnitInfo {

public:

    using HealthType = Traits<Unit>::HealthType;
    using EnergyType = Traits<Unit>::EnergyType;
    using AttackType = Traits<Unit>::AttackType;
    using DefenseType = Traits<Unit>::DefenseType;
    using SizeType = Traits<Unit>::SizeType;
    using SpeedType = Traits<Unit>::SpeedType;

    UnitInfo() : _max_health(0), _max_energy(0), _base_attack(0), _speed(0), _size(0) {}

    virtual ~UnitInfo() {}

    HealthType health() const { return _max_health; }
    EnergyType energy() const { return _max_energy; }
    AttackType baseAttack() const { return _base_attack; }
    SizeType size() const { return _size; }
    SpeedType speed() const { return _speed; }

    void addSkill(UnitSkill *skill, const QPixmap& icon) { _skills.emplace_back(skill, icon); }
    const QPixmap& skillIcon(UIntegerType n) const { return _skills[n].second; }
    UIntegerType callSkill(UIntegerType n, Unit *u, Map *m, const UnitSkill::Info&) const;
    bool skillNeedAngle(UIntegerType n) const { return _skills[n].first->needAngle(); }

    UIntegerType skills() const { return _skills.size(); }

    virtual void init(Unit *u) const { Q_UNUSED(u); }

    void copy(const UnitInfo *i) { copySkills(i); copyStatus(i); }
    void copySkills(const UnitInfo *i) { _skills = i->_skills; }
    void copyStatus(const UnitInfo *i);

protected:

    void setHealth(HealthType health) { _max_health = health; }
    void setEnergy(EnergyType energy) { _max_energy = energy; }
    void setSize(SizeType size) { _size = size; }
    void setBaseAttack(AttackType attack) { _base_attack = attack; }
    void setSpeed(SpeedType speed) { _speed = speed; }

private:

    using SkillVector = std::vector<std::pair<UnitSkill *, QPixmap> >;

    HealthType _max_health;
    EnergyType _max_energy;
    AttackType _base_attack;
    DefenseType _base_defense;
    SpeedType _speed;

    SizeType _size;

    SkillVector _skills;
};

#endif // UNITINFO_H
