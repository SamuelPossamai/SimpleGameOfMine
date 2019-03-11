
#include "utility/stringutils.h"
#include "utility/variantreader.h"

using namespace utility;
using namespace utility::stringutils;

VariantReader::~VariantReader() {

    for(UIntegerType i = 0; i < UIntegerType(ReadMode::END); i++) {

        if(_delete_reader_after[i]) delete _readers[i];
    }
}

bool VariantReader::setReader(ReadMode m, Reader *r, bool delete_after) {

    auto m_i = UIntegerType(m);

    if(m_i >= UIntegerType(ReadMode::END)) return false;
    if(r == nullptr) delete_after = false;

    _delete_reader_after[m_i] = delete_after;
    _readers[m_i] = r;

    return true;
}

Variant VariantReader::read(const std::string& s) const {

    auto stripped_str = strip(s);

    Variant last_error;

    bool not_default_seq;
    const auto& mode_seq = _get_read_mode_seq(stripped_str, &not_default_seq);

    if(not_default_seq) {

        stripped_str.pop_back();
        stripped_str.erase(stripped_str.begin());
    }

    for(ReadMode r : mode_seq) {

        Reader *reader = _readers[UIntegerType(r)];

        Variant v = reader->read(stripped_str, this);

        if(v.isType<Variant::Error>()) last_error = v;

        if(v.valid()) {

            if(_read_mode_match_type(v, r)) {

                return v;
            }

            return Variant::Error("Variant returned from reader has type that do not match the ReadMode");
        }
    }

    return last_error;
}

bool VariantReader::_read_mode_match_type(const Variant& v, ReadMode m) {

    switch(m) {

        case ReadMode::MAP:
            return v.isMap();
        case ReadMode::LIST:
            return v.isList();
        case ReadMode::STRING:
            return v.isString();
        case ReadMode::INTEGER:
            return v.isInteger();
        case ReadMode::REAL:
            return v.isReal();
        case ReadMode::NUMBER:
            return v.isNumber();
        case ReadMode::BOOL:
            return v.isBool();
        case ReadMode::CUSTOM1:
        case ReadMode::CUSTOM2:
            return true;
        case ReadMode::END:
            break;
    }

    return false;
}

const std::vector<VariantReader::ReadMode>& VariantReader::_get_read_mode_seq(const std::string& stripped_str,
                                                                              bool *not_default) const {

    *not_default = true;

    if(stripped_str.size() >= 2) {

        char last = stripped_str.back();
        switch(stripped_str[0]) {

            case '[':
                if(last == ']') return _brackets_seq;
                break;
            case '{':
                if(last == '}') return _curly_brackets_seq;
                break;
            case '(':
                if(last == ')') return _parenthesis_seq;
                break;
            case '<':
                if(last == '>') return _angle_brackets_seq;
                break;
            case '"':
                if(last == '"') return _double_quotes_seq;
                break;
            case '\'':
                if(last == '\'') return _single_quotes_seq;
                break;
            default:
                break;
        }
    }

    *not_default = false;
    return _default_seq;
}

VariantReader::BoolReader::BoolReader(const std::vector<std::string>& true_words,
                                      const std::vector<std::string>& false_words,
                                      bool case_sensitive) :
    _trues(true_words), _falses(false_words), _case_sensitive(case_sensitive) {

    if(_case_sensitive) {

        for(auto& word: _trues) toLower(word);
        for(auto& word: _falses) toLower(word);
    }
}

VariantReader::Reader::~Reader() {
}

Variant VariantReader::BoolReader::read(const std::string& s, const VariantReader *) {

    auto l_s = s;

    if(_case_sensitive) toLower(l_s);

    if(std::find(_trues.begin(), _trues.end(), s) != _trues.end()) return true;
    if(std::find(_falses.begin(), _falses.end(), s) != _falses.end()) return false;

    return Variant::Invalid();
}

Variant VariantReader::NumberReader::read(const std::string& s, const VariantReader *) {

    bool has_dot = false;

    std::string::const_iterator it;

    if(std::isdigit(s.front())) it = s.begin();
    else {

        if(s.front() != '+' && s.front() != '-') {

            return Variant::Error(std::string("Invalid character '") + s.front() + "' cannot read as a number");
        }

        it = std::find_if(s.begin() + 1, s.end(), notBlank);
    }

    for(; it != s.end(); it++) {

        char c = *it;

        if(!std::isdigit(c)) {

            if(c == '.') {

                if(has_dot) return Variant::Error("Number must not have more than one dot");

                has_dot = true;
            }
            else return Variant::Error(std::string("Invalid character '") + c + "' cannot read as a number");
        }
    }

    if(has_dot) return RealType(std::stod(s));

    return IntegerType(std::stoi(s));
}

Variant VariantReader::ListReader::read(const std::string& s, const VariantReader *vr) {

    std::vector<std::string> v;

    split(v, s, _sep_list, _not_inside);

    VariantList l;

    l.reserve(v.size());

    for(auto&& sp_str : v) l.push_back(vr->read(sp_str));

    return l;
}

Variant VariantReader::MapReader::read(const std::string& s, const VariantReader *vr) {

    std::vector<std::string> v;

    split(v, s, _el_sep, _not_inside);

    VariantMap m;

    for(auto& sp_str : v) {

        auto p = splitSingle(sp_str, _kv_sep);

        Variant key;
        if(_key_reader == nullptr) {

            stripInPlace(p.first);
            key = p.first;
        }
        else key = _key_reader->read(p.first);

        m[key] = vr->read(p.second);
    }

    return m;
}

Variant VariantReader::StringReader::read(const std::string& s, const VariantReader *) {

    if(_escapes.empty()) return s;

    auto s_copy = s;

    for(auto p : _escapes) replace(s_copy, p.first, p.second);

    return s_copy;
}


