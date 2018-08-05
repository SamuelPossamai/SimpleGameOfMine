
#ifndef TYPES_H
#define TYPES_H

#include <cstddef>

class SGOMFiles;

class BattleEngine;

class Unit;
class UnitBase;
class UnitInfo;

class UnitController;
class UnitSkill;
class UnitEffect;

class Map;

class Character;

class MainWindow;
class MainWidget;
class BattleWidget;
class IdButton;
class BattleView;
class Menu;
class HelpWidget;

class Animation;
class AnimatedObject;
class AnimationHandler;
class ProgressBarItem;
class PartialImageItem;
class UnitAnimationItem;
class UnitAnimationItemFactory;

class Jobs;
class Creatures;
class CreatureMap;

namespace utility {

class ImageColorChange;
template<typename> class Interval;

} /* namespace utility */

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
