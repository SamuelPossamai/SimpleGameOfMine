
#ifndef STRINGUTILS_H
#define STRINGUTILS_H

#include <algorithm>
#include <string>
#include <limits>

#include "config/types.h"

namespace utility::stringutils {

inline bool notBlank(char c) {

    return !std::isspace(c);
}

template<typename ITER1, typename ITER2>
bool startsWith(ITER1 b1, ITER1 e1, ITER2 b2, ITER2 e2) {

    while(b1 != e1 && b2 != e2) {

        if(*b1 != *b2) return false;

        ++b1;
        ++b2;
    }

    return b2 == e2;
}

template<typename String, typename Callable1, typename Callable2>
std::pair<typename String::const_iterator, typename String::const_iterator> findInterval(const String& str,
                                                                                         Callable1 c1, Callable2 c2) {

    auto stripped_begin = std::find_if(str.begin(), str.end(), c1);
    auto stripped_end = std::find_if(str.rbegin(), str.rend(), c2).base();

    if(stripped_begin > stripped_end) stripped_end = stripped_begin;

    return { stripped_begin, stripped_end };
}

template<typename Callable>
void stripInPlace(std::string& str, Callable callable) {

    auto p = findInterval(str, callable, callable);
    str.assign(p.first, p.second);
}

inline void stripInPlace(std::string& str) {

    stripInPlace(str, notBlank);
}

template<typename Callable>
std::string strip(const std::string& str, Callable callable) {

    auto p = findInterval(str, callable, callable);
    return std::string(p.first, p.second);
}

inline std::string strip(const std::string& str) {

    return strip(str, notBlank);
}

void splitSingle(std::string& f, std::string& s, const std::string& sub);

void splitSingle(std::string& f, std::string& s, char c);

inline std::pair<std::string, std::string> splitSingle(const std::string& str, const std::string& sub) {

    std::string f = str, s;
    splitSingle(f, s, sub);

    return {f, s};
}

inline std::pair<std::string, std::string> splitSingle(const std::string& str, char c) {

    std::string f = str, s;
    splitSingle(f, s, c);

    return {f, s};
}

template<template<typename, typename...> class Container, typename String>
void split(Container<String>& container, const String& str, const String& pat) {

    auto it = str.begin();
    while(it <= str.end()) {

        auto end_it = std::search(it, str.end(), pat.begin(), pat.end());

        container.push_back(String(it, end_it));

        it = end_it + pat.size();
    }
}

template<template<typename, typename...> class Container, typename String>
void split(Container<String>& container, const String& str, const char *pat) {

    split(container, str, String(pat));
}

template<template<typename, typename...> class OutputContainer,
         template<typename, typename...> class NotInsideContainer, typename String, typename Pair>
bool split(OutputContainer<String>& output, const String& str, const String& pat,
           const NotInsideContainer<Pair>& not_inside, UIntegerType max = std::numeric_limits<UIntegerType>::max()) {

    String s_inside;
    auto beg_it = str.begin();

    UIntegerType i = 0;
    for(auto it = str.begin(); it != str.end(); ++it) {

        if(s_inside.empty()) {

            for(auto&& p : not_inside) {

                auto&& s = p.first;

                if(startsWith(it, str.end(), s.begin(), s.end())) {

                    s_inside = p.second;
                    break;
                }
            }

            if(!s_inside.empty()) continue;

            if(startsWith(it, str.end(), pat.begin(), pat.end())) {

                output.push_back(String(beg_it, it));
                it += pat.size() - 1;
                beg_it = it + 1;

                if(i > max) break;
                i++;
            }
        }
        else if(startsWith(it, str.end(), s_inside.begin(), s_inside.end())) {

            it += s_inside.size() - 1;
            s_inside.clear();
        }
    }

    output.push_back(String(beg_it, str.end()));

    return s_inside.empty();
}

template<template<typename, typename...> class OutputContainer,
         template<typename, typename...> class NotInsideContainer, typename String, typename Pair>
bool split(OutputContainer<String>& output, const String& str, const char *pat,
           const NotInsideContainer<Pair>& not_inside, UIntegerType max = std::numeric_limits<UIntegerType>::max()) {

    return split(output, str, String(pat), not_inside, max);
}

inline void toLower(std::string& s) {

    std::transform(s.begin(), s.end(), s.begin(), static_cast<int (*)(int)>(std::tolower));
}

inline void toUpper(std::string& s) {

    std::transform(s.begin(), s.end(), s.begin(), static_cast<int (*)(int)>(std::toupper));
}

void replace(std::string& str, const std::string& o, const std::string& n);

} /* namespace utility::stringutils */

#endif // STRINGUTILS_H
