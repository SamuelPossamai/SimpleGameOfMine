#ifndef UNITCONTROLLER_H
#define UNITCONTROLLER_H

#include "engine_traits.h"

class UnitController {

public:

    UnitController(bool show_buttons) : _show_buttons(show_buttons) {}

    virtual UIntegerType choose(Unit *, Map *, BattleEngine *) = 0;

    virtual UnitController *clone() const = 0;

    bool showButtons() const { return _show_buttons; }

private:

    bool _show_buttons;
};

#endif // UNITCONTROLLER_H
