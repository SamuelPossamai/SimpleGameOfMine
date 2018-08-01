
#ifndef TRAININGGROUND_H
#define TRAININGGROUND_H

#include <utility/randomvalues.h>
#include <unittypes/creaturemap.h>

namespace map {

class TrainingGround : public CreatureMap {

    TrainingGround();

public:

    virtual CreaturesContainer getCreatures() const override;

    static TrainingGround *getMap() { if(!_map) _map = new TrainingGround; return _map; }

private:

    utility::RandomValues<CreaturesContainerContent> _values;

    static TrainingGround *_map;
};

} /* namespace map */

#endif // TRAININGGROUND_H
