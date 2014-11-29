#ifndef __ORM_H__
#define __ORM_H__

#include <string>

#include "../common.hpp"
#include "../sqlworker.hpp"

#include "ormfield.h"
#include "ormfieldhandler.h"
#include "database.h"


#define ORM_EXPORT_CLASS(ClassName) \
    namespace orm { \
        template <> \
        std::string getClassName<ClassName>() \
        {return #ClassName ; } \
    }

#define ORM_MODEL_FIELD(Field) \
    (orm::OrmField<TYPEOF(Field)>(Field, &Field, #Field))

namespace orm {

}

#endif
