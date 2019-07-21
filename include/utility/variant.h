
#ifndef UTILITY_VARIANT_H
#define UTILITY_VARIANT_H

#include <variant>
#include <optional>
#include <vector>
#include <map>
#include <string>

#include "types.h"

namespace utility {

/*!
 * \brief Wrapper for std::variant to contain some types easily readable/writable in a text format
 *
 * The following data types can be carried by an object of this class
 *
 * Variant::Invalid - Represents an invalid data
 * Variant::Error - Indicates an error
 * bool
 * Variant::Integer - Same as IntegerType
 * Variant::Real - Same as RealType
 * Variant::List - A std::vector with Variant as content
 * Variant::Map - A std::map with Variant as key and content
 */
class Variant {

public:

    /*!
     * \brief Struct that represents an invalid data inside the variant
     */
    struct Invalid {

        bool operator==(const Invalid&) const { return true; }
        bool operator!=(const Invalid&) const { return false; }
        bool operator<(const Invalid&) const { return false; }
        bool operator<=(const Invalid&) const { return true; }
        bool operator>(const Invalid&) const { return false; }
        bool operator>=(const Invalid&) const { return true; }
    };

    /*!
     * \brief Class used to indicates that an error ocurred in the variant
     * \brief it's used when converting from a string
     */
    class Error {

    public:

        /*!
         * \brief Construct an error passing an error message
         * \param str Error message
         */
        explicit Error(const std::string& str) : _msg(str) {}

        bool operator==(const Error& other) const { return _msg == other._msg; }
        bool operator!=(const Error& other) const { return _msg != other._msg; }
        bool operator<(const Error& other) const { return _msg < other._msg; }
        bool operator<=(const Error& other) const { return _msg <= other._msg; }
        bool operator>(const Error& other) const { return _msg > other._msg; }
        bool operator>=(const Error& other) const { return _msg >= other._msg; }

        /*!
         * \brief Get the error message
         * \return std::string with the error message
         */
        const std::string& message() const { return _msg; }

    private:

        std::string _msg;
    };

    using Integer = IntegerType;
    using Real = RealType;
    using List = std::vector<Variant>;
    using Map = std::map<Variant, Variant>;
    using String = std::string;
    using Pointer = void *;
    using InternalVariant = std::variant<Invalid, Error, bool, Integer, Real, String, List, Map, Pointer>;

    /*!
     * \brief Construct a Variant object in a invalid state
     */
    Variant() : _var(Invalid()) {}

    Variant(const Variant& other) : _var(other._var) {}

    Variant(const char *c_str) : _var(String(c_str)) {}
    Variant(const Invalid& i) : _var(i) {}
    Variant(const Error& e) : _var(e) {}
    Variant(bool b) : _var(b) {}
    Variant(const IntegerType& i) : _var(Integer(i)) {}
    Variant(const UIntegerType& i) : _var(Integer(i)) {}
    Variant(const Real& r) : _var(r) {}
    Variant(const String& s) : _var(s) {}
    Variant(const List& l) : _var(l) {}
    Variant(const Map& m) : _var(m) {}
    Variant(const Pointer& p) : _var(p) {}
    Variant(int i) : _var(Integer(i)) {}

    Variant& operator=(const Variant& other) { _var = other._var; return *this; }

    Variant& operator=(const char *c_str) { _var = String(c_str); return *this; }
    Variant& operator=(const Invalid& i) { _var = i; return *this; }
    Variant& operator=(const Error& e) { _var = e; return *this; }
    Variant& operator=(bool b) { _var = b; return *this; }
    Variant& operator=(const IntegerType& i) { _var = Integer(i); return *this; }
    Variant& operator=(const UIntegerType& i) { _var = Integer(i); return *this; }
    Variant& operator=(const Real& r) { _var = r; return *this; }
    Variant& operator=(const String& s) { _var = s; return *this; }
    Variant& operator=(const List& l) { _var = l; return *this; }
    Variant& operator=(const Map& m) { _var = m; return *this; }
    Variant& operator=(const Pointer& p) { _var = p; return *this; }
    Variant& operator=(int i) { _var = Integer(i); return *this; }

    ~Variant() = default;

    bool operator==(const Variant& other) const { return _var == other._var; }
    bool operator!=(const Variant& other) const { return _var != other._var; }

