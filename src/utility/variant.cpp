
#include <stack>
#include <sstream>
#include <cctype>
#include <algorithm>

#include "variant.h"

using namespace utility;

std::string Variant::_strip(const std::string& str) {

    auto not_blank = [](char c){ return !std::isspace(c); };

    auto st_it = std::find_if(str.begin(), str.end(), not_blank);

    if(st_it == str.end()) return "";

    return std::string(st_it, std::find_if(str.rbegin(), str.rend(), not_blank).base());
}

static Variant variantFromStringBasicNumber(const std::string& stripped_str) {

    bool has_dot = false;
    for(char c : stripped_str) {

        if(!std::isdigit(c)) {

            if(c == '.') {

                if(has_dot) return Variant::Invalid();

                has_dot = true;
            }
            else return Variant::Invalid();
        }
    }

    if(has_dot) return RealType(std::stod(stripped_str));

    return IntegerType(std::stoi(stripped_str));
}

Variant Variant::_variant_from_string_basic(const std::string& stripped_str) {

    if(stripped_str.empty()) return Variant::Invalid();

    if(stripped_str.front() == '"' or stripped_str.front() == '\'') {

        if(stripped_str.front() != stripped_str.back() || stripped_str.size() == 1) return Variant::Invalid();

        return std::string(stripped_str.begin() + 1, stripped_str.end() - 1);
    }

    return variantFromStringBasicNumber(stripped_str);
}

static bool advanceToNextValid(char c, std::string::const_iterator& it, const std::string::const_iterator& end_it,
                               char& quote_type, std::stack<char>& brackets) {

    for(; it != end_it; ++it) {

        if(*it == '"' || *it == '\'') {

            if(quote_type == 0) quote_type = *it;
            if(quote_type == *it) quote_type = 0;
        }

        if(quote_type != 0) continue;

        if(*it == '[' || *it == '{') brackets.push(*it);
        if(*it == ']' || *it == '}') {

            char last = brackets.top();
            if(brackets.empty()) return false;
            if(!((last == '[' && *it == ']') || (last == '{' && *it == '}'))) return false;

            brackets.pop();
        }

        if(!brackets.empty()) continue;

        if(*it == c) return true;
    }

    return true;
}

bool Variant::_add_variant_to_map(Variant& v, const std::string& str) {

    if(!v.isType<Map>()) return false;

    char quote_type = 0;
    std::stack<char> brackets;
    auto it = str.begin();
    bool ret = advanceToNextValid(':', it, str.end(), quote_type, brackets);

    if(!ret || it == str.end()) return false;

    Variant key = fromString(std::string(str.begin(), it));

    if(key.invalid()) return false;

    Variant content = fromString(std::string(it + 1, str.end()));

    v.get<Variant::Map>()[key] = content;

    return true;
}

bool Variant::_add_variant_to_list(Variant& v, const std::string& str) {

    if(!v.isType<List>()) return false;

    Variant el = fromString(str);

    if(el.invalid()) return false;

    v.get<List>().push_back(el);

    return true;
}

Variant Variant::fromString(const std::string& str) {

    std::string stripped_str = _strip(str);

    Variant var_basic = _variant_from_string_basic(stripped_str);

    if(var_basic.valid()) return var_basic;

    if(stripped_str.front() == '[' || stripped_str.front() == '{') {

        if(stripped_str.front() == '[' && stripped_str.back() != ']') return Invalid();
        if(stripped_str.front() == '{' && stripped_str.back() != '}') return Invalid();

        auto st_it = stripped_str.cbegin() + 1;
        const auto end_it = stripped_str.cend() - 1;

        if(std::find_if(stripped_str.begin() + 1, stripped_str.end() - 1,
                        [](char c){ return !std::isspace(c); }) == stripped_str.end()-1) {

            if(stripped_str.front() == '[') return Variant::List();
            return Variant::Map();
        }

        Variant result;

        if(stripped_str.front() == '[') result = Variant::List();
        else result = Variant::Map();

        char quote_type = 0;
        std::stack<char> brackets;

        auto it = st_it;
        while(it < end_it) {

            bool ret = advanceToNextValid(',', it, end_it, quote_type, brackets);

            if(!ret) return Invalid();

            std::string el_str = std::string(st_it, it);

            bool insert_failed = false;
            if(stripped_str.front() == '[') {

                if(!_add_variant_to_list(result, el_str)) insert_failed = true;
            }
            else {

                if(!_add_variant_to_map(result, el_str)) insert_failed = true;
            }

            if(insert_failed) return Error("Failed to parse `" + _strip(el_str) + "`");

            st_it = ++it;
        }

        if(quote_type != 0 || !brackets.empty()) return Invalid();

        return result;
    }

    if(stripped_str == "true" || stripped_str == "yes") return true;
    else if(stripped_str == "false" || stripped_str == "no") return false;

    return Invalid();
}

std::string Variant::_list_to_string(const List& l) const {

    if(l.empty()) return "[]";

    std::ostringstream oss;

    oss << "[ ";

    for(const Variant& v : l) {

        oss << v.toString() << ", ";
    }

    std::string s = oss.str();

    s[s.size() - 2] = ' ';
    s[s.size() - 1] = ']';

    return s;
}

std::string Variant::_map_to_string(const Map& m) const {

    if(m.empty()) return "{}";

    std::ostringstream oss;

    oss << "{ ";

    for(const std::pair<const Variant, Variant>& p : m) {

        oss << p.first.toString() << " : " << p.second.toString() << ", ";
    }

    std::string s = oss.str();

    s[s.size() - 2] = ' ';
    s[s.size() - 1] = '}';

    return s;
}

bool Variant::toBool() const {

    switch (typeId()) {

        case getTypeId<bool>(): return get<bool>();
        case getTypeId<Integer>(): return get<Integer>();
        case getTypeId<Real>(): return bool(get<Real>());
        case getTypeId<String>(): return !get<String>().empty();
        case getTypeId<List>(): return !get<List>().empty();
        case getTypeId<Map>(): return !get<Map>().empty();
    }

    return false;
}

Variant::operator Integer() const {

    if(isType<Real>()) return Integer(get<Real>());
    if(isType<bool>()) return Integer(get<bool>());

    return get<Integer>();
}

Variant::operator Real() const {

    if(isType<Integer>()) return Real(get<Real>());
    if(isType<bool>()) return Real(get<bool>());

    return get<Real>();
}

std::string Variant::toString() const {

    switch (typeId()) {

        case getTypeId<Error>(): return "Error: '" + get<Error>().message() + '\'';
        case getTypeId<bool>(): return get<bool>() ? "true" : "false";
        case getTypeId<Integer>(): return std::to_string(get<Integer>());
        case getTypeId<Real>(): return std::to_string(get<Real>());
        case getTypeId<String>(): return "'" + get<String>() + "'";
        case getTypeId<List>(): return _list_to_string(get<List>());
        case getTypeId<Map>(): return _map_to_string(get<Map>());
    }

    return "invalid";
}
