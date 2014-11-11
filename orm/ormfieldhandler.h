#ifndef __ORM_FIELD_HANDLER_H__
#define __ORM_FIELD_HANDLER_H__

#include <string>
#include <vector>

#include "ormfield.h"
#include "../functional/tripple.h"

namespace orm {
class OrmFieldHandler
//FIX IT
{
public:
    OrmFieldHandler(std::vector<functional::Tripple<std::string, std::string, std::string> > *fields, bool fillModel=false)
    {
        this->fields = fields;
        fill = fillModel;
        counter = 0;
    }

    bool fill;
    int counter;
    std::vector<functional::Tripple<std::string, std::string, std::string> > *fields;

    template<typename FieldType>
    void operator <<(OrmField<FieldType> ormField)
    {
        if(fill){
            *ormField.fieldPointer = sqlTypeFromString<FieldType>((*fields)[counter]);
        }else{
            fields->push_back(ormField.getSQLNameTypeAndVal());
        }
    }
};
}

#endif