    bool operator<(const Variant& other) const { return _var < other._var; }
    bool operator>(const Variant& other) const { return _var > other._var; }
    bool operator>=(const Variant& other) const { return _var >= other._var; }
    bool operator<=(const Variant& other) const { return _var <= other._var; }

    /*!
     * \brief Check if the Variant is valid, Invalid and Error are considered invalids by this method
     * \return true if it's valid, false otherwise
     * \sa invalid()
     */
    bool valid() const { return !invalid(); }

    /*!
     * \brief Check if the Variant is invalid, Invalid and Error are considered invalids by this method
     * \return true if it's invalid, false otherwise
     * \sa valid()
     */
    bool invalid() const { return isType<Invalid>() || isType<Error>() || _var.valueless_by_exception(); }

    /*!
     * \brief If this Variant carries an Integer, convert it to a Real
     * \brief If it does not contain a number std::bad_variant_access is thrown
     * \return Reference to the data inside
     */
    Real& numberToReal() { if(isInteger()) *this = Real(*this); return this->get<Real>(); }
    const Real& numberToReal() const { return const_cast<Variant *>(this)->numberToReal(); }

    /*!
     * \brief If this Variant carries a Real, convert it to an Integer
     * \brief If it does not contain a number std::bad_variant_access is thrown
     * \return Reference to the data inside
     */
    Integer& numberToInteger() { if(isReal()) *this = Integer(*this); return this->get<Integer>(); }
    const Integer& numberToInteger() const { return const_cast<Variant *>(this)->numberToInteger(); }

    /*!
     * \brief Verify if the Variant carries a data of type T
     * \tparam T Type that this Variant may carry, must be one of the ones that are supported
     * \return true if T is the type of data inside the Variant, false otherwise
     */
    template<typename T>
    bool isType() const { return std::holds_alternative<T>(_var); }

    /*!
     * \brief Get the id of the type of the data that the Variant carries
     * \return Id of the type of the data that the Variant carries
     */
    UIntegerType typeId() const { return _var.index(); }

    /*!
     * \brief Get the name of the type of the data taht the variant is holding
     * \return Name of the type of the data as a c-like string
     */
    const char *type() const { return typeName(typeId()); }

    /*!
     * \brief Verify if this Variant carries data of the same type as other
     * \param other Variant that will be compared to this
     * \return true if the types are the same, false otherwise
     */
    bool sameType(const Variant& other) const { return typeId() == other.typeId(); }

    /*!
     * \brief Verify if the type of the data is bool
     * \return true if the data is a bool, false otherwise
     */
    bool isBool() const { return isType<bool>(); }

    /*!
     * \brief Verify if the type of the data is Integer
     * \return true if the data is an Integer, false otherwise
     */
    bool isInteger() const { return isType<Integer>(); }

    /*!
     * \brief Verify if the type of the data is Real
     * \return true if the data is a Real, false otherwise
     */
    bool isReal() const { return isType<Real>(); }

    /*!
     * \brief Verify if the data is a number
     * \return true if the data is an Integer or a Real, false otherwise
     */
    bool isNumber() const { return isInteger() || isReal(); }

    /*!
     * \brief Verify if the type of the data is String
     * \return true if the data is a String, false otherwise
     */
    bool isString() const { return isType<String>(); }

    /*!
     * \brief Verify if the type of the data is List
     * \return true if the data is a List, false otherwise
     */
    bool isList() const { return isType<List>(); }

    /*!
     * \brief Verify if the type of the data is Map
     * \return true if the data is a Map, false otherwise
     */
    bool isMap() const { return isType<Map>(); }

    /*!
     * \brief Verify if the type of the data is Pointer
     * \return true if the data is a Pointer, false otherwise
     */
    bool isPointer() const { return isType<Pointer>(); }

    /*!
     * \brief Convert the data to a bool
     * Invalid and Error data will be converted to false
     * bool will be returned as it is
     * Integer and Real will be simply converted to bool
     * String, List and Map will be converted to false if they are empty, true otherwise
     * \return bool value converted from the data
     */
    bool toBool() const;

    /*!
     * \brief Get the data from the Variant, if it's not from the specified type, std::bad_variant_access will be thrown
     * \tparam Type of the data
     * \return Reference to the data inside the Variant
     */
    template<typename T>
    T& get() { return std::get<T>(_var); }

    template<typename T>
    const T& get() const { return std::get<T>(_var); }

