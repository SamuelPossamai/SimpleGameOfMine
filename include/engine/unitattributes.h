
#ifndef UNITATTRIBUTES_H
#define UNITATTRIBUTES_H

#include "config/types.h"

class UnitAttributes {

public:

    static constexpr UIntegerType freePointsPerLevel() { return 4; }

    /*!
     * \brief Return the quantity of _stats
     * \return The quantity of _stats
     */
    static constexpr UIntegerType statsCount() { return sizeof(_stats)/sizeof(_stats[0]); }

    UnitAttributes() { for(UIntegerType i = 0; i < statsCount(); i++) _stats[i] = 0; }
    UnitAttributes(const UnitAttributes&) = default;

    ~UnitAttributes() = default;

    UnitAttributes& operator=(const UnitAttributes&) = default;

    void setStrength(UIntegerType s) { _stats[0] = s; }
    const UIntegerType& strength() const { return _stats[0]; }

    void setVitality(UIntegerType s) { _stats[1] = s; }
    const UIntegerType& vitality() const { return _stats[1]; }

    void setDexterity(UIntegerType s) { _stats[2] = s; }
    const UIntegerType& dexterity() const { return _stats[2]; }

    void setAgility(UIntegerType s) { _stats[3] = s; }
    const UIntegerType& agility() const { return _stats[3]; }

    void setWisdom(UIntegerType s) { _stats[4] = s; }
    const UIntegerType& wisdom() const { return _stats[4]; }

    void assignPoint(UIntegerType attr_id) { _stats[attr_id]++; }

    const UIntegerType& getAttributeValue(UIntegerType attr_id) const { return _stats[attr_id]; }

    bool operator<(const UnitAttributes& other) const {

        for(UIntegerType i = 0; i < statsCount(); i++) {

            if(this->_stats[i] != other._stats[i]) return this->_stats[i] < other._stats[i];
        }

        return false;
    }

    static UnitAttributes generateRandom(UIntegerType level);

private:

    UIntegerType _stats[5];
};

#endif // UNITATTRIBUTES_H
