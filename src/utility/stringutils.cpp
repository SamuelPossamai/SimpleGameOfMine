
#include <algorithm>

#include "utility/stringutils.h"

namespace utility::stringutils {

void splitSingle(std::string& f, std::string& s, const std::string& sub) {

    auto it = std::search(f.begin(), f.end(), sub.begin(), sub.end());

    if(it == f.end()) return;

    s.assign(it + std::string::difference_type(sub.size()), f.end());
    f.resize(std::string::size_type(std::distance(f.begin(), it)));
}

void splitSingle(std::string& f, std::string& s, char c) {

    auto it = std::find(f.begin(), f.end(), c);

    if(it == f.end()) return;

    s.assign(it + 1, f.end());
    f.resize(std::string::size_type(std::distance(f.begin(), it)));
}

void replace(std::string& str, const std::string& o, const std::string& n) {

    auto it = str.rbegin();
    while(true) {

        it = std::search(it, str.rend(), o.rbegin(), o.rend());

        if(it >= str.rend()) break;

        str.replace(it.base(), it.base() + std::string::difference_type(o.size()), n.begin(), n.end());
    }
}

} /* namespace utility::stringutils */
