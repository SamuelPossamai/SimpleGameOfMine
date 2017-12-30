#ifndef TYPES_H
#define TYPES_H

class BattleEngine;

class Unit;
class UnitBase;
class UnitInfo;

class Map;

class MainWindow;
class BattleWidget;

class Animation;
class AnimatedObject;

using IntegerType = std::ptrdiff_t;
using UIntegerType = std::size_t;

using RealType = double;

template <typename T>
struct Vec2Type {

    T x, y;
};

#endif // TYPES_H
