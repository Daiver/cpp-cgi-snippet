#ifndef __SQLWORKER_H__
#define __SQLWORKER_H__

#include <string>
#include <vector>
#include "functional/either.h"

class SQLWorker
{
public:
    typedef std::vector<std::vector<std::string> > VectorOfVectorOfString;
    typedef functional::Either<std::string, VectorOfVectorOfString > SQLQueryResult;

    virtual bool isConnected() const = 0;
    virtual SQLQueryResult query(const std::string &qu) const = 0;
};

#endif
