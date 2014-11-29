
#include "modelscheme.hpp"

using namespace orm;

std::string ModelScheme::getCreationTableQuery() const
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


std::string ModelScheme::getInsertQuery() const
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


std::string ModelScheme::getUpdateQuery(int id) const
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

std::string ModelScheme::getSelectByIdQuery(int id) const
{
    std::stringstream ss;
    ss << id;
    std::string res = "SELECT * FROM `" + std::string(ORM_TABLE_PREFIX) + this->modelName + "` WHERE " + std::string(ORM_ID_PREFIX) + this->modelName + "=" + ss.str();
    return res;
}

std::string ModelScheme::getDeleteQuery(int id) const
{
    std::stringstream ss;
    ss << id;
    std::string res = "DELETE FROM `" + std::string(ORM_TABLE_PREFIX) + modelName + "` WHERE " + std::string(ORM_ID_PREFIX) + modelName + "=" + ss.str();
    return res;
}
