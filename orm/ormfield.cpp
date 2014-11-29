#include "ormfield.hpp"

namespace orm {

template<>
std::string getSQLTypeName<int>()
{
    return "INT";
}

template<>
std::string getSQLTypeName<long>()
{
    return "INT";
}

template<>
std::string getSQLTypeName<std::string>()
{
    return "VARCHAR(256)";
}

template<>
std::string sqlTypeToString<std::string>(std::string val)
{
    return "'" + val + "'";
}

template<>
std::string sqlTypeFromString(std::string val)
{
    return val;
}
}
