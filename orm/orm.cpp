#include "orm.h"

struct C{int a;};
ORM_EXPORT_CLASS(C);
/*namespace orm{
    template<>
    std::string getClassName<int>()
    {return "c";}
}*/
