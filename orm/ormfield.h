#ifndef __ORM_FIELD_H__
#define __ORM_FIELD_H__

#include <string>
#include <sstream>
#include "../functional/tripple.h"

namespace orm{

template <typename TypeName>
std::string getSQLTypeName();

template <typename TypeName>
std::string sqlTypeToString(TypeName val)
{
    std::stringstream ss;
    ss << val;
    return ss.str();
}

template <typename TypeName>
TypeName sqlTypeFromString(std::string val)
{
    std::istringstream iss(val);
    TypeName t;
    iss >> t;
    return t;
}

template<typename FieldType>
class OrmField
{
public:
    OrmField(FieldType fieldValue, std::string fieldName)
    {
        this->fieldName = fieldName;
        this->fieldValue = fieldValue;
    }

    functional::Tripple<std::string, std::string, std::string> getSQLNameTypeAndVal();

    std::string fieldName;
    FieldType fieldValue;
};
}


template<typename FieldType>
functional::Tripple<std::string, std::string, std::string> 
    orm::OrmField<FieldType>::getSQLNameTypeAndVal()
{
    return functional::makeTripple(this->fieldName, getSQLTypeName<FieldType>(), sqlTypeToString(this->fieldValue));
}

#endif
