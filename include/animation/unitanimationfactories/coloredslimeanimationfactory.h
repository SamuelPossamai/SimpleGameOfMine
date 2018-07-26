
#ifndef COLOREDSLIMEANIMATIONFACTORY_H
#define COLOREDSLIMEANIMATIONFACTORY_H

#include <memory/onecopymemorymanager.h>

#include "unitanimationfactories/slimeanimationfactory.h"

namespace unitanimationfactory {

class ColoredSlimeAnimationFactory : public SlimeAnimationFactory {

    ColoredSlimeAnimationFactory(QColor color);

public:

    virtual UnitAnimationItem *create(Unit *) override;

    static ColoredSlimeAnimationFactory *getFactory(QColor color) { return _memmanager.get(ColoredSlimeAnimationFactory(color)); }

    bool operator<(const ColoredSlimeAnimationFactory& other) const {

        if(_color.red() != other._color.red()) return _color.red() < other._color.red();
        if(_color.blue() != other._color.blue()) return _color.blue() < other._color.blue();
        if(_color.green() != other._color.green()) return _color.green() < other._color.green();

        return _color.alpha() < other._color.alpha();
    }

private:

    QColor _color;

    static OneCopyMemoryManager<ColoredSlimeAnimationFactory> _memmanager;
};

} /* namespace unitanimationfactory */

#endif // COLOREDSLIMEANIMATIONFACTORY_H
