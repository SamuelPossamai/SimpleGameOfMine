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

    void addImage(const QPixmap& p, UIntegerType initial_step);

    void setIsPeriodic(bool restart) { _restart = restart; }
    bool isPeriodic() const { return _restart; }

    void setFlag(Flag f, bool value = true) { _flags[UIntegerType(f)] = value; }
    void clearFlag(Flag f) { setFlag(f, false); }

    bool getFlag(Flag f) const { return _flags[UIntegerType(f)]; }

    void setSteps(UIntegerType steps);
    UIntegerType steps() const { return _steps; }

    QPixmap pixmap(UIntegerType n) const { return _vector[n].first; }
    UIntegerType startingStep(UIntegerType n) const { return _vector[n].second; }

    UIntegerType images() const { return _vector.size(); }

    bool cyclic() const { return _restart; }

private:

    std::vector<std::pair<QPixmap, UIntegerType> > _vector;

    UIntegerType _steps;
    bool _restart;

    std::bitset<flags_quantity> _flags;
};

#endif // Animation_H
