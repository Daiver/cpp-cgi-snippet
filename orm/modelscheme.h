#ifndef __MODEL_SCHEME_H__
#define __MODEL_SCHEME_H__

#include <string>
#include <sstream>
#include <vector>
#include "../functional/tripple.h"

namespace orm{

#define ORM_ID_PREFIX "orm_id_"
#define ORM_TABLE_PREFIX "orm_model_"


//represents sql version of model
class ModelScheme{
public:

    std::string modelName;
    std::vector<functional::Tripple<std::string, std::string, std::string> > fields;

    static std::string ormIdPrefix;

    std::string getCreationTableQuery() const;

    std::string getInsertQuery() const;

    std::string getUpdateQuery(int id) const;

    std::string getSelectByIdQuery(int id) const;

    std::string getDeleteQuery(int id) const;

};

}

#endif
