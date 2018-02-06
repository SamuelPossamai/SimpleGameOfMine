#ifndef Animation_H
#define Animation_H

#include <vector>
#include <bitset>
#include <random>

#include <QGraphicsItem>

#include "types.h"

/*!
 * \brief Abstraction for an animation.
 */
class Animation {

    static const UIntegerType flags_quantity = 1;

public:

    enum class Flag : UIntegerType { RandomStart };

    explicit Animation(UIntegerType steps = 1, bool restart = false);

    Animation(const Animation& other) = default;

    Animation& operator=(const Animation& other) = default;

    bool next();

    bool step() { return next(); }

    void addImage(const QPixmap& p, UIntegerType initial_step);

    bool isOver() const { return _cur_step >= _steps; }

    void start(bool rnd_start = true);

    void restart(bool rnd_start = false) { start(rnd_start); }

    void forceOver();

    void setIsPeriodic(bool restart) { _restart = restart; }
    bool isPeriodic() const { return _restart; }

    void setFlag(Flag f, bool value = true) { _flags[UIntegerType(f)] = value; }
    void clearFlag(Flag f) { setFlag(f, false); }

    bool getFlag(Flag f) const { return _flags[UIntegerType(f)]; }

    void setSteps(UIntegerType steps);
    UIntegerType steps() const { return _steps; }

    QPixmap pixmap() const { return (_vec_pos == 0) ? QPixmap() : _vector[_vec_pos - 1].first; }

    QPixmap pixmap(UIntegerType n) const { return _vector[n].first; }
    UIntegerType startingStep(UIntegerType n) const { return _vector[n].second; }

    UIntegerType images() const { return _vector.size(); }

    bool cyclic() const { return _restart; }

private:

    bool _choose_item();

    std::vector<std::pair<QPixmap, UIntegerType> > _vector;

    UIntegerType _cur_step;
    UIntegerType _vec_pos;

    UIntegerType _steps;
    bool _restart;

    std::bitset<flags_quantity> _flags;

    static std::mt19937 _gen;
};

#endif // Animation_H
