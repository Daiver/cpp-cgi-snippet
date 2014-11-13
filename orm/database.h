#ifndef __DATABASE_H__
#define __DATABASE_H__

#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <iostream>

#include "ormfield.h"
#include "ormfieldhandler.h"
#include "modelscheme.h"
#include "modelptr.h"


#include "../sqlworker.h"
#include "../functional/tripple.h"

namespace orm {

class Database
{
public:

    Database(SQLWorker *worker=NULL);

    //template <typename ClassName>
    //std::string getClassName();

    template<typename ModelClass>
    ModelScheme getSchemeFromModelClass();

    //template <typename ModelClass>
    //void initScheme(ModelClass &obj, ModelScheme *sch);

    template <typename ModelClass>
    void registerModel();

    void createScheme();

    template<typename ModelClass>
    int newInst(ModelClass &obj);

    template<typename ModelClass>
    void updInst(int id, ModelClass &obj);

    template<typename ModelClass>
    void deleteInst(int id);

    template<typename ModelClass>
    functional::Either<std::string, ModelClass> getInstById(int id);

    template<typename ModelClass>
    functional::Either<std::string, orm::ModelPtr<ModelClass> > getPtrById(int id);

    template<typename ModelClass>
    ModelPtr<ModelClass> createRecord(const ModelClass &example);

    SQLWorker *sqlWorker;
    std::vector<ModelScheme> models;
};
}

template<typename ModelClass>
orm::ModelPtr<ModelClass> orm::Database::createRecord(const ModelClass &example)
{
    ModelPtr<ModelClass> ptr(this->sqlWorker, example);
    ptr.id = ptr.newInst(ptr.obj);
    ptr.isCreated = true;
    return ptr;
}

/*template<typename ModelClass>
void orm::Database::initScheme(ModelClass &obj, ModelScheme *sch)
{
    obj.initOrm(OrmFieldHandler(&sch->fields));
}*/

template<typename ModelClass>
orm::ModelScheme orm::Database::getSchemeFromModelClass()
{
    ModelScheme res;
    res.modelName = getClassName<ModelClass>();
    ModelClass tmpInst;
    initScheme(tmpInst, &res);
    return res;
}

template<typename ModelClass>
void orm::Database::registerModel()
{
    models.push_back(this->getSchemeFromModelClass<ModelClass>());
}

template<typename ModelClass>
int orm::Database::newInst(ModelClass &obj)
{

    ModelScheme scheme;
    scheme.modelName = getClassName<ModelClass>();
    initScheme(obj, &scheme);

    sqlWorker->query(scheme.getInsertQuery());
    return atoi(sqlWorker->query("SELECT LAST_INSERT_ID()").getValue()[0][0].c_str());
}

template<typename ModelClass>
void orm::Database::updInst(int id, ModelClass &obj)
{
    ModelScheme scheme;
    scheme.modelName = getClassName<ModelClass>();
    initScheme(obj, &scheme);

    sqlWorker->query(scheme.getUpdateQuery(id));
}

template<typename ModelClass>
functional::Either<std::string, ModelClass> orm::Database::getInstById(int id)
{
    ModelClass res;
    ModelScheme scheme;
    scheme.modelName = getClassName<ModelClass>();
    initScheme(res, &scheme);

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
functional::Either<std::string, orm::ModelPtr<ModelClass> > 
        orm::Database::getPtrById(int id)
{
    functional::Either<std::string, ModelClass> ans = getInstById<ModelClass>(id);
    if(ans.isLeft)
        return functional::Either<std::string, ModelPtr<ModelClass> >::Left(ans.getLeft());
    
    ModelPtr<ModelClass> res(this->sqlWorker, ans.getValue());
    res.isCreated = true;
    res.id = id;
    return functional::Either<std::string, ModelPtr<ModelClass> >::Right(res);
}

template<typename ModelClass>
void orm::Database::deleteInst(int id)
{
    ModelClass res;
    ModelScheme scheme;
    scheme.modelName = getClassName<ModelClass>();
    initScheme(res, &scheme);

    std::string q = scheme.getDeleteQuery(id);
    SQLWorker::SQLQueryResult ans = sqlWorker->query(q);
   
}

#endif
