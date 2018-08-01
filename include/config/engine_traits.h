
#ifndef ENGINE_TRAITS_H
#define ENGINE_TRAITS_H

#include <traits.h>

template <>
struct Traits <BattleEngine> {

    using SizeType = UIntegerType;

    using PositionType = RealType;
    using AngleType = RealType;

    enum class AngleUnitType { radians, degrees };

    static const AngleUnitType angle_unit = AngleUnitType::radians;

    using PointType = Vec2Type<PositionType>;
};

template <>
struct Traits <Map> : public Traits<BattleEngine> {

    static const UIntegerType width = 1000;
    static const UIntegerType height = 500;

    static const bool solid_border = true;
};

template <>
struct Traits <Unit> : public Traits<BattleEngine> {

    using HealthType = UIntegerType;
    using EnergyType = UIntegerType;
    using AttackType = UIntegerType;
    using DefenseType = UIntegerType;
    using SpeedType = UIntegerType;
};

#endif // ENGINE_TRAITS_H
