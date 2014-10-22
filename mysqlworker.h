#ifndef __MYSQLWORKER_H__
#define __MYSQLWORKER_H__

#include <string>
#include <vector>
#include <stdio.h>
#include "functional/either.h"
#include "sqlworker.h"

#include <my_global.h>
#include <mysql.h>


class MySQLWorker : public SQLWorker
{
public:
    typedef functional::Either<std::string, MYSQL *> ConnectionResult;

    MySQLWorker();

    ConnectionResult connect(const std::string &server, const std::string &login,
                const std::string &password, const std::string &dbName);

    bool isConnected() const {return this->isConnectedToDb; }
    //virtual SQLQueryResult query(const std::string &qu) const = 0;

    bool isConnectedToDb;
    MYSQL *connection;
};

#endif
