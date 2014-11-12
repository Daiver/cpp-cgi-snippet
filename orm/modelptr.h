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
    ModelPtr(SQLWorker *sqlWorker, ModelClass &obj);
    ~ModelPtr();

    int newInst(ModelClass &obj);
    void updInst();
    void destroy();
    ModelClass *operator -> () const;

    int id;
    bool isModified;
    bool isCreated;
    ModelClass obj;
    SQLWorker *sqlWorker;
};

}

template<typename ModelClass>
orm::ModelPtr<ModelClass>::ModelPtr(SQLWorker *sqlWorker, ModelClass &obj)
{
    this->sqlWorker = sqlWorker;
    this->obj = obj;
    id = -1;
    isModified = false;
    isCreated  = false;
}


template<typename ModelClass>
orm::ModelPtr<ModelClass>::~ModelPtr()
{
    if(isCreated)
        updInst();
}

template<typename ModelClass>
ModelClass *orm::ModelPtr<ModelClass>::operator -> () const
{
    return &obj;
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
void orm::ModelPtr<ModelClass>::updInst()
{
    ModelScheme scheme;
    scheme.modelName = getClassName<ModelClass>();
    this->initScheme(obj, &scheme);

    sqlWorker->query(scheme.getUpdateQuery(id));
}

template<typename ModelClass>
void orm::ModelPtr<ModelClass>::destroy()
{
    ModelClass res;
    ModelScheme scheme;
    scheme.modelName = getClassName<ModelClass>();
    this->initScheme(res, &scheme);

    std::string q = scheme.getDeleteQuery(id);
    SQLWorker::SQLQueryResult ans = sqlWorker->query(q);
    isCreated = false;
}


#endif