    template<typename T>
    std::optional<T> getOptional() const { if(isType<T>()) return get<T>(); return std::nullopt; }

    Real getNumber() const { if(isInteger()) return get<Integer>(); return get<Real>(); }

    template<UIntegerType N>
    auto get() -> std::variant_alternative_t<N, InternalVariant> { return std::get<N>(_var); }

    template<UIntegerType N>
    auto get() -> std::variant_alternative_t<N, InternalVariant> const { return std::get<N>(_var); }

    /*!
     * \brief Same as a call to toBool()
     * \return The bool value for the content
     * \sa toBool()
     */
    explicit operator bool() const { return toBool(); }

    /*!
     * \brief Get the content as an Integer, if it's not a bool, a Real nor a Integer, std::bad_variant_access is thrown
     * \return Variant data converted to an Integer
     */
    explicit operator Integer() const;

    /*!
     * \brief Get the content as a Real, if it's not a bool, a Real nor a Integer, std::bad_variant_access is thrown
     * \return Variant data converted to a Real
     */
    explicit operator Real() const;

    /*!
     * \brief Get the text representation of the data inside
     * \brief Same as a call to toString()
     * \return String that represents the data
     * \sa toString()
     */
    explicit operator String() const { return toString(); }

    /*!
     * \brief Get the data if it's a List, otherwise std::bad_variant_access is thrown
     * \return Variant data as a List
     */
    explicit operator List() const { return get<List>(); }

    /*!
     * \brief Get the data if it's a Map, otherwise std::bad_variant_access is thrown
     * \return Variant data as a Map
     */
    explicit operator Map() const { return get<Map>(); }

    /*!
     * \brief Get the text representation of the data inside
     * \return String that represents the data
     */
    std::string toString() const;

    /*!
     * \brief Get a Variant from a string
     * " 1 " is interpreted as an Integer
     * " 1.2 " is interpreted as a Real
     * " true " or " false " are represented as a bool
     * " 'texto' " or " \"texto\" " are represented as a String
     * " [ 1, '2', 3., [4,5] ] " is represented as a List
     * " { 'texto':1., true:{ '1':[2,3] }}" is represented as a Map
     * \param str String that will converted to a variant
     * \return The Variant obtained from the string, if an error ocurred a call to valid() will return false
     */
    static Variant fromString(const std::string& str);

    template<typename T>
    constexpr static UIntegerType getTypeId() { return _get_type_id_aux<T>(); }

    constexpr static const char *typeName(UIntegerType id);

    template<typename T>
    constexpr static const char *typeName() { return typeName(getTypeId<T>()); }

    friend std::ostream& operator<<(std::ostream& os, const Variant& var) { os << var.toString(); return os; }

private:

    std::string _list_to_string(const List& l) const;

    std::string _map_to_string(const Map& m) const;

    static Variant _variant_from_string_basic(const std::string& stripped_str);

    static bool _add_variant_to_list(Variant& v, const std::string& str);

    static bool _add_variant_to_map(Variant& v, const std::string& str);

    template<typename T, typename U = std::variant_alternative_t<0, InternalVariant>, UIntegerType N = 0>
    struct _get_type_id {

        static const UIntegerType value = _get_type_id<T, std::variant_alternative_t<N+1, InternalVariant>, N+1>::value;
    };

    template<typename T, UIntegerType N>
    struct _get_type_id <T, T, N> {

        static const UIntegerType value = N;
    };

    template<typename T, typename U>
    struct _get_type_id <T, U, std::variant_size<InternalVariant>::value> {

        static const UIntegerType value = std::variant_npos;
    };

    template<typename T>
    constexpr static UIntegerType _get_type_id_aux() { return _get_type_id<T>::value; }

    InternalVariant _var;
};

constexpr const char *Variant::typeName(UIntegerType id) {

    switch (id) {

        case getTypeId<Error>(): return "Error";
        case getTypeId<bool>(): return "bool";
        case getTypeId<Integer>(): return "Integer";
        case getTypeId<Real>(): return "Real";
        case getTypeId<String>(): return "String";
        case getTypeId<List>(): return "List";
        case getTypeId<Map>(): return "Map";
    }

    return "Invalid";
}

using VariantList = Variant::List;
using VariantMap = Variant::Map;
using VariantDataInfo = std::map<std::string, Variant>;

} /* namespace utility */

#endif // UTILITY_VARIANT_H
