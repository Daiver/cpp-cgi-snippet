#ifndef __MODEL_PTR_H__
#define __MODEL_PTR_H__

#include "../sqlworker.h"
#include "modelscheme.h"
#include "ormfield.h"
#include "ormfieldhandler.h"

namespace orm {

template<typename ModelClass>
class ModelPtr
{
public:
    ModelPtr(SQLWorker *sqlWorker, ModelClass *obj);

    int newInst(ModelClass &obj);

    void updInst(int id, ModelClass &obj);

    void deleteInst(int id);

    functional::Either<std::string, ModelClass> getInstById(int id);

    ModelClass *obj;
    SQLWorker *sqlWorker;
};

}

template<typename ModelClass>
orm::ModelPtr<ModelClass>::ModelPtr(SQLWorker *sqlWorker, ModelClass *obj)
{
    this->sqlWorker = sqlWorker;
    this->obj = obj;
}

template<typename ModelClass>
int orm::ModelPtr<ModelClass>::newInst(ModelClass &obj)
{
    ModelScheme scheme;
    scheme.modelName = getClassName<ModelClass>();
    this->initScheme(obj, &scheme);

    sqlWorker->query(scheme.getInsertQuery());
    return atoi(sqlWorker->query("SELECT LAST_INSERT_ID()").getValue()[0][0].c_str());
}

template<typename ModelClass>
void orm::ModelPtr<ModelClass>::updInst(int id, ModelClass &obj)
{
    ModelScheme scheme;
    scheme.modelName = getClassName<ModelClass>();
    this->initScheme(obj, &scheme);

    sqlWorker->query(scheme.getUpdateQuery(id));
}

template<typename ModelClass>
functional::Either<std::string, ModelClass> orm::ModelPtr<ModelClass>::getInstById(int id)
{
    ModelClass res;
    ModelScheme scheme;
    scheme.modelName = getClassName<ModelClass>();
    this->initScheme(res, &scheme);

    std::string q = scheme.getSelectByIdQuery(id);
    //std::cout << q << std::endl;
    SQLWorker::SQLQueryResult ans = sqlWorker->query(q);
    if(ans.isLeft)
        return functional::Either<std::string, ModelClass>::Left(ans.getLeft());

    if(ans.getValue().size() != 1)
        return functional::Either<std::string, ModelClass>::Left("Bad count of rows!");

    std::vector<std::string> values = ans.getValue()[0];
    OrmFieldHandler handler(NULL, &values, true);
    res.initOrm(handler);

    return functional::Either<std::string, ModelClass>::Right(res);
}


template<typename ModelClass>
void orm::ModelPtr<ModelClass>::deleteInst(int id)
{
    ModelClass res;
    ModelScheme scheme;
    scheme.modelName = getClassName<ModelClass>();
    this->initScheme(res, &scheme);

    std::string q = scheme.getDeleteQuery(id);
    SQLWorker::SQLQueryResult ans = sqlWorker->query(q);
   
}


#endif
