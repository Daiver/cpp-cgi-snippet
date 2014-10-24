
#include <string>

#include "../common.h"
#include "../sqlworker.h"


#define ORM_EXPORT_CLASS(ClassName) \
    namespace orm { \
        template <> \
        std::string getClassName<ClassName>() \
        {return #ClassName ; } \
    }

namespace orm {

template <typename ClassName> 
std::string getClassName() ;
}
