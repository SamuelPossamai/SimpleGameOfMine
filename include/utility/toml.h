
#ifndef UTILITY_TOML_H
#define UTILITY_TOML_H

#include <exception>
#include <istream>

#include "utility/variant.h"

class QFile;

namespace utility::toml {

class ReadingError : public std::exception {

public:

    ReadingError(const std::string& error_message) : _error_message("toml::ReadingError" + error_message) {}

    virtual ~ReadingError() = default;

    virtual const char *what() const noexcept;

private:

    std::string _error_message;
};

std::map<std::string, Variant> read(std::istream& is);

std::map<std::string, Variant> read(QFile& file);

} /* namespace utility::toml */

#endif // UTILITY_TOML_H
