
#ifndef INTERFACE_TRAITS_H
#define INTERFACE_TRAITS_H

#include <traits.h>

template<>
struct Traits <MainWindow> {

    static constexpr const char * name = "SGOM";

    static const UIntegerType x = 200;
    static const UIntegerType y = 120;
    static const UIntegerType width = 1000;
    static const UIntegerType height = 500;
};

template<>
struct Traits <BattleWidget> {

    static constexpr RealType zoomInMultiplier = 1.2; // should be 1 or higher, 1 means disabled
    static constexpr RealType zoomOutMultiplier = 1.2; // should be 1 or higher, 1 means disabled

    enum class Direction { Horizontal, Vertical };
    static const Direction skillButtonDirection = Direction::Horizontal;

    static constexpr bool allowIdleAnimation = false;
};

#endif // INTERFACE_TRAITS_H
