#ifndef TRAITS_H
#define TRAITS_H

#include <cstddef>

#include "types.h"

template <typename T>
struct Traits {
};

template <>
struct Traits <BattleEngine> {

    using SizeType = UIntegerType;

    using PositionType = IntegerType;
    using AngleType = RealType;

    enum class AngleUnitType { radians, degrees };

    static const AngleUnitType angle_unit = AngleUnitType::radians;
};

template <>
struct Traits <Map> : public Traits<BattleEngine> {

    using PointType = Vec2Type<PositionType>;
};

template <>
struct Traits <Unit> : public Traits<BattleEngine> {

    using HealthType = UIntegerType;
    using AttackType = UIntegerType;
    using DefenseType = UIntegerType;
};

template<>
struct Traits <BattleWidget> {

    static constexpr RealType zoomInMultiplier = 1.05;
    static constexpr RealType zoomOutMultiplier = 1.05;
};

template<>
struct Traits <MainWindow> {

    static constexpr const char * name = "SGOM";

    static const UIntegerType x = 200;
    static const UIntegerType y = 200;
    static const UIntegerType width = 800;
    static const UIntegerType height = 400;
};

#endif // TRAITS_H
