#ifndef __MYSQLWORKER_H__
#define __MYSQLWORKER_H__

#include <string>
#include <vector>
#include <stdio.h>
#include "functional/either.h"
#include "sqlworker.h"

#include "mysql-connector-c-6.1.5-linux-glibc2.5-x86_64/include/my_global.h"
#include "mysql-connector-c-6.1.5-linux-glibc2.5-x86_64/include/mysql.h"

class MySQLWorker : public SQLWorker
{
public:
    typedef functional::Either<std::string, MYSQL *> ConnectionResult;

    MySQLWorker();
    ~MySQLWorker();

    ConnectionResult connect(const std::string &server, const std::string &login,
                const std::string &password, const std::string &dbName);

    bool isConnected() const {return this->isConnectedToDb; }
    SQLQueryResult query(const std::string &qu) const;

    bool isConnectedToDb;
    MYSQL *connection;
};

#endif
