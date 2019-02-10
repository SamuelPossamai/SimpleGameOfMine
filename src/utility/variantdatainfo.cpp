
#include "utility/variantdatainfo.h"

namespace utility::variantdatainfo {

std::pair<VariantDataInfo::iterator, bool> defaultsTo(VariantDataInfo& info, const std::string& str, const Variant& v) {

    auto it = info.find(str);

    if(it == info.end()) {

        auto p = info.insert({ str, v });

        if(!p.second) return { it, false };

        return { p.first, true };
    }
    return { it, false };
}

bool numberToReal(VariantDataInfo& info, const std::string& str) {

    auto it = info.find(str);

    if(it == info.end()) return false;

    return numberToReal(it);
}

bool numberToReal(const VariantDataInfo::iterator& it) {

    if(it->second.isNumber()) {

        it->second.numberToReal();
        return true;
    }
    return false;
}

} /* namespace utility::variantdatainfo */
