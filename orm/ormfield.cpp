#include "ormfield.h"

namespace orm {
template<>
std::string getSQLTypeName<int>()
{
    return "INT";
}
}
