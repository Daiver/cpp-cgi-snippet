#ifndef __MODEL_PTR_H__
#define __MODEL_PTR_H__

#include "../sqlworker.hpp"
#include "modelscheme.hpp"
#include "ormfield.hpp"
#include "ormfieldhandler.hpp"

namespace orm {

template<typename ModelClass>
void initScheme(ModelClass &obj, ModelScheme *sch)
{
    obj.initOrm(OrmFieldHandler(&sch->fields));
}


template<typename ModelClass>
class ModelPtr
{
public:
    ModelPtr();
    ModelPtr(SQLWorker *sqlWorker, const ModelClass &obj);
    ~ModelPtr();

    int newInst(ModelClass &obj);
    void updInst();
    void destroy();
    const ModelClass *operator -> () const;
    ModelClass *operator -> ();

    int id;
    bool isModified;
    bool isCreated;
    ModelClass obj;
    SQLWorker *sqlWorker;
};

}

template<typename ModelClass>
orm::ModelPtr<ModelClass>::ModelPtr()
{
    this->sqlWorker = NULL;
    id = -1;
    isModified = false;
    isCreated  = false;
}

template<typename ModelClass>
orm::ModelPtr<ModelClass>::ModelPtr(SQLWorker *sqlWorker, const ModelClass &obj)
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
    if(isCreated && isModified){
        updInst();
    }
}

template<typename ModelClass>
ModelClass *orm::ModelPtr<ModelClass>::operator -> () 
{
    isModified = true;
    return &obj;
}

template<typename ModelClass>
const ModelClass *orm::ModelPtr<ModelClass>::operator -> () const
{
    return &obj;
}

template<typename ModelClass>
int orm::ModelPtr<ModelClass>::newInst(ModelClass &obj)
{
    ModelScheme scheme;
    scheme.modelName = getClassName<ModelClass>();
    initScheme(obj, &scheme);

    sqlWorker->query(scheme.getInsertQuery());
    return atoi(sqlWorker->query("SELECT LAST_INSERT_ID()").getValue()[0][0].c_str());
}

template<typename ModelClass>
void orm::ModelPtr<ModelClass>::updInst()
{
    ModelScheme scheme;
    scheme.modelName = getClassName<ModelClass>();
    initScheme(obj, &scheme);

    std::string q = scheme.getUpdateQuery(id);

    if(sqlWorker->query(q).isLeft)
        std::cout << "UPD ERR " << q << std::endl;
}

template<typename ModelClass>
void orm::ModelPtr<ModelClass>::destroy()
{
    ModelClass res;
    ModelScheme scheme;
    scheme.modelName = getClassName<ModelClass>();
    initScheme(res, &scheme);

    std::string q = scheme.getDeleteQuery(id);
    SQLWorker::SQLQueryResult ans = sqlWorker->query(q);
    isCreated = false;
}

#endif
