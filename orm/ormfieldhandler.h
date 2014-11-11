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
    }

    bool fill;
    std::vector<functional::Tripple<std::string, std::string, std::string> > *fields;

    void operator <<(int i){};
};
}

#endif
