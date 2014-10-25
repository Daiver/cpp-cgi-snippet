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


    std::string fieldName;
    FieldType fieldValue;
};
}

#endif
