#ifndef Animation_H
#define Animation_H

#include <vector>

#include <QGraphicsItem>

#include "traits.h"

class Animation {

public:

    explicit Animation(UIntegerType steps = 1, bool restart = false);

    Animation(const Animation& other) = default;

    bool next();

    bool step() { return next(); }

    void addImage(const QPixmap& p, UIntegerType initial_step);

    bool isOver() const { return _cur_step >= _steps; }

    void start();

    void restart() { start(); }

    void forceOver();

    void setIsPeriodic(bool restart) { _restart = restart; }
    bool isPeriodic() const { return _restart; }

    void setSteps(UIntegerType steps);
    UIntegerType steps() const { return _steps; }

    const QPixmap& pixmap() const { return _vector[_vec_pos].first; }

private:

    bool _choose_item();

    std::vector<std::pair<QPixmap, UIntegerType> > _vector;

    UIntegerType _cur_step;
    UIntegerType _vec_pos;

    UIntegerType _steps;
    bool _restart;
};

#endif // Animation_H
