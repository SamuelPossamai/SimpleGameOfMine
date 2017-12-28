#ifndef TRAITS_H
#define TRAITS_H

#include <cstddef>

#include "types.h"

template <typename T>
struct Traits {
};

template <>
struct Traits <Unit> {

    using HealthType = UIntegerType;
    using AttackType = UIntegerType;
    using DefenseType = UIntegerType;

    using PositionType = IntegerType;
    using AngleType = IntegerType;
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