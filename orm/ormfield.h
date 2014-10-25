#ifndef __ORM_FIELD_H__
#define __ORM_FIELD_H__

#include <string>

namespace orm{

    template <typename TypeName>
    std::string getSQLTypeName();

template<typename FieldType>
class OrmField
{
public:
    OrmField(FieldType fieldValue, std::string fieldName)
    {
        this->fieldName = fieldName;
        this->fieldValue = fieldValue;
    }

    std::pair<std::string, std::string> getSQLNameAndType();

    std::string fieldName;
    FieldType fieldValue;
};
}


template<typename FieldType>
std::pair<std::string, std::string> orm::OrmField<FieldType>::getSQLNameAndType()
{
    return std::make_pair(this->fieldName, getSQLTypeName<FieldType>());
}

#endif
