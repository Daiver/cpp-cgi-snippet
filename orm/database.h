#ifndef __DATABASE_H__
#define __DATABASE_H__

#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <sstream>
#include <iostream>

#include "ormfield.h"
#include "ormfieldhandler.h"

#include "../sqlworker.h"
#include "../functional/tripple.h"

namespace orm {

#define ORM_ID_PREFIX "orm_id_"
#define ORM_TABLE_PREFIX "orm_model_"

//represents sql version of model
class ModelScheme{
public:

    std::string modelName;
    std::vector<functional::Tripple<std::string, std::string, std::string> > fields;

    static std::string ormIdPrefix;

    std::string getCreationTableQuery() const
    {
        std::ostringstream stringStream;
        stringStream << "CREATE TABLE `" << ORM_TABLE_PREFIX << modelName << "` (";
        stringStream << "`" << ORM_ID_PREFIX << modelName 
                     << "` INT NOT NULL AUTO_INCREMENT, ";
        for(int i = 0; i < fields.size(); ++i){
            stringStream << "`" << fields[i].first << "` " << fields[i].second << ", ";
        }
        stringStream << "PRIMARY KEY(`"<< ORM_ID_PREFIX << modelName << "`)";
        stringStream << ");";

        return stringStream.str();
    }

    std::string getInsertQuery() const
    {
        std::string res = "INSERT INTO `" + std::string(ORM_TABLE_PREFIX) + modelName + "` (";// + "` VALUES(" ;
        res += fields[0].first;
        for(int i = 1; i < fields.size(); ++i){
            res += ", " + fields[i].first;
        }
        res += ") VALUES(";
        res += fields[0].third;
        for(int i = 1; i < fields.size(); ++i){
            res += ", " + fields[i].third;
        }
        res += ");";
        return res;
    }

    std::string getUpdateQuery(int id) const
    {
        std::string res = "UPDATE `" + std::string(ORM_TABLE_PREFIX) + modelName + "` SET " ;
        res += fields[0].first + "=" + fields[0].third;
        for(int i = 1; i < fields.size(); ++i){
            res += ", " + fields[i].first + "=" + fields[i].third;
        }
        std::stringstream ss;
        ss << id;

        res += " WHERE " + std::string(ORM_ID_PREFIX) + modelName + "=" + ss.str();
        return res;
    }

    std::string getSelectByIdQuery(int id) const
    {
        std::stringstream ss;
        ss << id;
        std::string res = "SELECT * FROM `" + std::string(ORM_TABLE_PREFIX) + this->modelName + "` WHERE " + std::string(ORM_ID_PREFIX) + this->modelName + "=" + ss.str();
        return res;
    }
};

class Database
{
public:

    Database(SQLWorker *worker=NULL);

    template <typename ClassName>
    std::string getClassName();

    template<typename ModelClass>
    ModelScheme getSchemeFromModelClass();

    template <typename ModelClass>
    void initScheme(ModelClass &obj, ModelScheme *sch);

    template <typename ModelClass>
    void registerModel();

    void createScheme();

    template<typename ModelClass>
    int newInst(ModelClass &obj);

    template<typename ModelClass>
    void updInst(int id, ModelClass &obj);

    template<typename ModelClass>
    functional::Either<std::string, ModelClass> getInstById(int id);

    SQLWorker *sqlWorker;
    std::vector<ModelScheme> models;
};
}

template<typename ModelClass>
void orm::Database::initScheme(ModelClass &obj, ModelScheme *sch)
{
    obj.initOrm(OrmFieldHandler(&sch->fields));
}

template<typename ModelClass>
orm::ModelScheme orm::Database::getSchemeFromModelClass()
{
    ModelScheme res;
    res.modelName = getClassName<ModelClass>();
    ModelClass tmpInst;
    this->initScheme(tmpInst, &res);
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
    this->initScheme(obj, &scheme);

    sqlWorker->query(scheme.getInsertQuery());
    return atoi(sqlWorker->query("SELECT LAST_INSERT_ID()"
                    /*"SELECT " + std::string(ORM_ID_PREFIX) + 
                    scheme.modelName + " FROM " +
                    std::string(ORM_TABLE_PREFIX) + scheme.modelName*/
                    ).getValue()[0][0].c_str());
}

template<typename ModelClass>
void orm::Database::updInst(int id, ModelClass &obj)
{
    ModelScheme scheme;
    scheme.modelName = getClassName<ModelClass>();
    this->initScheme(obj, &scheme);

    sqlWorker->query(scheme.getUpdateQuery(id));
}

template<typename ModelClass>
functional::Either<std::string, ModelClass> orm::Database::getInstById(int id)
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

#endif
