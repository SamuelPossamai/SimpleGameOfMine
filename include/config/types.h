
#ifndef TYPES_H
#define TYPES_H

#include <cstddef>

class SGOMFiles;

class BattleEngine;

class EngineObject;
class EngineObjectBase;

class Unit;
class UnitBase;
class UnitInfo;

class Projectile;
class ProjectileFactory;

class UnitController;
class UnitSkill;
class UnitSkillFactory;
class UnitEffect;

class EngineMap;
using Map = EngineMap;

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
class AnimationItemBase;
class UnitAnimationItem;
class UnitAnimationItemFactory;
class ProjectileAnimationItem;
class ProjectileAnimationItemFactory;

namespace gameinfo {

class Creatures;
class Jobs;
class Projectiles;
class CreatureMap;

} /* namespace gameinfo */

namespace utility {

class ImageColorChange;
template<typename> class Interval;
class Variant;

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
