#ifndef Animation_H
#define Animation_H

#include <map>
#include <vector>

#include <QGraphicsItem>

#include "traits.h"

class Animation {

public:

    class Object;

    explicit Animation(QGraphicsScene *scene = nullptr, UIntegerType steps = 1, bool restart = false);

    Animation(const Animation& other);

    ~Animation() { delete _item; }

    bool next();

    bool step() { return next(); }

    void addImage(const QPixmap& p, UIntegerType initial_step);

    bool isOver() const { return _cur_step >= _steps; }

    void start();

    void restart() { start(); }

    void forceOver();

    void setPeriodic(bool restart) { _restart = restart; }
    bool periodic() const { return _restart; }

    void setObject(Object *obj) {  _obj = obj; }
    Object *object() const { return _obj; }

    void setScene(QGraphicsScene *scene);
    QGraphicsScene *scene() { return _scene; }

    void setSteps(UIntegerType steps);
    UIntegerType steps() const { return _steps; }

    void update();

private:

    void _over_procedure();

    void _choose_item();

    void _item_change(const QPixmap& new_item);

    using MapType = std::map<UIntegerType, QPixmap>;

    QGraphicsScene *_scene;

    MapType _map;

    UIntegerType _cur_step;
    MapType::iterator _map_it;

    UIntegerType _steps;
    bool _restart;

    QGraphicsPixmapItem *_item;

    Object *_obj;
};

class Animation::Object {

public:

    using PositionType = Traits<Unit>::PositionType;
    using AngleType = Traits<Unit>::AngleType;

    explicit Object(PositionType x = 0, PositionType y = 0, AngleType angle = 0) : _x(x), _y(y), _angle(angle) {}

    void setX(PositionType x) { _x = x; }
    void setY(PositionType y) { _y = y; }
    void setPos(PositionType x, PositionType y) { setX(x); setY(y); }

    void setAngle(AngleType angle) { _angle = angle; }

    PositionType x() const { return _x; }
    PositionType y() const { return _y; }

    AngleType angle() const { return _angle; }

private:

    PositionType _x, _y;
    AngleType _angle;
};


#endif // Animation_H
