
#ifndef TYPES_H
#define TYPES_H

#include <cstddef>

class BattleEngine;

class Unit;
class UnitBase;
class UnitInfo;

class UnitController;
class UnitSkill;

class Map;

class MainWindow;
class BattleWidget;
class IdButton;
class BattleView;
class Menu;
class HelpWidget;

class Animation;
class AnimatedObject;
class AnimationHandler;

using IntegerType = std::ptrdiff_t;
using UIntegerType = std::size_t;

using RealType = double;

template <typename T>
struct Vec2Type {

    using CoordType = T;

    Vec2Type() : x(0), y(0) {}
    Vec2Type(T x_value, T y_value) : x(x_value), y(y_value) {}

    T x, y;
};

#endif // TYPES_H
