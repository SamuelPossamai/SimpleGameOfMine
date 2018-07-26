
#ifndef GREENVALLEY_H
#define GREENVALLEY_H

#include <unittypes/creaturemap.h>
#include <utility/randomvalues.h>

namespace map {

class GreenValley : public CreatureMap {

    GreenValley();

public:

    virtual CreaturesContainer getCreatures() const override;

    static GreenValley *getMap() { if(!_map) _map = new GreenValley; return _map; }

private:

    utility::RandomValues<CreaturesContainerContent> _values;

    static GreenValley *_map;
};

} /* namespace map */

#endif // GREENVALLEY_H
