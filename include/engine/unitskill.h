
#ifndef UNITSKILL_H
#define UNITSKILL_H

#include <bitset>

#include "config/types.h"

#include "gameinfo/projectiles.h"

/*!
 * \brief This is a virtual pure class that represents an unit skill, all <!--
 * --> skills need to inherit it directly or indirectly.
 * \brief Specific skills are in the skills directory.
 */
class UnitSkill {

    using ProjectileInfo = gameinfo::Projectiles::ProjectileInfo;

public:

    enum class InputType : UIntegerType { angle, __size__ };

    using InputTypeBitSet = std::bitset<UIntegerType(InputType::__size__)>;

    class ProjectileCreationInterface {

    public:

        ProjectileCreationInterface() = default;

        virtual ~ProjectileCreationInterface();

        virtual bool create(const std::string& projectile_type,
                            const Unit *creator,
                            const ProjectileInfo& p_info,
                            Projectile::AngleType dir,
                            Projectile::PointType pos,
                            Projectile::AngleType angle) = 0;
    };

    struct Info {

        UIntegerType step;
        RealType angle;
    };

    explicit UnitSkill(InputTypeBitSet input_set = 0) : _input_set(input_set) {}

    template<typename... Args>
    explicit UnitSkill(InputType in_type, Args... args) {

        setInputTypeMulti(in_type, args...);
    }

    virtual ~UnitSkill();

    /*!
     * \brief This function is virtual pure and must be implemented in a <!--
     * --> derived class.
     * \brief This function is called several times, and it determine what <!--
     * --> the skill does.
     * \param unit The unit that is performing the skill.
     * \param map Object that contains all the units.
     * \param pci Interface to create projectiles.
     * \param info Information about the skill being performed, including <!--
     * --> how many steps(timer cycle) has passed.
     * \return Number of steps until the next call to 'action', to stop the <!--
     * -->skill return 0.
     */
    virtual UIntegerType action(Unit *unit, EngineMap *map,
                                ProjectileCreationInterface& pci,
                                const Info& info) = 0;

    /*!
     * \brief Same as a call to action.
     * \sa action(Unit *, Map *, const Info&)
     * \param unit The unit that is performing thne skill.
     * \param map Object that contains all the units.
     * \param pci Interface to create projectiles.
     * \param info Information about the skill being performed, including <!--
     * --> how many steps(timer cycle) has passed.
     * \return Number of steps until the next call to 'action', to stop the <!--
     * --> skill return 0.
     */
    UIntegerType operator() (Unit *unit, EngineMap *map,
                             ProjectileCreationInterface& pci,
                             const Info& info) {

        return this->action(unit, map, pci, info);
    }

    InputTypeBitSet inputTypeSet() const { return _input_set; }
    bool inputType(InputType in_type) const {

        return _input_set[UIntegerType(in_type)];
    }

    /*!
     * \brief Method to destroy the object, this method exists so derived <!--
     * --> classes can handle memory in a custom approach
     */
    virtual void destroy() { delete this; }

protected:

    void setInputTypeSet(InputTypeBitSet input_set) { _input_set = input_set; }

    void setInputType(InputType in_type, bool val = true) {

        _input_set[UIntegerType(in_type)] = val;
    }

    void unsetInputType(InputType in_type) { setInputType(in_type, false); }

    template<bool val = true, typename... Args>
    void setInputTypeMulti(InputType in_type, Args... args) {

        setInputType(in_type, val);
        setInputTypeMulti(args...);
    }

    void setInputTypeMulti() {}

    template<typename... Args>
    void unsetInputTypeMulti(InputType in_type, Args... args) {

        setInputTypeMulti<false>(in_type, args...);
    }

    void unsetInputTypeMulti() {}

private:

    InputTypeBitSet _input_set;
};

#endif // UNITSKILL_H
