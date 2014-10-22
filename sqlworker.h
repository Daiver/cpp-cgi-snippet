#ifndef __SQLWORKER_H__
#define __SQLWORKER_H__

#include <string>
#include <vector>
#include "functional/either.h"

class SQLWorker
{
public:
    typedef functional::Either<std::string, std::vector<std::vector<std::string> > > SQLQueryResult;

    virtual bool connected() const = 0;
    virtual SQLQueryResult query(const std::string &qu) const = 0;
};

#endif
