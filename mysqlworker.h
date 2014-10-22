#ifndef __MYSQLWORKER_H__
#define __MYSQLWORKER_H__

#include <string>
#include <vector>
#include "functional/either.h"
#include "sqlworker.h"

#include <my_global.h>
#include <mysql.h>


class MySQLWorker : public SQLWorker
{
public:
    MySQLWorker(const std::string &server, const std::string &login,
                const std::string &password, const std::string &dbName);

    //virtual bool connected() const = 0;
    //virtual SQLQueryResult query(const std::string &qu) const = 0;
};

#endif
