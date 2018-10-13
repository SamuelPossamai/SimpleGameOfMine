
#ifndef GREENVALLEY_H
#define GREENVALLEY_H

#include <gameinfo/creaturemap.h>
#include <utility/randomvalues.h>

namespace gameinfo {

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

} /* namespace gameinfo */

#endif // GREENVALLEY_H
