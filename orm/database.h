#ifndef __DATABASE_H__
#define __DATABASE_H__

#include <string>
#include <vector>

#include "ormfield.h"

#include "../sqlworker.h"

namespace orm {
class Database
{
public:
    template <typename ClassName>
    std::string getClassName();

    template <typename ModelClass>
    void registerModel();

    void createScheme();

    std::vector<std::string> modelNames;
};
}

template<typename ModelClass>
void orm::Database::registerModel()
{
    modelNames.push_back(this->getClassName<ModelClass>());
}

#endif
