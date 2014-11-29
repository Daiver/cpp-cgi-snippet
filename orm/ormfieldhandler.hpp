#ifndef __ORM_FIELD_HANDLER_H__
#define __ORM_FIELD_HANDLER_H__

#include <string>
#include <vector>

#include "ormfield.hpp"
#include "../functional/tripple.hpp"

namespace orm {
class OrmFieldHandler
//FIX IT
{
public:
    OrmFieldHandler(std::vector<functional::Tripple<std::string, std::string, std::string> > *fields, std::vector<std::string> *values=NULL, bool fillModel=false)
    {
        this->fields = fields;
        fill = fillModel;
        counter = 1;
        this->values = values;
    }

    bool fill;
    int counter;
    std::vector<std::string> *values;
    std::vector<functional::Tripple<std::string, std::string, std::string> > *fields;

    template<typename FieldType>
    void operator <<(OrmField<FieldType> ormField)
    {
        if(fill){
            *ormField.fieldPointer = sqlTypeFromString<FieldType>((*values)[counter]);
            ++counter;
        }else{
            fields->push_back(ormField.getSQLNameTypeAndVal());
        }
    }
};
}

#endif
