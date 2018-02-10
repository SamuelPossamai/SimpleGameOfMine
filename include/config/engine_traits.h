
#ifndef ENGINE_TRAITS_H
#define ENGINE_TRAITS_H

#include <traits.h>

template <>
struct Traits <BattleEngine> {

    using SizeType = UIntegerType;

    using PositionType = IntegerType;
    using AngleType = RealType;

    enum class AngleUnitType { radians, degrees };

    static const AngleUnitType angle_unit = AngleUnitType::radians;

    using PointType = Vec2Type<PositionType>;
};

template <>
struct Traits <Map> : public Traits<BattleEngine> {

};

template <>
struct Traits <Unit> : public Traits<BattleEngine> {

    using HealthType = UIntegerType;
    using AttackType = UIntegerType;
    using DefenseType = UIntegerType;
};


#endif // ENGINE_TRAITS_H
