
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

    enum class HorizontalAlign { Left, Center, Right };
    static const HorizontalAlign skillButtonHorizontalAlign = HorizontalAlign::Center;

    enum class VerticalAlign { Top, Center, Bottom };
    static const VerticalAlign skillButtonVerticalAlign = VerticalAlign::Bottom;

    static constexpr RealType skillButtonSize = 0.12*Traits<MainWindow>::height;
    static constexpr RealType skillButtonDistance = 0.2*skillButtonSize;
    static constexpr RealType skillButtonBorderVerticalDistance = skillButtonDistance;
    static constexpr RealType skillButtonBorderHorizontalDistance = skillButtonDistance;

    static constexpr bool allowIdleAnimation = false;
};

template<>
struct Traits <Menu> {

    static const UIntegerType buttonsWidth = 0.15*Traits<MainWindow>::width;
    static const UIntegerType buttonsHeight = 0.1*Traits<MainWindow>::height;

    static const UIntegerType buttonsX = (Traits<MainWindow>::width - buttonsWidth)/2;
    static const UIntegerType buttonsY = 0.2*Traits<MainWindow>::height;

    static const UIntegerType buttonsDistance = 0.05*Traits<MainWindow>::height;
};


#endif // INTERFACE_TRAITS_H
