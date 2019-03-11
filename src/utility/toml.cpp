
#include <QFile>

#include "stringutils.h"
#include "variantreader.h"
#include "toml.h"

using namespace utility::stringutils;

namespace utility::toml {

struct VariantReaderComponents {

    VariantReaderComponents() : bool_reader({"true"}, {"false"}, true),
        string_reader({{"\\\\", "\\"}, {"\\n", "\n"}}) {

        reader.setReader(VariantReader::ReadMode::BOOL, &bool_reader);
        reader.setReader(VariantReader::ReadMode::NUMBER, &number_reader);
        reader.setReader(VariantReader::ReadMode::LIST, &list_reader);
        reader.setReader(VariantReader::ReadMode::STRING, &string_reader);

        reader.setBracketsReadSequence({ VariantReader::ReadMode::LIST });
        reader.setDefaultReadSequence({ VariantReader::ReadMode::BOOL, VariantReader::ReadMode::NUMBER });
        reader.setQuotesReadSequence({ VariantReader::ReadMode::STRING });
    }

    VariantReader reader;
    VariantReader::BoolReader bool_reader;
    VariantReader::NumberReader number_reader;
    VariantReader::ListReader list_reader;
    VariantReader::StringReader string_reader;
};

const char *ReadingError::what() const noexcept {

    return _error_message.c_str();
}

static void advanceTables(const std::vector<std::string>& to, Variant *&current, UIntegerType line) {

    for(auto&& s : to) {

        if(current->valid() && !current->isMap()) throw ReadingError("Error at line " + std::to_string(line));

        if(!current->valid()) *current = VariantMap();

        auto& map = current->get<VariantMap>();

        current = &map[s];
    }
}

static Variant *findTable(std::map<std::string, Variant>& out, std::string table, UIntegerType current_line) {

    std::vector<std::string> to_sp;
    std::vector<std::pair<std::string, std::string> > not_inside = {{"\"", "\""}, {"'", "'"}};
    if(!split(to_sp, table, ".", not_inside)) throw ReadingError("Error at line " + std::to_string(current_line));
    if(to_sp.empty()) throw ReadingError("Error at line " + std::to_string(current_line));

    Variant *current = &out[to_sp[0]];
    to_sp.erase(to_sp.begin());

    advanceTables(to_sp, current, current_line);

    if(!current->valid()) *current = VariantMap();
    else if(!current->isMap()) throw ReadingError("Error at line " + std::to_string(current_line));

    return current;
}

static void assignValue(std::map<std::string, Variant>& out, std::string to, Variant *table_place,
                        const Variant& value, UIntegerType current_line) {

    std::vector<std::string> to_sp;
    std::vector<std::pair<std::string, std::string> > not_inside = {{"\"", "\""}, {"'", "'"}};
    if(!split(to_sp, to, ".", not_inside)) throw ReadingError("Error at line " + std::to_string(current_line));

    Variant *current = table_place;
    if(current == nullptr) {

        current = &out[to_sp[0]];
        to_sp.erase(to_sp.begin());
    }

    advanceTables(to_sp, current, current_line);

    if(current->valid()) throw ReadingError("Error at line " + std::to_string(current_line));

    *current = value;
}

static void parseAssignLine(std::map<std::string, Variant>& out,
                            const std::string& s, const VariantReader& reader,
                            Variant *current_table,
                            UIntegerType current_line) {

    std::vector<std::string> to_sp;
    std::vector<std::pair<std::string, std::string> > not_inside = {{"\"", "\""}, {"'", "'"}};
    if(!split(to_sp, s, "=", not_inside, 1)) throw ReadingError("Error at line " + std::to_string(current_line));
    if(to_sp.size() != 2) throw ReadingError("Error at line " + std::to_string(current_line));

    Variant val = reader.read(to_sp[1]);

    if(!val.valid()) throw ReadingError("Error at line " + std::to_string(current_line));

    stripInPlace(to_sp[0]);

    assignValue(out, to_sp[0], current_table, val, current_line);
}

static void parseLine(std::map<std::string, Variant>& out,
                      const std::string& s, const VariantReader& reader,
                      Variant *&current_table,
                      UIntegerType current_line) {

    std::string stripped_str = strip(s);

    stripped_str.erase(std::find(stripped_str.begin(), stripped_str.end(), '#'), stripped_str.end());

    if(stripped_str.empty()) return;

    if(stripped_str.front() == '[') {

        if(stripped_str.back() != ']') {

            throw ReadingError("Expected ']' at the end of the line at line " + std::to_string(current_line));
        }

        stripped_str.pop_back();
        stripped_str.erase(stripped_str.begin());
        current_table = findTable(out, stripped_str, current_line);
    }
    else parseAssignLine(out, s, reader, current_table, current_line);
}

std::map<std::string, Variant> read(std::istream& is) {

    VariantReaderComponents c;

    std::map<std::string, Variant> out;

    std::string str;

    UIntegerType current_line = 1;

    Variant *table = nullptr;

    while(is) {

        std::getline(is, str);
        parseLine(out, str, c.reader, table, current_line++);
    }

    return out;
}

std::map<std::string, Variant> read(QFile& file) {

    VariantReaderComponents c;

    std::map<std::string, Variant> out;

    std::string str;

    UIntegerType current_line = 1;

    Variant *table = nullptr;

    while(!file.atEnd()) {

        parseLine(out, file.readLine().toStdString(), c.reader, table, current_line++);
    }

    return out;
}

} /* namespace utility::toml */
