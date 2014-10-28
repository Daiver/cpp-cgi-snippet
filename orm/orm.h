#ifndef __ORM_H__
#define __ORM_H__

#include <string>

#include "../common.h"
#include "../sqlworker.h"

#include "ormfield.h"
#include "database.h"


#define ORM_EXPORT_CLASS(ClassName) \
    namespace orm { \
        template <> \
        std::string Database::getClassName<ClassName>() \
        {return #ClassName ; } \
    }

#define ORM_MODEL_FIELD(Field) \
    (orm::OrmField<TYPEOF(Field)>(Field, #Field).getSQLNameTypeAndVal())

namespace orm {

}

#endif
