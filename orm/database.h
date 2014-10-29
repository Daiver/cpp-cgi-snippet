#ifndef __DATABASE_H__
#define __DATABASE_H__

#include <string>
#include <vector>
#include <sstream>

#include "ormfield.h"

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
        //CREATE TABLE `table1` (`user_id` INT(5) NOT NULL AUTO_INCREMENT, `username` VARCHAR(50), PRIMARY KEY(`user_id`), INDEX(`username`));
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
        std::string res = "INSERT INTO `" + modelName + "` VALUES(" ;
        res += fields[0].third;
        for(int i = 1; i < fields.size(); ++i){
            res += ", " + fields[i].third;
        }
        res += ");";
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
    void registerModel();

    void createScheme();

    template<typename ModelClass>
    void newInst(ModelClass &obj);

    SQLWorker *sqlWorker;
    std::vector<ModelScheme> models;
};
}

template<typename ModelClass>
orm::ModelScheme orm::Database::getSchemeFromModelClass()
{
    ModelScheme res;
    res.modelName = getClassName<ModelClass>();
    ModelClass tmpInst;
    tmpInst.initOrm(&res.fields);
    return res;
}

template<typename ModelClass>
void orm::Database::registerModel()
{
    models.push_back(this->getSchemeFromModelClass<ModelClass>());
}

template<typename ModelClass>
void orm::Database::newInst(ModelClass &obj)
{

    ModelScheme scheme;
    scheme.modelName = getClassName<ModelClass>();
    obj.initOrm(&scheme.fields);

    sqlWorker->query(scheme.getInsertQuery());
}

#endif
