#include "database.h"

using namespace orm;

Database::Database(SQLWorker *worker): sqlWorker(worker)
{
}

void Database::createScheme()
{
    for(int i = 0; i < models.size(); ++i)
        sqlWorker->query(models[i].getCreationTableQuery());
}
