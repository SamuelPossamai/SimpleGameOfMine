
#ifndef VARIANTREADER_H
#define VARIANTREADER_H

#include <vector>

#include "utility/variant.h"

namespace utility {

class VariantReader {

public:

    VariantReader() {

        for(auto& reader: _readers) reader = nullptr;
        for(auto& b: _delete_reader_after) b = false;
    }

    ~VariantReader();

    enum class ReadMode : unsigned char { MAP, LIST, STRING, INTEGER, REAL, NUMBER, BOOL, CUSTOM1, CUSTOM2, END };

    class Reader;
    class BoolReader;
    class IntegerReader;
    class RealReader;
    class NumberReader;
    class ListReader;
    class MapReader;
    class StringReader;

    void setQuotesReadSequence(const std::vector<ReadMode>& seq) {

        setDoubleQuotesReadSequence(seq);
        setSingleQuotesReadSequence(seq);
    }

    void setDoubleQuotesReadSequence(const std::vector<ReadMode>& seq) { _double_quotes_seq = seq; }
    void setSingleQuotesReadSequence(const std::vector<ReadMode>& seq) { _single_quotes_seq = seq; }
    void setCurlyBracketsReadSequence(const std::vector<ReadMode>& seq) { _curly_brackets_seq = seq; }
    void setBracketsReadSequence(const std::vector<ReadMode>& seq) { _brackets_seq = seq; }
    void setAngleBracketsReadSequence(const std::vector<ReadMode>& seq) { _angle_brackets_seq = seq; }
    void setParenthesisReadSequence(const std::vector<ReadMode>& seq) { _parenthesis_seq = seq; }
    void setDefaultReadSequence(const std::vector<ReadMode>& seq) { _default_seq = seq; }

    bool setReader(ReadMode m, Reader *r, bool delete_after = false);
    const Reader *reader(ReadMode m) const { return _get_reader(m); }

    Variant read(const std::string&) const;

private:

    static bool _read_mode_match_type(const Variant& v, ReadMode m);

    Reader *_get_reader(ReadMode m) const {

        auto m_i = UIntegerType(m);

        if(m_i >= UIntegerType(ReadMode::END)) return nullptr;

        return _readers[m_i];
    }

    const std::vector<ReadMode>& _get_read_mode_seq(const std::string& stripped_str, bool *not_default) const;

    std::vector<ReadMode> _double_quotes_seq;
    std::vector<ReadMode> _single_quotes_seq;
    std::vector<ReadMode> _curly_brackets_seq;
    std::vector<ReadMode> _brackets_seq;
    std::vector<ReadMode> _angle_brackets_seq;
    std::vector<ReadMode> _parenthesis_seq;
    std::vector<ReadMode> _default_seq;

    Reader *_readers[UIntegerType(ReadMode::END)];

    bool _delete_reader_after[UIntegerType(ReadMode::END)];
};

class VariantReader::Reader {

public:

    Reader() = default;

    virtual ~Reader();

    virtual Variant read(const std::string& s, const VariantReader *vr) = 0;
};

class VariantReader::BoolReader : public Reader {

public:

    BoolReader(const std::vector<std::string>& true_words, const std::vector<std::string>& false_words, bool case_sensitive);

    virtual ~BoolReader() override = default;

    virtual Variant read(const std::string& s, const VariantReader *vr) override;

private:

    std::vector<std::string> _trues;
    std::vector<std::string> _falses;

    bool _case_sensitive;
};

class VariantReader::NumberReader : public Reader {

public:

    NumberReader() = default;

    virtual ~NumberReader() override = default;

    virtual Variant read(const std::string& s, const VariantReader *vr) override;
};

class VariantReader::IntegerReader : public NumberReader {

public:

    IntegerReader() = default;

    virtual ~IntegerReader() override = default;

    virtual Variant read(const std::string& s, const VariantReader *vr) override {

        Variant v = NumberReader::read(s, vr);

        if(v.isReal()) return Variant::Error("Expected integer found real");

        return v;
    }
};

class VariantReader::RealReader : public NumberReader {

public:

    RealReader() = default;

    virtual ~RealReader() override = default;

    virtual Variant read(const std::string& s, const VariantReader *vr) override {

        Variant v = NumberReader::read(s, vr);

        if(v.isInteger()) v.numberToReal();

        return v;
    }
};

class VariantReader::ListReader : public Reader {

public:

    ListReader(const std::string& separator = ",") : _sep_list(separator) {

        _not_inside = {{"{", "}"}, {"[", "]"}, {"(", ")"}, {"<", ">"}, {"'", "'"}, {"\"", "\""}};
    }

    ListReader(const std::string& separator, std::vector<std::pair<std::string, std::string> > not_inside) :
        _sep_list(separator), _not_inside(not_inside) {}

    virtual ~ListReader() override = default;

    virtual Variant read(const std::string& s, const VariantReader *vr) override;

private:

    std::string _sep_list;
    std::vector<std::pair<std::string, std::string> > _not_inside;
};

class VariantReader::MapReader : public Reader {

public:

    MapReader(const std::string& el_separator = ",", const std::string& kv_separator = ":") :
        _el_sep(el_separator), _kv_sep(kv_separator), _key_reader(nullptr) {

        _not_inside = {{"{", "}"}, {"[", "]"}, {"(", ")"}, {"<", ">"}, {"'", "'"}, {"\"", "\""}};
    }

    MapReader(const std::string& elements_separator, const std::string& key_value_separator,
              std::vector<std::pair<std::string, std::string> > not_inside) :
        _el_sep(elements_separator), _kv_sep(key_value_separator), _not_inside(not_inside),
        _key_reader(nullptr) {}

    virtual ~MapReader() override = default;

    void setKeyReader(const VariantReader *key_reader) { _key_reader = key_reader; }
    const VariantReader *keyReader() const { return _key_reader; }

    virtual Variant read(const std::string& s, const VariantReader *vr) override;

private:

    std::string _el_sep;
    std::string _kv_sep;
    std::vector<std::pair<std::string, std::string> > _not_inside;

    const VariantReader *_key_reader;
};

class VariantReader::StringReader : public Reader {

public:

    StringReader(const std::vector<std::pair<std::string, std::string> >& escapes = {}) : _escapes(escapes) {}

    virtual ~StringReader() override = default;

    virtual Variant read(const std::string& s, const VariantReader *vr) override;

private:

    std::vector<std::pair<std::string, std::string> > _escapes;
};

} /* namespace utility */

#endif // VARIANTREADER_H
