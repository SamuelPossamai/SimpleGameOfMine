
#ifndef JOBS_H
#define JOBS_H

#include <optional>
#include <tuple>

#include <engine/unitsinfo/unitclassinfo.h>

class Jobs {

public:

    using Info = std::tuple<unitsinfo::UnitClassInfo *, UnitAnimationItemFactory *>;
    using Attributes = unitsinfo::UnitClassInfo::Attributes;

    static std::optional<Info> get(std::string name, const Attributes& attr);

private:

    using GetJobFunctionType = Info (*)(const Attributes&);

    static void _init();

    static std::map<std::string, GetJobFunctionType> _jobs;
};

#endif // JOBS_H
